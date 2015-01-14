#!/bin/bash

# Make the data
./data.sh > dest/tmp.csv

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
