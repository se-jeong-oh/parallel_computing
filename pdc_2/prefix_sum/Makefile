prefix_sum : pdc_2_2.o
	mpicc -o prefix_sum pdc_2_2.o

pdc_2_2.o : pdc_2_2.c
	mpicc -c -o pdc_2_2.o pdc_2_2.c

clean :
	rm *.o prefix_sum