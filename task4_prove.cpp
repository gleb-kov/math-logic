#include <iostream>
#include <vector>

#include "parser/lib.h"

int main() {
    std::string head;
    getline(std::cin, head);
    TParser solver;
    NGrammar::expr formula = solver.parse(head);
    return 0;
}
