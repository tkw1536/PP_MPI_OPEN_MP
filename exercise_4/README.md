# Exercise 4

* Modify the passing-around-a-ring exercise.
* Calculate two separate sums:
  * rank integer sum, as before
  * rank floating point sum
* Use a struct datatype for this.
* Advanced: Instead of passing around the ring use global reduction and a user-defined function for the sum of the struct. [0_ring](0_ring)

*  Rewrite the exercise passing numbers round the ring using a one-dimensional ring topology. [1_ring](1_ring)

* Rewrite the exercise in two dimensions, as a torus. Each row of the torus should compute its own separate result.
* Extra exercise: Let MPI calculate the number of processes per coordinate direction (MPI_Dims_create). [2_ring](2_ring)
