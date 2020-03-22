#ifndef MATLOG_PARSER_H
#define MATLOG_PARSER_H

#include "../utils/grammar.h"
#include <string>
#include <memory>

class TParser {
private:
    using expr = NGrammar::expr;

private:
    expr res;
    EToken token = EToken::None;
    std::string::iterator begin;
    std::string::iterator end;

private:
    [[nodiscard]] expr parse_impl();

    [[nodiscard]] expr parse_dis();

    [[nodiscard]] expr parse_con();

    [[nodiscard]] expr parse_neg();

    [[nodiscard]] expr parse_var();

    void next_token();

    [[nodiscard]] EToken starts_with();

public:
    explicit TParser(std::string s);

    TParser(std::string::iterator begin, std::string::iterator end);

    expr get_result();
};

#endif //MATLOG_PARSER_H
