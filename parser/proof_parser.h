#ifndef MATLOG_PROOF_PARSER_H
#define MATLOG_PROOF_PARSER_H

#include <ostream>
#include <string>
#include <vector>

#include "../grammar/lib.h"
#include "../proof/lib.h"
#include "../parser/parser.h"
#include "errors.h"

class TProofParser {
private:
    using expr = NGrammar::expr;
    using context = NGrammar::context;

private:
    context head;
    TExprList proof;
    TParser parser;

    // TODO: replace with TProof
    // hypothesis, axiom or modus ponens
    std::vector<std::pair<size_t, uint64_t>> proof_state;
    // connected expr's in proof
    std::vector<std::vector<size_t>> proof_dependency;
    std::vector<size_t> renumeration;

public:
    TProofParser() = delete;

    TProofParser(std::string &statement, std::vector<std::string> &proof_body, bool verbose = false);

    [[deprecated]] void minimize();

    friend std::ostream &operator<<(std::ostream &, TProofParser &);

private:
    [[noreturn]] static void error(bool verbose) noexcept(false);

    [[noreturn]] static void error(bool verbose, size_t) noexcept(false);

    [[deprecated]] void print(std::ostream &);
};

#endif //MATLOG_PROOF_PARSER_H
