#ifndef MATLOG_AUTO_PROVE_H
#define MATLOG_AUTO_PROVE_H

#include <unordered_set>
#include <iostream>

#include "../grammar/lib.h"
#include "structures.h"

bool possible_prove(NGrammar::expr &e, TExprList &context);

#endif //MATLOG_AUTO_PROVE_H
