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
