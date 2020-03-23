#ifndef MATLOG_PARSER_H
#define MATLOG_PARSER_H

#include <memory>
#include <string>

#include "../utils/grammar.h"

class TParser {
private:
    using expr = NGrammar::expr;
    using context = NGrammar::context;

private:
    EToken token = EToken::None;
    std::string::iterator begin;
    std::string::iterator end;
    const expr EMPTY_EXPR = std::shared_ptr<TNode>(nullptr);
    const context EMPTY_CONTEXT = std::shared_ptr<TContext>(nullptr);

private:
    [[nodiscard]] expr parse();

    [[nodiscard]] expr parse_impl();

    [[nodiscard]] expr parse_dis();

    [[nodiscard]] expr parse_con();

    [[nodiscard]] expr parse_neg();

    [[nodiscard]] expr parse_var();

    void next_token();

    [[nodiscard]] EToken starts_with();

    void error() noexcept(false);

    void shift_token();

public:
    TParser() = default;

    [[nodiscard]] expr parse(std::string &s);

    [[nodiscard]] expr parse(std::string::iterator from, std::string::iterator to);

    [[nodiscard]] context parse_context(std::string &);

    [[nodiscard]] context parse_context(std::string::iterator from, std::string::iterator to);

    void clear();
};

#endif //MATLOG_PARSER_H
