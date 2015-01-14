#include <stdio.h>
#include <mpi.h>
#define FALSE 0
#define TRUE !(FALSE)

/*
* Copyright (c) 2015 Tom Wiesing
*
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

struct IntAndFloat {
  int integer;
  float floating;
};

void create_IntAndFloat_type(struct IntAndFloat *instance, MPI_Datatype *MPI_Intandfloat){
  //these types we need for computing the new datatype
  int MPI_Intandfloat_counts[2] = {1, 1};
  MPI_Datatype MPI_Intandfloat_types[2] = {MPI_INT, MPI_FLOAT};
  MPI_Aint MPI_Intandfloat_offsets[3];

  //comute offsets
  MPI_Get_address(&(instance->integer), &MPI_Intandfloat_offsets[0]);
  MPI_Get_address(&(instance->floating), &MPI_Intandfloat_offsets[1]);
  MPI_Get_address(instance, &MPI_Intandfloat_offsets[2]);
  MPI_Intandfloat_offsets[0] -= MPI_Intandfloat_offsets[2];
  MPI_Intandfloat_offsets[1] -= MPI_Intandfloat_offsets[2];

  //Create the datatypye
  MPI_Type_create_struct(2, MPI_Intandfloat_counts, MPI_Intandfloat_offsets, MPI_Intandfloat_types, MPI_Intandfloat);
}

void create_ring(int comm_size, int comm_rank, MPI_Comm *MPI_ring_comm){
  int dims[] = {0, 0};
  int periods[] = {TRUE, FALSE};

  MPI_Dims_create(comm_size, 2, dims);
  MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, TRUE, MPI_ring_comm);
}

int main(int argc, char *argv[]){

  //Intialise MPI
  if(MPI_Init(&argc, &argv) != MPI_SUCCESS){
    return 1;
  }

  int comm_size, comm_rank, comm_next, comm_prev;

  MPI_Request request;
  MPI_Status status;
  MPI_Comm MPI_ring_comm;
  MPI_Datatype MPI_Intandfloat;

  //get the variables.
  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

  //compute the next and previous person.
  create_ring(comm_size, comm_rank, &MPI_ring_comm);

  if(MPI_ring_comm == MPI_COMM_NULL){
    MPI_Finalize(); 
    return 0;
  }

  MPI_Cart_shift(MPI_ring_comm, 0, 1, &comm_prev, &comm_next);

  //Here is my count.
  struct IntAndFloat count;
  count.integer = 0;
  count.floating = 0;

  //Create the type and commit it.
  create_IntAndFloat_type(&count, &MPI_Intandfloat);
  MPI_Type_commit(&MPI_Intandfloat);

  //what we need to receive and send.
  struct IntAndFloat dataSend[1];
  struct IntAndFloat dataReceive[1];

  dataSend[0].integer = comm_rank;
  dataSend[0].floating = (float) comm_rank;

  dataReceive[0].integer = -1;
  dataReceive[0].floating = -1.0;

  while(dataReceive[0].integer != comm_rank){

    //send and receive
    MPI_Sendrecv(dataSend, 1, MPI_Intandfloat, comm_next, 0, dataReceive, 1, MPI_Intandfloat, comm_prev, 0, MPI_ring_comm, &status);

    //we want to send the next data value.
    dataSend[0].integer = dataReceive[0].integer;
    dataSend[0].floating = dataReceive[0].floating;

    //add to the counter
    count.integer = count.integer + dataSend[0].integer;
    count.floating = count.floating + dataSend[0].floating;
  }

  int coords[2];

  MPI_Cart_coords(MPI_ring_comm, comm_rank, 2, coords);

  printf("Count %d, %f (in process %d %d)!\n", count.integer, count.floating, coords[0], coords[1]);

  //Finalise MPI
  if(MPI_Finalize() != MPI_SUCCESS){
    return 1;
  }

  //and we're done.
  return 0;
}
