#ifndef MATLOG_STRUCTURES_H
#define MATLOG_STRUCTURES_H

#include <string>
#include <unordered_map>
#include <memory>
#include <vector>

#include "proof.h"

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
    using context = std::shared_ptr<TContext>;
}

namespace NProof {
    using pstate = std::unique_ptr<TProofState>;
}

// TODO:
struct TProof {
private:
    NGrammar::context head;
    std::vector<std::unique_ptr<TProofState>> proof_state;

public:
    TProof() = default;

    void set_context() {}

    void add_state() {}

    std::vector<size_t> minimize_body() const {
        return {};
    }
};

namespace NProof {
    [[gnu::pure, nodiscard, gnu::hot]] std::pair<size_t, size_t> check_modus_ponens(TExprList &, NGrammar::expr const &);

    bool is_modus_ponens(TExprList &, NGrammar::expr const &);
}

std::ostream &operator<<(std::ostream &s, TContext &);

#endif //MATLOG_STRUCTURES_H
