#include <cassert>

#include "grammar.h"

bool NGrammar::is_binary(EOperation sign) {
    for (EOperation s : BINARY_OPERATIONS) {
        if (s == sign) {
            return true;
        }
    }
    return false;
}

bool NGrammar::is_unary(EOperation sign) {
    for (EOperation s : UNARY_OPERATIONS) {
        if (s == sign) {
            return true;
        }
    }
    return false;
}

bool NGrammar::is_skippable(EToken sign) {
    for (EToken s : SKIPPABLE) {
        if (s == sign) {
            return true;
        }
    }
    return false;
}

bool NGrammar::is_hidden(EToken sign) {
    for (EToken s : HIDDEN_TOKEN) {
        if (s == sign) {
            return true;
        }
    }
    return false;
}

std::string NGrammar::to_string(EOperation sign) {
    switch (sign) {
        case EOperation::Turnstile:
            return "|-";
        case EOperation::Implication:
            return "->";
        case EOperation::Disjunction:
            return "|";
        case EOperation::Conjunction:
            return "&";
        case EOperation::Negation:
            return "!";
        default:
            return "error";
    }
}

std::string NGrammar::to_string(EToken sign) {
    switch (sign) {
        case EToken::Turnstile:
            return "|-";
        case EToken::Implication:
            return "->";
        case EToken::Disjunction:
            return "|";
        case EToken::Conjunction:
            return "&";
        case EToken::Negation:
            return "!";
        case EToken::LeftBrace:
            return "(";
        case EToken::RightBrace:
            return ")";
        case EToken::Comma:
            return ",";
        case EToken::Space:
            return " ";
        case EToken::Tab:
            return "\t";
        case EToken::NewLine:
            return "\n";
        case EToken::None:
            return "none";
        case EToken::Variable:
            return "variable";
        default:
            return "error";
    }
}

TOperation::TOperation(EOperation sign) : sign(sign) {}

std::string TOperation::to_string() const {
    return NGrammar::to_string(sign);
}

TUnaryOperation::TUnaryOperation(EOperation const &sign, NGrammar::expr op)
        : sign(sign), operand(std::move(op)) {
    assert(NGrammar::is_unary(sign));
}

std::string TUnaryOperation::to_suffix() {
    return '(' + sign.to_string() + operand->to_suffix() + ')';
}

std::string TUnaryOperation::to_string() {
    return sign.to_string() + operand->to_string();
}

TBinaryOperation::TBinaryOperation(EOperation const &sign, NGrammar::expr lhs, NGrammar::expr rhs)
        : sign(sign), lhs(std::move(lhs)), rhs(std::move(rhs)) {
    assert(NGrammar::is_binary(sign));
}

std::string TBinaryOperation::to_suffix() {
    return '(' + sign.to_string() + ',' + lhs->to_suffix() + ',' + rhs->to_suffix() + ')';
}

std::string TBinaryOperation::to_string() {
    return '(' + lhs->to_string() + ' ' + sign.to_string() + ' ' + rhs->to_string() + ')';
}

TVariable::TVariable(std::string const &name) : name(name) {}

TVariable::TVariable(std::string &&name) : name(std::move(name)) {}

std::string TVariable::to_suffix() {
    return name;
}

std::string TVariable::to_string() {
    return name;
}

bool TVariable::good_first_characher(char c) {
    return 'A' <= c && c <= 'Z';
}

bool TVariable::good_character(char c) {
    return good_first_characher(c) || c == '\'' || ('0' <= c && c <= '9');
}

TContext::TContext() : sign(EOperation::Turnstile) {}

void TContext::add_hypothesis(NGrammar::expr const &hyp) {
    hypothesis.emplace_back(hyp);
}

void TContext::set_statement(NGrammar::expr const &res) {
    result = res;
}

std::string TContext::to_suffix() {
    return "";
}

std::string TContext::to_string() {
    return "";
}

std::ostream &operator<<(std::ostream &s, TNode &e) {
    return s << e.to_string();
}

std::ostream &operator<<(std::ostream &s, TContext &e) {
    return s << e.to_string();
}
