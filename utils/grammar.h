#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <memory>
#include <string>
#include <vector>

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
struct TContext;

namespace NGrammar {
    using expr = std::shared_ptr<TNode>;
    using context = std::shared_ptr<TContext>;

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

    const EToken HIDDEN_TOKEN[] = {
            EToken::Variable,
            EToken::None,
            EToken::Error
    };

    constexpr EToken SKIPPABLE[]{
            EToken::Space,
            EToken::Tab,
            EToken::NewLine
    };

    bool is_binary(EOperation);

    bool is_unary(EOperation);

    bool is_skippable(EToken);

    bool is_hidden(EToken);

    std::string to_string(EOperation);

    std::string to_string(EToken);
}

struct TOperation {
private:
    const EOperation sign;

public:
    TOperation(EOperation);

    std::string to_string() const;
};

struct TNode {
    virtual std::string to_suffix() = 0;

    virtual std::string to_string() = 0;
};

struct TUnaryOperation : TNode {
private:
    const TOperation sign;
    NGrammar::expr operand;

public:
    TUnaryOperation(EOperation const &, NGrammar::expr);

    [[nodiscard]] std::string to_suffix() override;

    [[nodiscard]] std::string to_string() override;
};

struct TBinaryOperation : TNode {
private:
    const TOperation sign;
    NGrammar::expr lhs;
    NGrammar::expr rhs;

public:
    TBinaryOperation(EOperation const &, NGrammar::expr lhs, NGrammar::expr rhs);

    [[nodiscard]] std::string to_suffix() override;

    [[nodiscard]] std::string to_string() override;
};

struct TVariable : TNode {
private:
    std::string name;

public:
    TVariable(std::string const &);

    TVariable(std::string &&);

    std::string to_suffix() override;

    std::string to_string() override;

    static bool good_first_characher(char);

    static bool good_character(char);
};

struct TContext {
private:
    const TOperation sign;
    std::vector<NGrammar::expr> hypothesis;
    NGrammar::expr result;

public:
    TContext();

    void add_hypothesis(NGrammar::expr const &);

    void set_statement(NGrammar::expr const &);

    std::string to_suffix();

    std::string to_string();
};

std::ostream &operator<<(std::ostream &s, TNode &);

std::ostream &operator<<(std::ostream &s, TContext &);

#endif //MATLOG_GRAMMAR_H
