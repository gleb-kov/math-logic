#include "grammar.h"

uint64_t NGrammar::check_axiom(NGrammar::expr const &e) {
    return 0;
}

bool NGrammar::is_axiom(NGrammar::expr const &e) {
    return check_axiom(e) != 0;
}

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

EOperation TOperation::get_sign() const {
    return sign;
}
