#ifndef MATLOG_PROOF_H
#define MATLOG_PROOF_H

#include <string>
#include <unordered_map>
#include <vector>

#include "grammar.h"
#include "expression.h"

struct TExprList {
private:
    using expr = NGrammar::expr;

private:
    size_t cnt = 0;
    std::unordered_map<size_t, size_t> table;
    std::vector<expr> list;
    // indices of expr's where rhs is given implication
    std::unordered_map<size_t, std::vector<size_t>> rev_impl;

public:
    TExprList() = default;

    void add(expr const &);

    size_t get_index(expr const &) const;

    bool contains(expr const &) const;

    bool contains_rev(expr const &) const;

    size_t size() const;

    expr back() const;

    expr operator[](size_t index);

    expr operator[](size_t index) const;

    std::vector<expr>::iterator begin();

    std::vector<expr>::iterator end();

    std::vector<size_t>::const_iterator rev_impl_begin(expr const &);

    std::vector<size_t>::const_iterator rev_impl_end(expr const &);
};

struct TContext {
private:
    using expr = NGrammar::expr;

private:
    const TOperation sign;
    const EToken separator;
    expr result;
    TExprList hypothesis;

public:
    TContext();

    void add_hypothesis(expr const &);

    void set_statement(expr const &);

    size_t get_hypothesis(expr const &);

    bool has_hypothesis(expr const &);

    expr get_statement();

    size_t size() const;

    std::string to_string();
};

namespace NGrammar {
    [[gnu::pure, nodiscard, gnu::hot]] std::pair<size_t, size_t> check_modus_ponens(TExprList &, expr const &);

    bool is_modus_ponens(TExprList &, expr const &);
}

std::ostream &operator<<(std::ostream &s, TContext &);

#endif //MATLOG_PROOF_H
