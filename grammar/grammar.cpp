#include "grammar.h"

#include <algorithm>

bool NGrammar::is_binary(EOperation sign) {
    return std::find(BINARY.begin(), BINARY.end(), sign) != BINARY.end();
}

bool NGrammar::is_unary(EOperation sign) {
    return std::find(UNARY.begin(), UNARY.end(), sign) != UNARY.end();
}

bool NGrammar::is_skippable(EToken sign) {
    return std::find(SKIPPABLE.begin(), SKIPPABLE.end(), sign) != SKIPPABLE.end();
}

bool NGrammar::is_hidden(EToken sign) {
    return std::find(HIDDEN.begin(), HIDDEN.end(), sign) != HIDDEN.end();
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
            throw std::runtime_error("unsupported token");
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
            return "\r";
        default:
            throw std::runtime_error("unsupported token");
    }
}

TOperation::TOperation(EOperation sign) : sign(sign) {}

std::string TOperation::to_string() const {
    return NGrammar::to_string(sign);
}

EOperation TOperation::get_sign() const {
    return sign;
}
