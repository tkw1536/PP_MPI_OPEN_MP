all: pingpong.c
	mkdir -p dest
	gcc $(shell mpicc --showme:link) -o dest/pingpong pingpong.c
