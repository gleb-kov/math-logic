#include "parser.h"

TParser::TParser(std::string s) : TParser(s.begin(), s.end()) {}

TParser::TParser(std::string::iterator s, std::string::iterator t) : begin(s), end(t) {
    if (begin < end) {
        next_token();
        res = parse_impl();
    }
}

TParser::expr TParser::get_result() {
    return res;
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
    token = starts_with();
    if (token == EToken::None) return;
    if (token == EToken::Error) {
        throw std::runtime_error("Parsing error.");
    }
    if (token != EToken::Variable) {
        std::advance(begin, NGrammar::to_string(token).size());
    }
}

EToken TParser::starts_with() {
    if (begin >= end) {
        return EToken::None;
    }
    for (auto op : NGrammar::TokenOperations) {
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
