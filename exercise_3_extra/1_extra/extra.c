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

int main(int argc, char *argv[]){

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }

  int comm_size, comm_rank, i;
  double end_time, start_time;

  MPI_Request request;
  MPI_Status status;

  //get the variables.
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

  int data_gather[comm_size - 1];
  int data[comm_size - 1];

  if(comm_rank == 0){
    //fill the array.
    for(i = 0;i < comm_size - 1; i++){
      data[i] = 0;
    }

    start_time = MPI_Wtime();

    //send data
    MPI_Scatter(&data, 1, MPI_INT, &data_gather, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //and receive data_gather
    MPI_Gather(&data, 1, MPI_INT, &data_gather, 1, MPI_INT, 0, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

    printf("%f", end_time - start_time);

  } else {
    //receive data
    MPI_Scatter(&data_gather, 1, MPI_INT, &data, 1, MPI_INT, 0, MPI_COMM_WORLD);

    //and send data again.
    MPI_Gather(&data, 1, MPI_INT, &data_gather, 1, MPI_INT, 0, MPI_COMM_WORLD);
  }

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
