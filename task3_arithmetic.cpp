#include <iostream>
#include <vector>

#include "parser/proof_parser.h"
#include "parser/errors.h"

int main() {
    std::string head;
    std::string step;
    getline(std::cin, head);
    std::vector<std::string> body;
    while (getline(std::cin, step)) {
        body.emplace_back(step);
    }
    try {
        TProofParser solver(head, body, true);
        std::cout << solver;
    } catch (parser_error const &pae) {
        std::cout << pae.what();
    } catch (proof_error const &pre) {
        std::cout << pre.what();
    }
    return 0;
}
