#include <cassert>
#include <queue>

#include "proof_parser.h"

namespace {
    using expr = NGrammar::expr;
    using context = NGrammar::context;
    using proof_ptr = NProof::proof;

    [[noreturn]] void error(bool verbose) noexcept(false) {
        throw proof_error(verbose);
    }

    [[noreturn]] void error(bool verbose, size_t n) noexcept(false) {
        generate_proof_error(verbose, n);
    }
}

proof_ptr NProofParser::parse(std::string &statement, std::vector<std::string> &proof_body, bool verbose) {
    if (proof_body.empty()) {
        error(verbose);
    }

    TExprList body;
    TParser parser;
    std::unique_ptr<TProof> result = std::make_unique<TProof>();
    context head = parser.parse_context(statement);
    parser.clear();
    result->set_context(head);

    for (size_t i = 0; i < proof_body.size(); i++) {
        uint64_t scheme_num = 0;
        auto state = parser.parse(proof_body[i]);
        parser.clear();
        if (i + 1 < proof_body.size() && body.contains(state)) {
            continue;
        }

        if (head->has_hypothesis(state)) {
            size_t num = head->get_hypothesis(state);
            result->add_state<THypothesis>(num, state);
        } else if ((scheme_num = NGrammar::check_axiom_scheme(state)) != 0) {
            result->add_state<TAxiomScheme>(scheme_num, state);
        } else {
            std::pair<size_t, size_t> mp = NProof::check_modus_ponens(body, state);
            if (mp.first == 0 || mp.second == 0) {
                error(verbose);
            }
            result->add_state<TModusPonens>(mp.first, mp.second, state);
        }
        body.add(state);
    }
    if (body.back() != head->get_statement()) {
        error(verbose);
    }
    return result;
}
