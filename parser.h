#ifndef MATLOG_PARSER_H
#define MATLOG_PARSER_H

#include "grammar.h"

class TParser {
private:
    using expr = NGrammar::expr;

private:
    expr res;
    EOperation token = EOperation::None;

    // given string borders
    std::string::iterator begin;
    std::string::iterator end;

    // current token borders
    std::string::iterator token_l;
    std::string::iterator token_r;

private:
    [[nodiscard]] expr parse_impl();

    [[nodiscard]] expr parse_dis();

    [[nodiscard]] expr parse_con();

    [[nodiscard]] expr parse_neg();

    void next_token();

    void take_variable();

    [[nodiscard]] EOperation starts_with();

public:
    explicit TParser(std::string s);

    TParser(std::string::iterator begin, std::string::iterator end);

    expr get_result();
};

#endif //MATLOG_PARSER_H
