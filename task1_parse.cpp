#include <iostream>

#include "parser/parser.h"

int main() {
    std::string s;
    std::cin >> s;
    std::cout << TParser(s).get_result()->to_string();
    return 0;
}
