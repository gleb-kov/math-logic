#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <string>
#include <memory>

enum class EOperation {
    Implication,
    Disjunction,
    Conjunction,
    Negation,
    Variable,
    LeftBrace,
    RightBrace,
    None,
    Error
};

struct TNode;

namespace NGrammar {
    using expr = std::shared_ptr<TNode>;

    constexpr EOperation BinaryOperations[] = {
            EOperation::Implication,
            EOperation::Disjunction,
            EOperation::Conjunction,
    };

    constexpr EOperation TokenOperations[] = {
            EOperation::Implication,
            EOperation::Disjunction,
            EOperation::Conjunction,
            EOperation::Negation,
            EOperation::LeftBrace,
            EOperation::RightBrace
    };

    constexpr EOperation UnaryOperations[] = {
            EOperation::Negation
    };

    constexpr EOperation Specials[] = {
            EOperation::LeftBrace,
            EOperation::RightBrace,
            EOperation::None,
            EOperation::Error
    };
}

struct TOperation {
private:
    const EOperation sign;

public:
    TOperation(EOperation sign) : sign(sign) {}

    std::string to_string() const {
        return to_string(sign);
    }

    static std::string to_string(EOperation sign) {
        switch (sign) {
            case EOperation::Implication:
                return "->";
            case EOperation::Disjunction:
                return "|";
            case EOperation::Conjunction:
                return "&";
            case EOperation::Negation:
                return "!";
            case EOperation::LeftBrace:
                return "(";
            case EOperation::RightBrace:
                return ")";
            case EOperation::None:
                return "none";
            case EOperation::Variable:
                return "variable";
            default:
                return "error";
        }
    }
};

struct TNode {
    virtual std::string suffix_print() = 0;
};

struct TBinaryOperation : TNode {
    const TOperation sign;
    NGrammar::expr lhs;
    NGrammar::expr rhs;

    TBinaryOperation(TOperation const &sign, NGrammar::expr lhs, NGrammar::expr rhs)
            : sign(sign), lhs(std::move(lhs)), rhs(std::move(rhs)) {}

    [[nodiscard]] std::string suffix_print() override {
        return '(' + sign.to_string() + ',' + lhs->suffix_print() + ',' + rhs->suffix_print() + ')';
    }
};

struct TUnaryOperation : TNode {
    const TOperation sign;
    NGrammar::expr operand;

    TUnaryOperation(TOperation const &sign, NGrammar::expr op) : sign(sign), operand(std::move(op)) {}

    [[nodiscard]] std::string suffix_print() override {
        return '(' + sign.to_string() + operand->suffix_print() + ')';
    }
};

struct TVariable : TNode {
    std::string name;

    TVariable(std::string const &name) : name(name) {}

    TVariable(std::string &&name) : name(std::move(name)) {}

    std::string suffix_print() override {
        return name;
    }

    static bool good_first_characher(char c) {
        return 'A' <= c && c <= 'Z';
    }

    static bool good_character(char c) {
        return good_first_characher(c) || c == '\'' || ('0' <= c && c <= '9');
    }
};

#endif //MATLOG_GRAMMAR_H
