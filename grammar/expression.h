#ifndef MATLOG_EXPRESSION_H
#define MATLOG_EXPRESSION_H

#include <memory>
#include <string>

#include "grammar.h"

struct TUnaryOperation;
struct TBinaryOperation;
struct TVariable;

namespace NGrammar {
    using unary_expr = std::shared_ptr<TUnaryOperation>;
    using binary_expr = std::shared_ptr<TBinaryOperation>;
    using var_expr = std::shared_ptr<TVariable>;

    [[gnu::pure, nodiscard]] unary_expr to_unary(expr const &);

    [[gnu::pure, nodiscard]] binary_expr to_binary(expr const &);

    [[gnu::pure, nodiscard]] var_expr to_variable(expr const &);



    [[gnu::pure, nodiscard, gnu::hot]] uint64_t check_axiom_scheme(expr const &);

    bool is_axiom_scheme(expr const &);

    [[deprecated("undefined"), gnu::pure, nodiscard, gnu::hot]] uint64_t check_axiom(expr const &);

    bool is_axiom(expr const &);

    [[deprecated("undefined"), gnu::pure, nodiscard, gnu::hot]] uint64_t check_intro_rule(expr const &);

    bool is_intro_rule(expr const &);
}

struct TNode {
    virtual std::string to_suffix() const = 0;

    virtual std::string to_string() const = 0;

    virtual size_t calc_hash() const;

    virtual size_t get_hash() const;

    virtual bool is_unary() const;

    virtual bool is_binary() const;

    virtual bool is_variable() const;

    virtual bool check_sign(EOperation);

    friend bool operator==(NGrammar::expr const &lhs, NGrammar::expr const &rhs) {
        return lhs->get_hash() == rhs->get_hash();
    }

    friend bool operator!=(NGrammar::expr const &lhs, NGrammar::expr const &rhs) {
        return lhs->get_hash() != rhs->get_hash();
    }
};

struct TUnaryOperation : TNode {
private:
    size_t hash;
    const TOperation sign;
    NGrammar::expr operand;

public:
    TUnaryOperation(EOperation const &, NGrammar::expr);

    [[nodiscard]] std::string to_suffix() const override;

    [[nodiscard]] std::string to_string() const override;

    NGrammar::expr get_operand() const;

    size_t get_hash() const override;

    bool is_unary() const override;

    bool check_sign(EOperation) override;
};

struct TBinaryOperation : TNode {
private:
    size_t hash;
    const TOperation sign;
    NGrammar::expr lhs;
    NGrammar::expr rhs;

public:
    TBinaryOperation(EOperation const &, NGrammar::expr lhs, NGrammar::expr rhs);

    [[nodiscard]] std::string to_suffix() const override;

    [[nodiscard]] std::string to_string() const override;

    NGrammar::expr get_lhs() const;

    NGrammar::expr get_rhs() const;

    size_t get_hash() const override;

    bool is_binary() const override;

    bool check_sign(EOperation) override;
};

struct TVariable : TNode {
private:
    size_t hash;
    std::string name;

public:
    explicit TVariable(std::string const &);

    explicit TVariable(std::string &&);

    std::string to_suffix() const override;

    std::string to_string() const override;

    size_t get_hash() const override;

    bool is_variable() const override;

    [[gnu::pure]] static bool good_first_characher(char);

    [[gnu::pure]] static bool good_character(char);
};

namespace std {
    template<>
    struct hash<TNode> {
        size_t operator()(TNode const &s) const noexcept {
            return s.get_hash();
        }
    };
}

std::ostream &operator<<(std::ostream &s, TNode &);

#endif //MATLOG_EXPRESSION_H
