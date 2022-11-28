all: test clean

sequential:
	g++ -o sequential.out branch_bound.cpp functions.h branch.h parser.h point.h
	./sequential.out


clean:
	rm -f *.bin *.txt *.blif *.out *~

.PHONY: all clean