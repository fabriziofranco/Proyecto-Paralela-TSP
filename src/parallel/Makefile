all: test clean

run:
	g++ -fopenmp -o parallel.out parallel.cpp functions.h branch.h parser.h point.h
	./parallel.out

clean:
	rm -f *.bin *.txt *.blif *.out *~

.PHONY: all clean