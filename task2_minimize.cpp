#include <iostream>
#include <vector>

#include "parser/lib.h"

int main() {
    // std::ifstream fin("input.txt");

    std::string head;
    std::string step;
    getline(std::cin, head);
    std::vector<std::string> body;
    while (getline(std::cin, step)) {
        body.emplace_back(step);
    }
    try {
        TProofParser solver;
        auto proof = solver.parse(head, body).release();
        proof->minimize_body();
        std::cout << *proof;
    } catch (parser_error const &pae) {
        std::cout << pae.what();
    } catch (proof_error const &pre) {
        std::cout << pre.what();
    }
    return 0;
}
