all: first second third fourth

first:
	gcc -E test.c -o test.i

second:
	gcc -S test.i

third:
	gcc -c test.s

fourth:
	gcc test.o -o test

clean:
	rm -rf test test.i test.o test.s