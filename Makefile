COMPILE=g++ -std=c++17 -O3

grammar=grammar/grammar.h grammar/grammar.cpp grammar/expression.h grammar/expression.cpp grammar/proof.h grammar/proof.cpp grammar/lib.h
parser=parser/parser.h parser/parser.cpp parser/parser_error.h
proof=proof/proof_parser.h proof/proof_parser.cpp

all: 
	$(COMPILE) $(grammar) $(parser) task1_parse.cpp -o task1.out
	$(COMPILE) $(grammar) $(parser) $(proof) task2_minimize.cpp -o task2.out

run:
	./task1.out
