#include <iostream>
#include <vector>

#include "parser/proof_parser.h"
#include "parser/parser_error.h"

int main() {
    std::string head;
    std::string step;
    getline(std::cin, head);
    std::vector<std::string> body;
    while (getline(std::cin, step)) {
        body.emplace_back(step);
    }
    try {
        TProofParser solver(head, body);
        solver.minimize();
        std::cout << solver;
    } catch (parser_error const &error) {
        std::cout << error.what();
    }
    return 0;
}
