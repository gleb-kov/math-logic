#include <iostream>
#include <vector>

#include "parser/lib.h"
#include "proof/lib.h"

using namespace NGrammar;

int main() {
    std::string head = "A -> A & B";
    // getline(std::cin, head);

    expr formula = TParser().parse(head);

    expr vara = gen_variable("A");
    expr varb = gen_variable("B");
    expr varc = gen_variable("C");

    expr nvara = gen_negative(vara);
    expr nvarb = gen_negative(varb);
    expr nvarc = gen_negative(varc);

    TExprList init_ctx;
    init_ctx.add(vara);
    init_ctx.add(varb);

    std::cout << possible_prove(formula, init_ctx);
    return 0;
}
