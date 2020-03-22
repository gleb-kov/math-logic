#include "parser.h"

TParser::expr TParser::parse(std::string &s) {
    return parse(s.begin(), s.end());
}

TParser::expr TParser::parse(std::string::iterator from, std::string::iterator to) {
    begin = from;
    end = to;
    if (begin < end) {
        next_token();
        return parse_impl();
    }
    return EMPTY;
}

TParser::expr TParser::parse_context(std::string &s) {
    return parse_context(s.begin(), s.end());
}

TParser::expr TParser::parse_context(std::string::iterator from, std::string::iterator to) {
    return EMPTY;
}

void TParser::clear() {
    token = EToken::None;
}

TParser::expr TParser::parse_impl() {
    expr cur = parse_dis();
    if (token == EToken::Implication) {
        next_token();
        cur = std::make_shared<TBinaryOperation>(EOperation::Implication, cur, parse_impl());
    }
    return cur;
}

TParser::expr TParser::parse_dis() {
    expr cur = parse_con();
    while (token == EToken::Disjunction) {
        next_token();
        cur = std::make_shared<TBinaryOperation>(EOperation::Disjunction, cur, parse_con());
    }
    return cur;
}

TParser::expr TParser::parse_con() {
    expr cur = parse_neg();
    while (token == EToken::Conjunction) {
        next_token();
        cur = std::make_shared<TBinaryOperation>(EOperation::Conjunction, cur, parse_neg());
    }
    return cur;
}

TParser::expr TParser::parse_neg() {
    expr cur;
    if (token == EToken::Negation) {
        next_token();
        cur = std::make_shared<TUnaryOperation>(EOperation::Negation, parse_neg());
    } else {
        if (token == EToken::LeftBrace) {
            next_token();
            cur = parse_impl();
        } else {
            cur = parse_var();
        }
        next_token();
    }
    return cur;
}

TParser::expr TParser::parse_var() {
    auto pos = begin;
    if (TVariable::good_first_characher(*pos)) {
        pos++;
        while (pos < end && TVariable::good_character(*pos)) pos++;
    }
    std::string::iterator tmp = begin;
    begin = pos;
    return std::make_shared<TVariable>(std::string(tmp, pos));
}

void TParser::next_token() {
    while (true) {
        token = starts_with();
        if (!NGrammar::is_skippable(token)) break;
    }
    token = starts_with();
    if (token == EToken::None) return;
    if (token == EToken::Error) {
        error();
    }
    if (token != EToken::Variable) {
        std::advance(begin, NGrammar::to_string(token).size());
    }
}

EToken TParser::starts_with() {
    if (begin >= end) {
        return EToken::None;
    }
    for (auto op : NGrammar::TOKEN_OPERATIONS) {
        std::string prefix = NGrammar::to_string(op);
        std::string::iterator fake = begin;
        size_t ind = 0;
        while (fake < end && ind < prefix.size()) {
            if (*fake != prefix[ind]) break;
            ind++;
            fake++;
        }
        if (ind == prefix.size()) {
            return op;
        }
    }
    if (TVariable::good_character(*begin)) {
        return EToken::Variable;
    }
    return EToken::Error;
}

void TParser::error() {
    throw std::runtime_error("Parsing error.");
}
