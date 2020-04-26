#include <cassert>

#include "expression.h"

using namespace NGrammar;

size_t TNode::calc_hash() const {
    return std::hash<std::string>{}(to_string());
}

size_t TNode::get_hash() const {
    return calc_hash();
}

bool TNode::is_unary() const {
    return false;
}

bool TNode::is_binary() const {
    return false;
}

bool TNode::is_variable() const {
    return false;
}

bool TNode::check_sign(EOperation) {
    return false;
}

TUnaryOperation::TUnaryOperation(EOperation const &sign, expr op)
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

expr TUnaryOperation::get_operand() const {
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

TBinaryOperation::TBinaryOperation(EOperation const &sign, expr lhs, expr rhs)
        : sign(sign), lhs(std::move(lhs)), rhs(std::move(rhs)) {
    assert(NGrammar::is_binary(sign));
    hash = calc_hash();
}

std::string TBinaryOperation::to_suffix() const {
    return LEFT_BRACE + sign.to_string() + SEPARATOR + lhs->to_suffix() + SEPARATOR + rhs->to_suffix() + RIGHT_BRACE;
}

std::string TBinaryOperation::to_string() const {
    return LEFT_BRACE + lhs->to_string() + SPACE + sign.to_string() + SPACE + rhs->to_string() + RIGHT_BRACE;
}

expr TBinaryOperation::get_lhs() const {
    return lhs;
}

expr TBinaryOperation::get_rhs() const {
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

unary_expr NGrammar::to_unary(expr const &e) {
    return std::dynamic_pointer_cast<TUnaryOperation>(e);
}

binary_expr NGrammar::to_binary(expr const &e) {
    return std::dynamic_pointer_cast<TBinaryOperation>(e);
}

var_expr NGrammar::to_variable(expr const &e) {
    return std::dynamic_pointer_cast<TVariable>(e);
}

uint64_t NGrammar::check_axiom(expr const &e) {
    if (!e->check_sign(EOperation::Implication)) {
        return 0;
    }
    binary_expr impl = to_binary(e);
    auto lhs = impl->get_lhs();
    auto rhs = impl->get_rhs();
    if (rhs->check_sign(EOperation::Implication) && to_binary(rhs)->get_rhs() == lhs) {
        return 1;
    }
    if (rhs->check_sign(EOperation::Implication) && to_binary(rhs)->get_rhs()->check_sign(EOperation::Conjunction)) {
        auto tt = to_binary(to_binary(rhs)->get_rhs());
        if (tt->get_lhs() == lhs && tt->get_rhs() == to_binary(rhs)->get_lhs()) {
            return 3;
        }
    }
    if (lhs->check_sign(EOperation::Conjunction)) {
        if (to_binary(lhs)->get_lhs() == rhs) {
            return 4;
        }
        if (to_binary(lhs)->get_rhs() == rhs) {
            return 5;
        }
    }
    if (rhs->check_sign(EOperation::Disjunction)) {
        if (to_binary(rhs)->get_lhs() == lhs) {
            return 6;
        }
        if (to_binary(rhs)->get_rhs() == lhs) {
            return 7;
        }
    }

    if (lhs->check_sign(EOperation::Implication) &&
        rhs->check_sign(EOperation::Implication) &&
        to_binary(rhs)->get_lhs()->check_sign(EOperation::Implication)) {
        auto lrhs = to_binary(rhs)->get_lhs();
        auto rrhs = to_binary(rhs)->get_rhs();
        auto rlrhs = to_binary(lrhs)->get_rhs();

        auto l1 = to_binary(lhs)->get_lhs();
        auto l2 = to_binary(lhs)->get_rhs();

        if (rrhs->check_sign(EOperation::Implication)) {
            auto lrrhs = to_binary(rrhs)->get_lhs();
            auto rrrhs = to_binary(rrhs)->get_rhs();
            if (rlrhs->check_sign(EOperation::Implication) &&
                l1 == lrrhs &&
                l1 == to_binary(lrhs)->get_lhs() &&
                l2 == to_binary(rlrhs)->get_lhs() &&
                rrrhs == to_binary(rlrhs)->get_rhs()) {
                return 2;
            }
            if (l2 == rlrhs &&
                l2 == rrrhs &&
                lrrhs->check_sign(EOperation::Disjunction) &&
                l1 == to_binary(lrrhs)->get_lhs() &&
                to_binary(lrhs)->get_lhs() == to_binary(lrrhs)->get_rhs()) {
                return 8;
            }
        }
        if (rrhs->check_sign(EOperation::Negation)) {
            auto a = to_unary(rrhs)->get_operand();
            if (rlrhs->check_sign(EOperation::Negation) &&
                l2 == to_unary(rlrhs)->get_operand() &&
                a == l1 &&
                a == to_binary(lrhs)->get_lhs()) {
                return 9;
            }
        }
    }
    if (lhs->is_unary()) {
        auto llhs = to_unary(lhs)->get_operand();
        if (lhs->check_sign(EOperation::Negation) &&
            llhs->check_sign(EOperation::Negation) &&
            to_unary(llhs)->get_operand() == rhs) {
            return 10;
        }
    }
    return 0;
}

bool NGrammar::is_axiom(expr const &e) {
    return check_axiom(e) != 0;
}

std::ostream &operator<<(std::ostream &s, TNode &e) {
    return s << e.to_string();
}
