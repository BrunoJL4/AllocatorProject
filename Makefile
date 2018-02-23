all: alloc

alloc: alloc.h
	gcc -o alloc alloc.c

clean:
	rm -f alloc *.o