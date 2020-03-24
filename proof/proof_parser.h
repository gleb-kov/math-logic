#ifndef MATLOG_PROOF_PARSER_H
#define MATLOG_PROOF_PARSER_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../parser/parser.h"
#include "../parser/parser_error.h"

class TProofParser {
private:
    using expr = NGrammar::expr;
    using context = NGrammar::context;

private:
    context head;
    TParser parser;
    TExprList proof;
    // hypothesis, axiom or modus ponens
    std::vector<std::pair<size_t, uint64_t>> proof_state;
    // connected expr in proof
    std::vector<std::vector<size_t>> proof_dependency;

public:
    TProofParser(std::string &statement, std::vector<std::string> &proof_body);

    context get_statement() const;

    std::pair<size_t, size_t> modus_ponens(expr const &);

    void print(std::ostream &s);

    [[deprecated]] std::vector<expr>::iterator begin();

    [[deprecated]] std::vector<expr>::iterator end();
};

std::ostream &operator<<(std::ostream &s, TProofParser &);

#endif //MATLOG_PROOF_PARSER_H
