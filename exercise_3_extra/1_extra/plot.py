#!/usr/bin/env python

import sys
from numpy import genfromtxt
import matplotlib.pyplot as plt

data = genfromtxt(sys.stdin, skip_header=1, delimiter=',')
plt.plot(data[:, 0], data[:, 1])
plt.xlabel('num_procs')
plt.ylabel('scatter_gather_time')

plt.show()
