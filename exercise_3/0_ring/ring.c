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

  int comm_size, comm_rank, comm_next, comm_prev;

  MPI_Request request;
  MPI_Status status;

  //get the variables.
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

  //compute the next and previous person.
  comm_next = (comm_rank + 1) % comm_size;
  comm_prev = (comm_rank + comm_size - 1) % comm_size;

  int dataSend[1];
  int dataReceive[1];
  int count = 0;

  //intialiser.
  dataReceive[0] = -1;
  dataSend[0] = comm_rank;

  while(dataReceive[0] != comm_rank){

    //send, non-blocking
    MPI_Issend(dataSend, 1, MPI_INT, comm_next, 0, MPI_COMM_WORLD, &request);

    //receive, blocking.
    MPI_Recv(dataReceive, 1, MPI_INT, comm_prev, 0, MPI_COMM_WORLD, &status);

    //end the send.
    MPI_Wait(&request, &status);

    //we want to send the next data value.
    dataSend[0] = dataReceive[0];
    count = count + dataSend[0];
  }

  printf("Count %d (in process %d)!\n", count, comm_rank);

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
