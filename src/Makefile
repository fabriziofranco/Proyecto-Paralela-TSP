all: test clean

test_parser:
	g++ -o test_parser.out parser.cpp point.cpp
	./test_parser.out  $(N)


clean:
	rm -f *.bin *.txt *.blif *.out *~

.PHONY: all clean