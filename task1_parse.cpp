#include <iostream>

#include "parser/parser.h"

int main() {
    std::string s;
    getline(std::cin, s);
    TParser solver;
    std::cout << solver.parse(s)->to_suffix();
    return 0;
}
