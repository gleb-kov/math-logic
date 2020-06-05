#include <cassert>
#include <queue>

#include "proof_parser.h"

std::unique_ptr<TProof>
TProofParser::parse(std::string &statement, std::vector<std::string> &proof_body, bool verbose) {
    if (proof_body.empty()) {
        error(verbose);
    }

    head = parser.parse_context(statement);
    result.set_context(head);

    parser.clear();

    for (size_t i = 0; i < proof_body.size(); i++) {
        auto state = parser.parse(proof_body[i]);
        parser.clear();

        uint64_t scheme_num = 0;

        if (i + 1 < proof_body.size() && body.contains(state)) continue;

        if (head->has_hypothesis(state)) {
            size_t num = head->get_hypothesis(state);
            result.add_state<THypothesis>(num, state);
        } else if ((scheme_num = NGrammar::check_axiom_scheme(state)) != 0) {
            result.add_state<TAxiomScheme>(scheme_num, state);
        } else {
            std::pair<size_t, size_t> mp = NProof::check_modus_ponens(body, state);
            if (mp.first == 0 || mp.second == 0) {
                error(verbose);
            }
            result.add_state<TModusPonens>(mp.first, mp.second, state);
        }
        body.add(state);
    }

    if (body.back() != head->get_statement()) {
        error(verbose);
    }
    return std::unique_ptr<TProof>(&result);
}

void TProofParser::error(bool verbose) {
    throw proof_error(verbose);
}

void TProofParser::error(bool verbose, size_t n) {
    generate_proof_error(verbose, n);
}