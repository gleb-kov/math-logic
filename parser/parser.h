#ifndef MATLOG_PARSER_H
#define MATLOG_PARSER_H

#include <memory>
#include <string>

#include "../grammar/lib.h"
#include "errors.h"

class TParser {
private:
    using expr = NGrammar::expr;
    using context = NGrammar::context;
    using siter = std::string::iterator;

private:
    EToken token = EToken::None;
    std::string::iterator begin;
    std::string::iterator end;

private:
    [[nodiscard, gnu::hot]] expr parse();

    [[nodiscard]] expr parse_impl();

    [[nodiscard]] expr parse_dis();

    [[nodiscard]] expr parse_con();

    [[nodiscard]] expr parse_neg();

    [[nodiscard]] expr parse_var();

    [[gnu::hot]] void next_token();

    [[nodiscard, gnu::hot]] EToken starts_with();

    [[gnu::hot]] void shift_token();

    [[noreturn]] void error() noexcept(false);

public:
    TParser() = default;

    [[nodiscard]] expr parse(std::string &s);

    [[nodiscard]] expr parse(siter from, siter to);

    [[nodiscard]] context parse_context(std::string &);

    [[nodiscard]] context parse_context(siter from, siter to);

    void clear();
};

#endif //MATLOG_PARSER_H
