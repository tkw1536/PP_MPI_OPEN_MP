all: p2p.c
	mkdir -p dest
	gcc $(shell mpicc --showme:link) -o dest/p2p p2p.c
