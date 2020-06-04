COMPILE=g++ -std=c++17 -O2 -flto

grammar=grammar/*
parser=parser/*
proof=proof/*

all:
	$(COMPILE) $(grammar) $(parser) $(proof) task2_minimize.cpp -o task2.out

run:
	./task2.out
