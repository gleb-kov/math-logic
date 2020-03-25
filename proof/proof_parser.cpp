#include <cassert>

#include "proof_parser.h"

TProofParser::TProofParser(std::string &statement, std::vector<std::string> &proof_body) {
    head = parser.parse_context(statement);
    parser.clear();
    for (auto &it : proof_body) {
        auto state = parser.parse(it);
        proof.add(state);
        parser.clear();
        if (head->has_hypothesis(state)) {
            uint64_t num = head->get_hypothesis(state);
            proof_state.emplace_back(0, num);
            proof_dependency.emplace_back();
        } else if (NGrammar::is_axiom(state)) {
            uint64_t num = NGrammar::check_axiom(state);
            proof_state.emplace_back(1, num);
            proof_dependency.emplace_back();
        } else {
            std::pair<size_t, size_t> mp = modus_ponens(state);
            //if (mp.first == 0 || mp.second == 0) {
            //    throw parser_error("Proof is incorrect");
            //}
            proof_state.emplace_back(2, 0);
            proof_dependency.push_back({mp.first, mp.second});
        }
    }
    assert(proof_body.size() == proof.size());
    assert(proof_state.size() == proof.size());
    assert(proof_dependency.size() == proof.size());
}

NGrammar::context TProofParser::get_statement() const {
    return head;
}

std::pair<size_t, size_t> TProofParser::modus_ponens(NGrammar::expr const &e) {
    return {0, 0};
}

void TProofParser::print(std::ostream &s) {
    s << head->to_string() << std::endl;
    for (size_t i = 0; i < proof.size(); i++) {
        s << '[' << i + 1 << ". ";
        switch (proof_state[i].first) {
            case 0: {
                s << "Hypothesis " << proof_state[i].second;
                break;
            }
            case 1: {
                s << "Ax. sch. " << proof_state[i].second;
                break;
            }
            case 2: {
                s << "M.P. " << proof_dependency[i][0] << " " << proof_dependency[i][1];
                break;
            }
            default: {
                throw parser_error("Undefined origin of statement.");
            }
        }
        s << "] " << proof[i]->to_string() << std::endl;
    }
}

std::vector<NGrammar::expr>::iterator TProofParser::begin() {
    return proof.begin();
}

std::vector<NGrammar::expr>::iterator TProofParser::end() {
    return proof.end();
}

std::ostream &operator<<(std::ostream &s, TProofParser &solver) {
    solver.print(s);
    return s;
}
