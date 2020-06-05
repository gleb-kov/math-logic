#include <iostream>
#include <vector>

#include "parser/lib.h"
#include "proof/lib.h"

int main() {
    std::string head = "A -> A & B";
    //getline(std::cin, head);
    NGrammar::expr formula = TParser().parse(head);

    std::unordered_set<NGrammar::expr> s1;
    auto s2 = s1;

    std::cout << formula->depth() << ' ' << possible_prove(formula, s1, s2);
    return 0;
}
