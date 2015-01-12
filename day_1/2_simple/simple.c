#include <stdio.h>
#include <mpi.h>

//OPEN MPI testing
//(c) Tom Wiesing 2015

int main(int argc, char *argv[]){
  //declare a few variables.
  int comm_size, comm_rank;

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }


  //Get the number of processes.
  if(MPI_Comm_size(MPI_COMM_WORLD, &comm_size) != MPI_SUCCESS){
    return 1;
  }

  //Get the current process
  if(MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank) != MPI_SUCCESS){
    return 1;
  }

  //Print Something for every process!
  printf("Process %d / %d saying Hello World!\n", comm_rank, comm_size);

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
