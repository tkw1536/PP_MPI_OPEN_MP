all: extra.c
	mkdir -p dest
	gcc $(shell mpicc --showme:link) -o dest/extra extra.c
