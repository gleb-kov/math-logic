#include <iostream>
#include <algorithm>
#include <memory>

#include "parser/parser.h"

int main() {
    std::string s;
    std::cin >> s;
    std::cout << TParser(s).get_result()->suffix_print();
    return 0;
}
