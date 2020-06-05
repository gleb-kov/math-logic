#ifndef MATLOG_PROOF_PARSER_H
#define MATLOG_PROOF_PARSER_H

#include <string>
#include <vector>

#include "../grammar/lib.h"
#include "../proof/lib.h"
#include "../parser/parser.h"
#include "errors.h"

namespace NProofParser {
    using namespace NProof;

    proof parse(std::string &statement, std::vector<std::string> &proof_body, bool verbose = false);
}

#endif //MATLOG_PROOF_PARSER_H