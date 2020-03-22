#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <string>
#include <memory>

enum class EToken {
    Turnstile,
    Implication,
    Disjunction,
    Conjunction,
    Negation,
    Variable,
    LeftBrace,
    RightBrace,
    Comma,
    Space,
    Tab,
    NewLine,
    None,
    Error
};

// turnstile ?
enum class EOperation {
    Implication,
    Disjunction,
    Conjunction,
    Negation
};

struct TNode;

namespace NGrammar {
    using expr = std::shared_ptr<TNode>;

    // turnstile
    constexpr EOperation BinaryOperations[] = {
            EOperation::Implication,
            EOperation::Disjunction,
            EOperation::Conjunction,
    };

    constexpr EOperation UnaryOperations[] = {
            EOperation::Negation
    };

    // turnstile ?
    constexpr EToken TokenOperations[] = {
            EToken::Implication,
            EToken::Disjunction,
            EToken::Conjunction,
            EToken::Negation,
            EToken::LeftBrace,
            EToken::RightBrace
    };

    // turnstile ?
    std::string to_string(EOperation sign);

    std::string to_string(EToken sign);
}

struct TOperation {
private:
    const EOperation sign;

public:
    TOperation(EOperation sign);

    std::string to_string() const;
};

struct TNode {
    virtual std::string suffix_print() = 0;
};

struct TUnaryOperation : TNode {
    const TOperation sign;
    NGrammar::expr operand;

    TUnaryOperation(TOperation const &sign, NGrammar::expr op);

    [[nodiscard]] std::string suffix_print() override;
};

struct TBinaryOperation : TNode {
    const TOperation sign;
    NGrammar::expr lhs;
    NGrammar::expr rhs;

    TBinaryOperation(TOperation const &sign, NGrammar::expr lhs, NGrammar::expr rhs);

    [[nodiscard]] std::string suffix_print() override;
};

struct TVariable : TNode {
    std::string name;

    TVariable(std::string const &name);

    TVariable(std::string &&name);

    std::string suffix_print() override;

    static bool good_first_characher(char c);

    static bool good_character(char c);
};

#endif //MATLOG_GRAMMAR_H
