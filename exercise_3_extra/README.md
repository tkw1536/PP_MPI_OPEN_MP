# Extra exercise (Collective Comm.)

* Write a program in which the process with rank 0 broadcasts a message via MPI_COMM_WORLD and then waits for every other process to send back that message. [0_extra](0_extra)

* Write a program in which the process with rank 0 scatters a message to all processes via MPI_COMM_WORLD and then gathers back that message. How do the execution times of this program and the previous one compare? [1_extra](1_extra)
  * this program is slower than the first one. 
