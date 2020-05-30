COMPILE=g++ -std=c++17 -O2 -flto

grammar=grammar/grammar.h grammar/expression.h grammar/expression.cpp grammar/proof.h grammar/proof.cpp grammar/lib.h
parser=parser/parser.h parser/parser.cpp parser/proof_parser.h parser/proof_parser.cpp parser/errors.h

all:
	$(COMPILE) $(grammar) $(parser) task2_minimize.cpp -o task2.out

run:
	./task2.out
