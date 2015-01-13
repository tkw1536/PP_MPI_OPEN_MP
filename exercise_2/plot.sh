#!/bin/bash

# Make the data
mpirun -np 2 dest/pingpong > dest/tmp.csv

# And run the plot
python -c "
from numpy import genfromtxt
import matplotlib.pyplot as plt

data = genfromtxt('dest/tmp.csv', skip_header=1, delimiter=',')
plt.loglog(data[:, 0], data[:, 1])
plt.xlabel('message_size')
plt.ylabel('transfer_time')

plt.show()
"
