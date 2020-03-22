all: 
	g++ -std=c++17 -O3 utils/grammar.h utils/grammar.cpp parser/parser.h parser/parser.cpp task1_parse.cpp -o task1.out
	g++ -std=c++17 -O3 utils/grammar.h utils/grammar.cpp parser/parser.h parser/parser.cpp proof/proof_parser.h proof/proof_parser.cpp task2_minimize.cpp -o task2.out

run:
	./task1.out
