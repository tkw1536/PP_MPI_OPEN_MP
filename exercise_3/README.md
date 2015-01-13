# Exercise 3

* A set of processes are arranged in a ring.
* Each process stores its rank in MPI_COMM_WORLD
in an integer.
* Each process passes this on to its neighbour on the right.
* Keep passing what is received until the own rank is back where it started.
* Each processor calculates the sum of the values. [0_ring](0_ring)

* Rewrite the pass-around-the-ring program to use MPI global reduction to perform its global sums. [1_ring](1_ring)
* Then rewrite it so that each process computes a partial sum.
* Then rewrite this so that the program prints out the partial results in the correct order (process 0, then process 1, etc.). [2_ring](2_ring)
