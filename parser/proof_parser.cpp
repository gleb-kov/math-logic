#include <cassert>

#include "proof_parser.h"

TProofParser::TProofParser(std::string &statement, std::vector<std::string> &proof_body) {
    if (proof_body.empty()) {
        throw parser_error("Proof is incorrect");
    }
    head = parser.parse_context(statement);
    parser.clear();
    for (size_t i = 0; i < proof_body.size(); i++) {
        auto state = parser.parse(proof_body[i]);
        parser.clear();
        if (i + 1 < proof_body.size() && proof.contains(state)) continue;
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
            if (mp.first == 0 || mp.second == 0) {
                throw parser_error("Proof is incorrect");
            }
            proof_state.emplace_back(2, 0);
            proof_dependency.push_back({mp.first, mp.second});
        }
        proof.add(state);
    }
    size_t last = proof.size();

    assert(last == proof_state.size());
    assert(last == proof_dependency.size());

    if (proof[last] != head->get_statement()) {
        throw parser_error("Proof is incorrect");
    }

    // minimize block
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

NGrammar::context TProofParser::get_context() const {
    return head;
}

std::pair<size_t, size_t> TProofParser::modus_ponens(NGrammar::expr const &e) {
    for (auto it = proof.rev_impl_begin(e); it != proof.rev_impl_end(e); it++) {
        size_t rhs_ind = *it;
        auto rhs = proof[rhs_ind];
        auto needed_lhs = NGrammar::to_binary(rhs)->get_lhs();
        size_t lhs_ind = proof.get_index(needed_lhs);
        if (lhs_ind) return {rhs_ind, lhs_ind};
    }
    return {0, 0};
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

std::ostream &operator<<(std::ostream &s, TProofParser &solver) {
    solver.print(s);
    return s;
}
