#include <iostream>
#include <vector>

#include "proof/proof_parser.h"

int main() {
    // test.cpp
    // tests parse context

    std::string head;
    std::string step;
    getline(std::cin, head);
    std::vector<std::string> body;
    while (std::cin >> step) {
        body.push_back(step);
    }
    TProofParser solver(head, body);
    std::cout << solver;
    return 0;
}
