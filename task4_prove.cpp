#include <iostream>
#include <vector>

#include "parser/lib.h"

int main() {
    std::string head;
    getline(std::cin, head);
    NGrammar::expr formula = TParser().parse(head);
    return 0;
}
