#include "proof_parser.h"

TProofParser::TProofParser(std::string const &statement, std::vector<std::string> const &proof_body) : head(statement) {

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

std::ostream &operator<<(std::ostream &s, TProofParser &a) {
    if (a.is_failed()) {
        return s << std::string("Proof is incorrect") << std::endl;
    } else {
        return s << a.get_statement() << std::endl;
    }
}