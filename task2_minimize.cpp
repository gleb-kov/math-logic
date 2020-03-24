#include <iostream>
#include <vector>
#include <fstream>

#include "proof/proof_parser.h"

/*
 * TODO:
 * structure for hashable expr
 * put it in context and proof parser
 *
 * do not recalc hash for nodes
 * check axiom
 * check modus ponens
 */

int main() {
    std::ifstream fin("input.txt");
    
    std::string head;
    std::string step;
    getline(fin, head);
    std::vector<std::string> body;
    while (fin >> step) {
        body.push_back(step);
    }
    try {
        TProofParser solver(head, body);
        std::cout << solver;
    } catch (std::runtime_error const & error) {
        std::cout << error.what();
    } catch (...) {
        std::cerr << "Undefined exception";
    }
    /*TParser solver;
    std::string a = "C";
    std::string a2 = "B'";
    auto t1 = solver.parse(a)->get_hash();
    solver.clear();
    auto t2 = solver.parse(a2)->get_hash();
    std::cout << t1 << " " << t2;
    std::cout << std::hash<std::string>{}(a) << " ";
    std::cout << std::hash<std::string>{}(a2);*/
    return 0;
}
