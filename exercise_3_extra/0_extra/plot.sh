#!/bin/bash

# Make the data
echo "num_procs, bcast_gather_time" > dest/tmp.csv
for i in `seq 2 20`;
do
  echo "$i, $(mpirun -np $i dest/extra)">> dest/tmp.csv
done

# And run the plot
python -c "
from numpy import genfromtxt
import matplotlib.pyplot as plt

data = genfromtxt('dest/tmp.csv', skip_header=1, delimiter=',')
plt.plot(data[:, 0], data[:, 1])
plt.xlabel('num_procs')
plt.ylabel('bcast_gather_time')

plt.show()
"
