#include <iostream>
#include <vector>
#include <fstream>

#include "proof/proof_parser.h"
#include "parser/parser_error.h"

/*
 * TODO:
 * structure for hashable expr: add modus ponens helper
 * check modus ponens
 *
 * check axiom 2,8,9
 * tnode funct to cpp
 * assoc string variable to it pointer while parsing
 */

int main() {
    std::ifstream fin("input.txt");

    std::string head;
    std::string step;
    getline(fin, head);
    std::vector<std::string> body;
    while (getline(fin, step)) {
        body.push_back(step);
    }
    try {
        TProofParser solver(head, body);
        std::cout << solver;
    } catch (parser_error const &error) {
        std::cout << error.what();
    } catch (...) {
        std::cerr << "Undefined exception";
    }

    /*std::shared_ptr<TVariable> tmp = std::make_shared<TVariable>(std::string("hello"));
    std::shared_ptr<TVariable> tmp2 = std::make_shared<TVariable>(std::string("hello"));
    std::cout << tmp->to_string();
    std::cout << tmp2->to_string();
    std::cout << (tmp == tmp2);*/
    return 0;
}
