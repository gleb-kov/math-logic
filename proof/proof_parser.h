#ifndef MATLOG_PROOF_PARSER_H
#define MATLOG_PROOF_PARSER_H

#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "../parser/parser.h"

class TProofParser {
private:
    std::string const head;
    TParser parser;
    std::vector<std::string> proof; // change to needed structure
    bool failed = false;

public:
    TProofParser(std::string const &statement, std::vector<std::string> const &proof_body);

    std::string get_statement() const;

    bool is_okay() const;

    bool is_failed() const;

    std::vector<std::string>::iterator begin();

    std::vector<std::string>::iterator end();
};

std::ostream &operator<<(std::ostream &s, TProofParser &);

#endif //MATLOG_PROOF_PARSER_H
