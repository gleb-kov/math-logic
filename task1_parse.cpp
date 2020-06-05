#include <iostream>

#include "parser/lib.h"

int main() {
    std::string s;
    getline(std::cin, s);
    std::cout << TParser().parse(s)->to_suffix();
    return 0;
}
