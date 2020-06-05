#ifndef MATLOG_AUTO_PROVE_H
#define MATLOG_AUTO_PROVE_H

#include <unordered_set>

#include "../grammar/lib.h"

bool possible_prove(NGrammar::expr e,
                    std::unordered_set<NGrammar::expr> &neg,
                    std::unordered_set<NGrammar::expr> &pos);

#endif //MATLOG_AUTO_PROVE_H
