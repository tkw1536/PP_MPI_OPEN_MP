#include <stdio.h>
#include <mpi.h>

/*
* Copyright (c) 2015 Tom Wiesing
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

double run_main(){
  int comm_size, comm_rank, data, i;
  double end_time, start_time;

  MPI_Request request;
  MPI_Status status;

  //get the variables.
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

  int data_gather[comm_size - 1];

  start_time = MPI_Wtime();

  //OK, send things
  MPI_Bcast(&data, 1, MPI_INT, 0, MPI_COMM_WORLD);

  //and gather them back.
  MPI_Gather(&data, 1, MPI_INT, &data_gather, 1, MPI_INT, 0, MPI_COMM_WORLD);

  end_time = MPI_Wtime();

  return end_time - start_time;
}

int main(int argc, char *argv[]){

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }

  int i, j, num = 100;
  double count = 0;

  MPI_Comm_rank(MPI_COMM_WORLD, &j);

  for(i = 0; i < num; i++){
    count += (run_main() / num);
  }

  if(j == 0){
    printf("%f", count);
  }

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
