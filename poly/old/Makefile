GCC_OPT=-g -Wall


all: test_poly_creux


test_poly_creux: test_poly_creux.o poly_creux.o
	gcc $(GCC_OPT) -o test_poly_creux test_poly_creux.o poly_creux.o
	rm -f *.o

test_poly_creux.o: test_poly_creux.c poly_creux.h
	gcc $(GCC_OPT) -c test_poly_creux.c

poly_creux.o: poly_creux.c poly_creux.h
	gcc $(GCC_OPT) -c poly_creux.c


clean:
	rm -f test_poly_creux *.o
