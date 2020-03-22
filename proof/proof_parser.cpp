#include "proof_parser.h"

TProofParser::TProofParser(std::string const &statement, std::vector<std::string> const &proof_body) : head(statement) {
    proof = proof_body;
}

std::string TProofParser::get_statement() const {
    return head;
}

bool TProofParser::is_okay() const {
    return !failed;
}

bool TProofParser::is_failed() const {
    return failed;
}

std::vector<std::string>::iterator TProofParser::begin() {
    return proof.begin();
}

std::vector<std::string>::iterator TProofParser::end() {
    return proof.end();
}

std::ostream &operator<<(std::ostream &s, TProofParser &solver) {
    if (solver.is_failed()) {
        s << std::string("Proof is incorrect") << std::endl;
    } else {
        s << solver.get_statement() << std::endl;
        for (auto it = solver.begin(); it != solver.end(); it++) {
            s << *it << std::endl;
        }
    }
    return s;
}