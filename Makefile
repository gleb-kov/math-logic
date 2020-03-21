all: 
	g++ -std=c++17 -O3 grammar.h parser.h parser.cpp main.cpp -o solution.out

run:
	./solution.out
