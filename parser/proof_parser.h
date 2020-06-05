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
    using proof_ptr = std::unique_ptr<TProof>;

private:
    context head;
    TExprList body;
    TParser parser;
    TProof result;

public:
    //TProofParser() = delete;

    proof_ptr parse(std::string &statement, std::vector<std::string> &proof_body, bool verbose = false);

private:
    [[noreturn]] static void error(bool verbose) noexcept(false);

    [[noreturn]] static void error(bool verbose, size_t) noexcept(false);
};

#endif //MATLOG_PROOF_PARSER_H
