#!/bin/bash

# Make the data
echo "num_procs, bcast_gather_time"
for i in `seq 2 20`;
do
  echo "$i, $(mpirun -np $i dest/extra)"
done
