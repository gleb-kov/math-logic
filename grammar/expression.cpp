#include <cassert>
#include <iostream>

#include "expression.h"
#include "../parser/parser_error.h"

TUnaryOperation::TUnaryOperation(EOperation const &sign, NGrammar::expr op)
        : sign(sign), operand(std::move(op)) {
    assert(NGrammar::is_unary(sign));
    hash = calc_hash();
}

std::string TUnaryOperation::to_suffix() const {
    return '(' + sign.to_string() + operand->to_suffix() + ')';
}

std::string TUnaryOperation::to_string() const {
    return sign.to_string() + operand->to_string();
}

NGrammar::expr TUnaryOperation::get_operand() const {
    return operand;
}

size_t TUnaryOperation::get_hash() const {
    return hash;
}

bool TUnaryOperation::is_unary() const {
    return true;
}

bool TUnaryOperation::check_sign(EOperation cmp) {
    return sign.get_sign() == cmp;
}

TBinaryOperation::TBinaryOperation(EOperation const &sign, NGrammar::expr lhs, NGrammar::expr rhs)
        : sign(sign), lhs(std::move(lhs)), rhs(std::move(rhs)) {
    assert(NGrammar::is_binary(sign));
    hash = calc_hash();
}

std::string TBinaryOperation::to_suffix() const {
    return '(' + sign.to_string() + ',' + lhs->to_suffix() + ',' + rhs->to_suffix() + ')';
}

std::string TBinaryOperation::to_string() const {
    return '(' + lhs->to_string() + ' ' + sign.to_string() + ' ' + rhs->to_string() + ')';
}

NGrammar::expr TBinaryOperation::get_lhs() const {
    return lhs;
}

NGrammar::expr TBinaryOperation::get_rhs() const {
    return rhs;
}

size_t TBinaryOperation::get_hash() const {
    return hash;
}

bool TBinaryOperation::is_binary() const {
    return true;
}

bool TBinaryOperation::check_sign(EOperation cmp) {
    return sign.get_sign() == cmp;
}

TVariable::TVariable(std::string const &name) : name(name) {
    hash = calc_hash();
}

TVariable::TVariable(std::string &&name) : name(std::move(name)) {
    hash = calc_hash();
}

std::string TVariable::to_suffix() const {
    return name;
}

std::string TVariable::to_string() const {
    return name;
}

bool TVariable::good_first_characher(char c) {
    return 'A' <= c && c <= 'Z';
}

bool TVariable::is_variable() const {
    return true;
}

bool TVariable::good_character(char c) {
    return good_first_characher(c) || c == '\'' || ('0' <= c && c <= '9');
}

size_t TVariable::get_hash() const {
    return hash;
}

NGrammar::unary_expr NGrammar::to_unary(expr const &e) {
    return std::dynamic_pointer_cast<TUnaryOperation>(e);
}

NGrammar::binary_expr NGrammar::to_binary(expr const &e) {
    return std::dynamic_pointer_cast<TBinaryOperation>(e);
}

NGrammar::var_expr NGrammar::to_variable(expr const &e) {
    return std::dynamic_pointer_cast<TVariable>(e);
}

uint64_t NGrammar::check_axiom(NGrammar::expr const &e) {
    if (!e->is_binary() || !e->check_sign(EOperation::Implication)) {
        return 0;
    }
    binary_expr impl = to_binary(e);
    auto lhs = impl->get_lhs();
    auto rhs = impl->get_rhs();
    if (lhs->is_unary()) {
        auto llhs = to_unary(lhs)->get_operand();
        if (!lhs->check_sign(EOperation::Negation) || !llhs->check_sign(EOperation::Negation)) return 0;
        if (to_unary(llhs)->get_operand() == rhs) {
            return 10;
        }
        return 0;
    } else if (lhs->check_sign(EOperation::Conjunction)) {
        if (to_binary(lhs)->get_lhs() == rhs) {
            return 3;
        }
        if (to_binary(lhs)->get_rhs() == rhs) {
            return 4;
        }
    } else if (rhs->check_sign(EOperation::Disjunction)) {
        if (to_binary(rhs)->get_lhs() == lhs) {
            return 6;
        } else if (to_binary(rhs)->get_rhs() == lhs) {
            return 7;
        }
    } else if (rhs->check_sign(EOperation::Implication)) {
        if (to_binary(rhs)->get_rhs() == lhs) {
            return 1;
        } else if (to_binary(rhs)->get_rhs()->check_sign(EOperation::Conjunction)) {
            auto tt = to_binary(to_binary(rhs)->get_rhs());
            if (tt->get_lhs() == lhs && tt->get_rhs() == to_binary(rhs)->get_lhs()) {
                return 5;
            }
        }
    }
    return 0;
}

bool NGrammar::is_axiom(NGrammar::expr const &e) {
    return check_axiom(e) != 0;
}

std::ostream &operator<<(std::ostream &s, TNode &e) {
    return s << e.to_string();
}
