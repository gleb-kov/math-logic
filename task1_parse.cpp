#include <iostream>

#include "parser/parser.h"

bool test() {
    TParser solver;
    std::string t1 = "!A&!B->!(A|B)";
    std::string r1 = "(->,(&,(!A),(!B)),(!(|,A,B)))";
    std::string t2 = "P1'->!QQ->!R10&S|!T&U&V";
    std::string r2 = "(->,P1',(->,(!QQ),(|,(&,(!R10),S),(&,(&,(!T),U),V))))";
    std::string t3 = "P1’->!QQ->!R10&S|!T&U&V";
    if (solver.parse(t1)->to_suffix() != r1) return false;
    solver.clear();
    if (solver.parse(t2)->to_suffix() != r2) return false;
    solver.clear();
    try {
        NGrammar::expr t = solver.parse(t3);
        return false;
    } catch (...) {}
    return true;
}

void verdict() {
    if (!test()) {
        std::cerr << "FAILED";
    } else {
        std::cerr << "PASSED";
    }
}

int main() {
    //verdict();

    std::string s;
    getline(std::cin, s);
    TParser solver;
    std::cout << solver.parse(s)->to_suffix();
    return 0;
}
