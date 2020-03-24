#include <cassert>

#include "expression.h"

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

size_t TUnaryOperation::get_hash() const {
    return hash;
}

bool TUnaryOperation::is_operation(EOperation cmp) {
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

size_t TBinaryOperation::get_hash() const {
    return hash;
}

bool TBinaryOperation::is_operation(EOperation cmp) {
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

bool TVariable::good_character(char c) {
    return good_first_characher(c) || c == '\'' || ('0' <= c && c <= '9');
}

size_t TVariable::get_hash() const {
    return hash;
}

std::ostream &operator<<(std::ostream &s, TNode &e) {
    return s << e.to_string();
}
