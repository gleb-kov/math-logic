#include <iostream>
#include <algorithm>
#include <memory>

#include "proof/proof_parser.h"

int main() {
    std::string s;
    std::cin >> s;
    TProofParser solver(s, {});
    std::cout << solver;
    return 0;
}
