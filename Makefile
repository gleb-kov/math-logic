all: 
	g++ -std=c++17 -O3 utils/grammar.h utils/grammar.cpp parser/parser.h parser/parser.cpp task1_parse.cpp -o task1.out

run:
	./task1.out
