#include <cassert>
#include <queue>

#include "proof_parser.h"

TProofParser::TProofParser(std::string &statement, std::vector<std::string> &proof_body, bool verbose) {
    if (proof_body.empty()) {
        error(verbose);
    }
    head = parser.parse_context(statement);
    parser.clear();
    for (size_t i = 0; i < proof_body.size(); i++) {
        auto state = parser.parse(proof_body[i]);
        parser.clear();

        uint64_t scheme_num = 0;

        if (i + 1 < proof_body.size() && proof.contains(state)) continue;

        if (head->has_hypothesis(state)) {
            uint64_t num = head->get_hypothesis(state);
            proof_state.emplace_back(0, num);
            proof_dependency.emplace_back();
        } else if ((scheme_num = NGrammar::check_axiom_scheme(state)) != 0) {
            proof_state.emplace_back(1, scheme_num);
            proof_dependency.emplace_back();
        } else {
            std::pair<size_t, size_t> mp = NProof::check_modus_ponens(proof, state);
            if (mp.first == 0 || mp.second == 0) {
                error(verbose);
            }
            proof_state.emplace_back(2, 0);
            proof_dependency.push_back({mp.first, mp.second});
        }
        proof.add(state);
    }

    if (proof.back() != head->get_statement()) {
        error(verbose);
    }
}

NGrammar::context TProofParser::get_context() const {
    return head;
}

size_t TProofParser::proof_size() const {
    return proof.size();
}

void TProofParser::minimize() {
    size_t last = proof.size();
    renumeration.assign(last + 1, 0);
    std::queue<size_t> dep({last});
    renumeration[last] = 1;
    while (!dep.empty()) {
        size_t cur = dep.front();
        dep.pop();
        for (size_t sub : proof_dependency[cur - 1]) {
            if (renumeration[sub] == 0) {
                renumeration[sub] = 1;
                dep.push(sub);
            }
        }
    }
    size_t cnt = 0;
    for (size_t i = 1; i < renumeration.size(); i++) {
        cnt += renumeration[i];
        if (renumeration[i]) renumeration[i] = cnt;
    }
}

void TProofParser::print(std::ostream &s) {
    s << head->to_string() << std::endl;
    for (size_t i = 0; i < proof.size(); i++) {
        if (renumeration[i + 1] == 0) continue;
        s << '[' << renumeration[i + 1] << ". ";
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
                s << "M.P. " << renumeration[proof_dependency[i][0]] << ", " << renumeration[proof_dependency[i][1]];
                break;
            }
            default: {
                throw std::runtime_error("Undefined origin of statement.");
            }
        }
        s << "] " << proof[i + 1]->to_string() << std::endl;
    }
}

void TProofParser::error(bool verbose) {
    throw proof_error(verbose);
}

void TProofParser::error(bool verbose, size_t n) {
    generate_proof_error(verbose, n);
}

std::ostream &operator<<(std::ostream &s, TProofParser &solver) {
    solver.print(s);
    return s;
}
