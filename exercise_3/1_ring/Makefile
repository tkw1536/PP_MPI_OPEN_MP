all: ring.c
	mkdir -p dest
	gcc $(shell mpicc --showme:link) -o dest/ring ring.c
