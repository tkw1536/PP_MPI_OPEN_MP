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


int runMPImaster(int size, int num_procs, int repeats){
  double time = 0; 
  int i, j; 
  double data[size];
  MPI_Status receiver_status;
  double start_time, end_time;
  
  for(j = 0; j < repeats; j++){
    //intialise zeros to send.
    int i;
    for(i = 0; i < size; i++){
      data[i] = 0;
    }

    start_time = MPI_Wtime();

    //send the things.
    for(i = 1;i < num_procs;i++){
      MPI_Ssend(&data, size, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      MPI_Recv(&data, size, MPI_DOUBLE, i, 1, MPI_COMM_WORLD, &receiver_status);
    }  

    //end time and output.
    end_time = MPI_Wtime();
    time = time + (end_time - start_time)/repeats; 
  }

  printf("%2d, %.6f\n", num_procs, time);

  return 0;
}

int runMPIslave(int size, int num_procs, int repeats){
  //declare a few variables
  double data[size];
  MPI_Status receiver_status;
  int j; 
  for(j = 0; j < repeats; j++){
    //Receive the data and send it back.
    MPI_Recv(&data, size, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, &receiver_status);
    MPI_Ssend(&data, size, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
  }

  return 0;
}

int startMPI(){

  int size = 1, comm_rank, comm_size;

  if(MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank) != MPI_SUCCESS){
    return 1;
  }

  if(MPI_Comm_size(MPI_COMM_WORLD, &comm_size) != MPI_SUCCESS){
    return 1;
  }

  int repeats = 100; 

  if(comm_rank == 0){
    return runMPImaster(size, comm_size, repeats);
  } else {
    return runMPIslave(size, comm_size, repeats);
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
