GCC_OPT=-g -Wall



all: test_poly perf_poly test_poly_creux perf_poly_creux



perf_poly: perf_poly.o poly.o
	gcc $(GCC_OPT) -o perf_poly perf_poly.o poly.o

perf_poly.o: perf_poly.c poly.h
	gcc $(GCC_OPT) -c perf_poly.c


perf_poly_creux: perf_poly_creux.o poly_creux.o
	gcc $(GCC_OPT) -o perf_poly perf_poly_creux.o poly_creux.o

perf_poly_creux.o: perf_poly_creux.c poly_creux.h
	gcc $(GCC_OPT) -c perf_poly_creux.c



test_poly: test_poly.o poly.o
	gcc $(GCC_OPT) -o test_poly test_poly.o poly.o

test_poly.o: test_poly.c poly.h
	gcc $(GCC_OPT) -c test_poly.c

poly.o: poly.c poly.h
	gcc $(GCC_OPT) -c poly.c


test_poly_creux: test_poly_creux.o poly_creux.o
	gcc $(GCC_OPT) -o test_poly_creux test_poly_creux.o poly_creux.o

test_poly_creux.o: test_poly_creux.c poly_creux.h
	gcc $(GCC_OPT) -c test_poly_creux.c

poly_creux.o: poly_creux.c poly_creux.h
	gcc $(GCC_OPT) -c poly_creux.c



clean:
	rm -f test_poly perf_poly test_poly_creux perf_poly_creux *.o
