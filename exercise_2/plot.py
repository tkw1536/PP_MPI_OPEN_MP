#!/usr/bin/env python

import sys
from numpy import genfromtxt
import matplotlib.pyplot as plt

data = genfromtxt(sys.stdin, skip_header=1, delimiter=',')
plt.loglog(data[:, 0], data[:, 1])
plt.xlabel('message_size')
plt.ylabel('transfer_time')

plt.show()
