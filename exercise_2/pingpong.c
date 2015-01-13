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


double MPIPongA(int size){
  //variables
  double data[size];
  double time_start, time_end;
  MPI_Status receiver_status;

  //intialise zeros to send.
  int i;
  for(i = 0; i < size; i++){
    data[i] = 0;
  }

  //send and wait for the response.
  time_start = MPI_Wtime();
  MPI_Ssend(&data, size, MPI_DOUBLE, 1, 0, MPI_COMM_WORLD);
  MPI_Recv(&data, size, MPI_DOUBLE, 1, 1, MPI_COMM_WORLD, &receiver_status);
  time_end = MPI_Wtime();

  return time_end - time_start;
}

void MPIPongB(int size){
  //declare a few variables
  double data[size];
  MPI_Status receiver_status;

  //Receive the data and send it back.
  MPI_Recv(&data, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &receiver_status);
  MPI_Ssend(&data, size, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
}

int runMPImaster(int size_count, int *sizes){
  printf("message_size, transfer_time\n");

  //iterate through the sizes.
  int i = 0;
  for(i = 0;i < size_count;i++){
    printf("%6d, %.6f\n", sizes[i], MPIPongA(sizes[i]));
  }


  return 0;
}

int runMPIslave(int size_count, int *sizes){
  //for the slave just do things.
  int i = 0;
  for(i = 0;i < size_count;i++){
    MPIPongB(sizes[i]);
  }
  return 0;
}

int startMPI(){

  //initalise some variables
  int i, comm_rank, size_count = 20;
  int sizes[size_count];

  //intialise the sizes array
  sizes[0] = 1;

  for(i = 1;i<size_count;i++){
    sizes[i] = 2*sizes[i-1];
  }

  if(MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank) != MPI_SUCCESS){
    return 1;
  }

  if(comm_rank == 0){
    return runMPImaster(size_count, sizes);
  } else if(comm_rank == 1){
    return runMPIslave(size_count, sizes);
  } else {
    //nothing to do.
    return 0;
  }

}

int checkMPINeeds(){

  //Get the comm size
  int comm_size;

  if(MPI_Comm_size(MPI_COMM_WORLD, &comm_size) != MPI_SUCCESS){
    return 1;
  }

  if(comm_size < 2){
    printf("MPI_Comm_size must be at least 2. ");
    MPI_Abort(MPI_COMM_WORLD, 1);
    return 1;
  }

  return 0;
}


int main(int argc, char *argv[]){
  //declare a few variables.
  int comm_size, comm_rank;

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }


  //Check what we need for this one.
  if(checkMPINeeds() != 0){
    return 1;
  }

  //run the code
  if(startMPI() != 0){
    return 1;
  }

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
