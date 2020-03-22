#ifndef MATLOG_PARSER_H
#define MATLOG_PARSER_H

#include <memory>
#include <string>

#include "../utils/grammar.h"

class TParser {
private:
    using expr = NGrammar::expr;

private:
    EToken token = EToken::None;
    std::string::iterator begin;
    std::string::iterator end;
    const expr EMPTY = std::shared_ptr<TNode>(nullptr);

private:
    [[nodiscard]] expr parse_impl();

    [[nodiscard]] expr parse_dis();

    [[nodiscard]] expr parse_con();

    [[nodiscard]] expr parse_neg();

    [[nodiscard]] expr parse_var();

    void next_token();

    [[nodiscard]] EToken starts_with();

    void error() noexcept(false);

public:
    TParser() = default;

    expr parse(std::string &s);

    expr parse(std::string::iterator from, std::string::iterator to);

    expr parse_context(std::string &);

    expr parse_context(std::string::iterator from, std::string::iterator to);

    void clear();
};

#endif //MATLOG_PARSER_H
