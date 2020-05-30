#ifndef MATLOG_PROOF_PARSER_H
#define MATLOG_PROOF_PARSER_H

#include <ostream>
#include <string>
#include <vector>

#include "../grammar/lib.h"
#include "../parser/parser.h"
#include "../parser/parser_error.h"

class TProofParser {
private:
    using expr = NGrammar::expr;
    using context = NGrammar::context;

private:
    context head;
    TExprList proof;
    TParser parser;
    // hypothesis, axiom or modus ponens
    std::vector<std::pair<size_t, uint64_t>> proof_state;
    // connected expr's in proof
    std::vector<std::vector<size_t>> proof_dependency;
    std::vector<size_t> renumeration;

public:
    TProofParser(std::string &statement, std::vector<std::string> &proof_body);

    context get_context() const;

    size_t proof_size() const;

    void minimize();

    void print(std::ostream &);

    [[noreturn]] void error() noexcept(false);
};

std::ostream &operator<<(std::ostream &s, TProofParser &);

#endif //MATLOG_PROOF_PARSER_H
