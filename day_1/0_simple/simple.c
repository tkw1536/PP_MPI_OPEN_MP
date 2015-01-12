#include <stdio.h>
#include <mpi.h>

//OPEN MPI testing
//(c) Tom Wiesing 2015

int main(int argc, char *argv[]){

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }

  //hello world!
  printf("Hello World!\n");

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
