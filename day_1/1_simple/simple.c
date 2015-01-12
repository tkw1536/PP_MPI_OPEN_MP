#include <stdio.h>
#include <mpi.h>

//OPEN MPI testing
//(c) Tom Wiesing 2015

int main(int argc, char *argv[]){
  //declare a few variables.
  int comm_rank;

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }

  //Get the current process
  if(MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank) != MPI_SUCCESS){
    return 1;
  }

  //we want to print only for the first process.
  if(comm_rank == 0){
    //Print Something!
    printf("Hello World!\n");
  }

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
