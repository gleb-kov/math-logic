#include "auto_prove.h"

namespace {
    bool is_neg_variable(NGrammar::expr const &e) {
        return (e->is_unary() &&
                e->check_sign(EOperation::Negation) &&
                NGrammar::to_unary(e)->get_operand()->is_variable());
    }
}

// TODO: double neg, 13
bool possible_prove(NGrammar::expr &e, TExprList &context) {
    std::cout << e->to_string() << ' ' << e->get_hash() << '\n';

    if (e->is_variable()) {
        bool verd = context.contains(e);
        std::cout << "DETECT" << verd << '\n';
        return verd;
    }
    if (is_neg_variable(e)) {
        return context.contains(NGrammar::to_unary(e)->get_operand());
    }

    if (e->is_binary()) {
        NGrammar::expr lhs = NGrammar::to_binary(e)->get_lhs();
        NGrammar::expr rhs = NGrammar::to_binary(e)->get_rhs();
        NGrammar::expr nle = std::make_shared<TUnaryOperation>(EOperation::Negation, lhs);
        NGrammar::expr nre = std::make_shared<TUnaryOperation>(EOperation::Negation, rhs);

        bool l = possible_prove(lhs, context);
        bool r = possible_prove(rhs, context);
        bool nl = possible_prove(lhs, context);
        bool nr = possible_prove(rhs, context);

        if (e->check_sign(EOperation::Conjunction)) {
            return l && r;
        } else if (e->check_sign(EOperation::Disjunction)) {
            if (l && r) return true;
            if (nl && r) return true;
            if (l && nr) return true;
            return false;
        } else if (e->check_sign(EOperation::Implication)) {
            // TODO: deduction

            if (l && r) return true;
            if (nl && r) return true;
            if (nl && nr) return true;
            return false;
        }
    }
    // TODO:
    if (e->is_unary() && e->check_sign(EOperation::Negation)) {
        return false;
    }
    return false;
}
