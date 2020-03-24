#ifndef MATLOG_PROOF_PARSER_H
#define MATLOG_PROOF_PARSER_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../parser/parser.h"

class TProofParser {
private:
    using expr = NGrammar::expr;
    using context = NGrammar::context;

private:
    context head;
    TParser parser;
    std::vector<expr> proof;
    // hypothesis, axiom or modus ponens
    std::vector<std::pair<size_t, uint64_t>> proof_state;
    // connected expr in proof
    std::vector<std::vector<size_t>> proof_dependency;

public:
    TProofParser(std::string &statement, std::vector<std::string> &proof_body);

    context get_statement() const;

    std::pair<size_t, size_t> modus_ponens(expr const &);

    std::vector<expr>::iterator begin();

    std::vector<expr>::iterator end();

    void print(std::ostream &s) {
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
                    throw std::runtime_error("proof parser error");
                }
            }
            s << "] " << proof[i]->to_string() << std::endl;
        }
    }
};

std::ostream &operator<<(std::ostream &s, TProofParser &);

#endif //MATLOG_PROOF_PARSER_H
