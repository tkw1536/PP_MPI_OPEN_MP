#!/bin/bash

# Make the data
echo "num_procs, transfer_time"
for i in `seq 2 20`;
do
  mpirun -np $i dest/p2p
done
