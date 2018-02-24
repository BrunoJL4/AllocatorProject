all: alloc

alloc: alloc.h
	gcc -g -o alloc alloc.c

clean:
	rm -f alloc *.o