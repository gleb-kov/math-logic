#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <memory>
#include <string>

enum class EToken {
    Turnstile,
    Implication,
    Disjunction,
    Conjunction,
    Negation,
    LeftBrace,
    RightBrace,
    Comma,
    Space,
    Tab,
    NewLine,
    Variable,
    None,
    Error
};

enum class EOperation {
    Turnstile,
    Implication,
    Disjunction,
    Conjunction,
    Negation
};

struct TNode;

namespace NGrammar {
    using expr = std::shared_ptr<TNode>;

    constexpr EOperation BINARY_OPERATIONS[] = {
            EOperation::Turnstile,
            EOperation::Implication,
            EOperation::Disjunction,
            EOperation::Conjunction,
    };

    constexpr EOperation UNARY_OPERATIONS[] = {
            EOperation::Negation
    };

    constexpr EToken TOKEN_OPERATIONS[] = {
            EToken::Turnstile,
            EToken::Implication,
            EToken::Disjunction,
            EToken::Conjunction,
            EToken::Negation,
            EToken::LeftBrace,
            EToken::RightBrace,
            EToken::Comma,
            EToken::Space,
            EToken::Tab,
            EToken::NewLine
    };

    constexpr EToken SKIPPABLE[]{
            EToken::Space,
            EToken::Tab,
            EToken::NewLine
    };

    bool is_binary(EOperation);

    bool is_unary(EOperation);

    bool is_skippable(EToken);

    std::string to_string(EOperation);

    std::string to_string(EToken);
}

struct TOperation {
private:
    const EOperation sign;

public:
    explicit TOperation(EOperation);

    std::string to_string() const;
};

struct TNode {
    virtual std::string to_suffix() = 0;

    virtual std::string to_string() = 0;
};

struct TUnaryOperation : TNode {
    const TOperation sign;
    NGrammar::expr operand;

    TUnaryOperation(EOperation const &, NGrammar::expr);

    [[nodiscard]] std::string to_suffix() override;

    [[nodiscard]] std::string to_string() override;
};

struct TBinaryOperation : TNode {
    const TOperation sign;
    NGrammar::expr lhs;
    NGrammar::expr rhs;

    TBinaryOperation(EOperation const &, NGrammar::expr lhs, NGrammar::expr rhs);

    [[nodiscard]] std::string to_suffix() override;

    [[nodiscard]] std::string to_string() override;
};

struct TVariable : TNode {
    std::string name;

    TVariable(std::string const &);

    TVariable(std::string &&);

    std::string to_suffix() override;

    std::string to_string() override;

    static bool good_first_characher(char);

    static bool good_character(char);
};

#endif //MATLOG_GRAMMAR_H
