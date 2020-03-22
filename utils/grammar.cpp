#include "grammar.h"

std::string NGrammar::to_string(EOperation sign) {
    switch (sign) {
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

TUnaryOperation::TUnaryOperation(TOperation const &sign, NGrammar::expr op)
        : sign(sign), operand(std::move(op)) {}

std::string TUnaryOperation::suffix_print() {
    return '(' + sign.to_string() + operand->suffix_print() + ')';
}

TBinaryOperation::TBinaryOperation(TOperation const &sign, NGrammar::expr lhs, NGrammar::expr rhs)
        : sign(sign), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

std::string TBinaryOperation::suffix_print() {
    return '(' + sign.to_string() + ',' + lhs->suffix_print() + ',' + rhs->suffix_print() + ')';
}

TVariable::TVariable(std::string const &name) : name(name) {}

TVariable::TVariable(std::string &&name) : name(std::move(name)) {}

std::string TVariable::suffix_print() {
    return name;
}

bool TVariable::good_first_characher(char c) {
    return 'A' <= c && c <= 'Z';
}

bool TVariable::good_character(char c) {
    return good_first_characher(c) || c == '\'' || ('0' <= c && c <= '9');
}
