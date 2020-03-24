#ifndef MATLOG_EXPRESSION_H
#define MATLOG_EXPRESSION_H

#include <memory>
#include <string>

#include "grammar.h"

struct TNode {
    virtual std::string to_suffix() const = 0;

    virtual std::string to_string() const = 0;

    virtual size_t calc_hash() const {
        return std::hash<std::string>{}(to_string());
    }

    virtual size_t get_hash() const {
        return calc_hash();
    }

    virtual bool is_operation(EOperation) {
        return false;
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

    size_t get_hash() const override;

    bool is_operation(EOperation) override;
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

    size_t get_hash() const override;

    bool is_operation(EOperation) override;
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

    static bool good_first_characher(char);

    static bool good_character(char);
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
