#!/bin/bash

mkdir -p dest

# Make the data
echo "num_procs, bcast_gather_time, scatter_gather_time"
for i in `seq 2 20`;
do
  echo "$i, $(mpirun -np $i 0_extra/dest/extra), $(mpirun -np $i 1_extra/dest/extra)"
done
