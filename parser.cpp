#include "parser.h"
#include "grammar.h"

TParser::TParser(std::string s) : TParser(s.begin(), s.end()) {}

TParser::TParser(std::string::iterator s, std::string::iterator t) : begin(s), end(t), token_l(begin), token_r(begin) {
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
    if (token == EOperation::Implication) {
        next_token();
        cur = std::make_shared<TBinaryOperation>(EOperation::Implication, cur, parse_impl());
    }
    return cur;
}

TParser::expr TParser::parse_dis() {
    expr cur = parse_con();
    while (token == EOperation::Disjunction) {
        next_token();
        cur = std::make_shared<TBinaryOperation>(EOperation::Disjunction, cur, parse_con());
    }
    return cur;
}

TParser::expr TParser::parse_con() {
    expr cur = parse_neg();
    while (token == EOperation::Conjunction) {
        next_token();
        cur = std::make_shared<TBinaryOperation>(EOperation::Conjunction, cur, parse_neg());
    }
    return cur;
}

TParser::expr TParser::parse_neg() {
    expr cur;
    if (token == EOperation::Negation) {
        next_token();
        cur = std::make_shared<TUnaryOperation>(EOperation::Negation, parse_neg());
    } else {
        if (token == EOperation::LeftBrace) {
            next_token();
            cur = parse_impl();
        } else {
            cur = std::make_shared<TVariable>(std::string(token_l, token_r));
        }
        next_token();
    }
    return cur;
}

void TParser::next_token() {
    token = starts_with();
    if (token == EOperation::None) return;
    if (token == EOperation::Error) {
        throw std::runtime_error("Parsing error.");
    }
    if (token == EOperation::Variable) {
        take_variable();
    } else {
        std::advance(begin, TOperation::to_string(token).size());
    }
}

void TParser::take_variable() {
    auto pos = begin;
    if (TVariable::good_first_characher(*pos)) {
        pos++;
        while (pos < end && TVariable::good_character(*pos)) pos++;
    }
    token_l = begin;
    token_r = pos;
    begin = pos;
}

EOperation TParser::starts_with() {
    if (begin >= end) {
        return EOperation::None;
    }
    for (auto op : NGrammar::TokenOperations) {
        std::string prefix = TOperation::to_string(op);
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
        return EOperation::Variable;
    }
    return EOperation::Error;
}
