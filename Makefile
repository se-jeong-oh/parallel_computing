calc.out : calc.o
	gcc -o calc.out calc.o -lm
	rm -r *.o

calc.o : calc.h calc.c
	gcc -c -o calc.o calc.c -lm

clean:
	rm -r *.o
	rm -r *.out