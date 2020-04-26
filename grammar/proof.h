#ifndef MATLOG_PROOF_H
#define MATLOG_PROOF_H

#include <string>
#include <unordered_map>
#include <vector>

#include "grammar.h"
#include "expression.h"

struct TExprList {
private:
    size_t cnt = 0;
    std::unordered_map<size_t, size_t> table;
    std::vector<NGrammar::expr> list;
    // indices of expr's where rhs is given implication
    std::unordered_map<size_t, std::vector<size_t>> rev_impl;

public:
    TExprList() = default;

    void add(NGrammar::expr const &);

    size_t get_index(NGrammar::expr const &);

    bool contains(NGrammar::expr const &);

    size_t size() const;

    NGrammar::expr operator[](size_t index);

    NGrammar::expr operator[](size_t index) const;

    std::vector<NGrammar::expr>::iterator begin();

    std::vector<NGrammar::expr>::iterator end();

    std::vector<size_t>::iterator rev_impl_begin(NGrammar::expr const &);

    std::vector<size_t>::iterator rev_impl_end(NGrammar::expr const &);
};

struct TContext {
private:
    const TOperation sign;
    const EToken separator;
    NGrammar::expr result;
    TExprList hypothesis;

public:
    TContext();

    void add_hypothesis(NGrammar::expr const &);

    void set_statement(NGrammar::expr const &);

    size_t get_hypothesis(NGrammar::expr const &);

    bool has_hypothesis(NGrammar::expr const &);

    NGrammar::expr get_statement();

    size_t size() const;

    std::string to_string();
};

std::ostream &operator<<(std::ostream &s, TContext &);

#endif //MATLOG_PROOF_H
