all: test clean

run:
	g++ -o sequential.out sequential.cpp functions.h branch.h parser.h point.h
	./sequential.out

clean:
	rm -f *.bin *.txt *.blif *.out *~

.PHONY: all clean