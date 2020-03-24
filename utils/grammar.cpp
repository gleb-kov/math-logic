#include <cassert>

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

TUnaryOperation::TUnaryOperation(EOperation const &sign, NGrammar::expr op)
        : sign(sign), operand(std::move(op)) {
    assert(NGrammar::is_unary(sign));
}

std::string TUnaryOperation::to_suffix() const {
    return '(' + sign.to_string() + operand->to_suffix() + ')';
}

std::string TUnaryOperation::to_string() const {
    return sign.to_string() + operand->to_string();
}

TBinaryOperation::TBinaryOperation(EOperation const &sign, NGrammar::expr lhs, NGrammar::expr rhs)
        : sign(sign), lhs(std::move(lhs)), rhs(std::move(rhs)) {
    assert(NGrammar::is_binary(sign));
}

std::string TBinaryOperation::to_suffix() const {
    return '(' + sign.to_string() + ',' + lhs->to_suffix() + ',' + rhs->to_suffix() + ')';
}

std::string TBinaryOperation::to_string() const {
    return '(' + lhs->to_string() + ' ' + sign.to_string() + ' ' + rhs->to_string() + ')';
}

TVariable::TVariable(std::string const &name) : name(name) {}

TVariable::TVariable(std::string &&name) : name(std::move(name)) {}

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

TContext::TContext() : sign(EOperation::Turnstile), separator(EToken::Comma) {}

void TContext::add_hypothesis(NGrammar::expr const &hyp) {
    size_t pos = size() + 1;
    hyp_size++;
    table[hyp->get_hash()] = pos;
    hypothesis.emplace_back(hyp);
}

void TContext::set_statement(NGrammar::expr const &res) {
    result = res;
}

size_t TContext::get_hypothesis(NGrammar::expr const &hyp) {
    auto pos = table.find(hyp->get_hash());
    return (pos == table.end() ? 0 : pos->second);
}

bool TContext::has_hypothesis(NGrammar::expr const &hyp) {
    return table.find(hyp->get_hash()) != table.end();
}

size_t TContext::size() const {
    return hyp_size;
}

std::string TContext::to_suffix() {
    return to_string();
}

std::string TContext::to_string() {
    std::string res;
    for (size_t i = 0; i < hypothesis.size(); i++) {
        res += hypothesis[i]->to_string();
        if (i + 1 < hypothesis.size()) {
            res += NGrammar::to_string(separator);
        }
        res += NGrammar::to_string(EToken::Space);
    }
    res += sign.to_string() + NGrammar::to_string(EToken::Space);
    res += result->to_string();
    return res;
}

std::ostream &operator<<(std::ostream &s, TNode &e) {
    return s << e.to_string();
}

std::ostream &operator<<(std::ostream &s, TContext &e) {
    s << e.to_string();
    return s;
}
