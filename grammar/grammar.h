#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <algorithm>
#include <array>
#include <cassert>
#include <memory>
#include <string>
#include <string_view>

enum class EToken {
    Implication,
    Turnstile,
    Disjunction,
    Conjunction,
    Negation,
    Addition,
    Multiplication,
    Universal,
    Existential,
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
    Negation,
    Addition,
    Multiplication
};

struct TNode;
struct TContext;

namespace NGrammar {
    using expr = std::shared_ptr<TNode>;
    using context = std::shared_ptr<TContext>;

    constexpr std::array<EOperation, 4> BINARY = {
            EOperation::Implication,
            EOperation::Turnstile,
            EOperation::Disjunction,
            EOperation::Conjunction,
    };

    constexpr std::array<EOperation, 1> UNARY = {
            EOperation::Negation
    };

    constexpr std::array<EToken, 11> OPERATIONS = {
            EToken::Implication,
            EToken::Turnstile,
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

    constexpr std::array<EToken, 3> HIDDEN = {
            EToken::Variable,
            EToken::None,
            EToken::Error
    };

    constexpr std::array<EToken, 3> SKIPPABLE = {
            EToken::Space,
            EToken::Tab,
            EToken::NewLine
    };

    [[gnu::pure, nodiscard]] inline bool is_binary(EOperation sign) {
        return std::find(BINARY.begin(), BINARY.end(), sign) != BINARY.end();
    }

    [[gnu::pure, nodiscard]] inline bool is_unary(EOperation sign) {
        return std::find(UNARY.begin(), UNARY.end(), sign) != UNARY.end();
    }

    [[gnu::pure, nodiscard]] inline bool is_skippable(EToken sign) {
        return std::find(SKIPPABLE.begin(), SKIPPABLE.end(), sign) != SKIPPABLE.end();
    }

    [[gnu::pure, nodiscard]] inline bool is_hidden(EToken sign) {
        return std::find(HIDDEN.begin(), HIDDEN.end(), sign) != HIDDEN.end();
    }

    [[gnu::pure, nodiscard]] constexpr std::string_view to_string(EOperation sign) noexcept {
        switch (sign) {
            case EOperation::Turnstile:
                return "|-";
            case EOperation::Implication:
                return "->";
            case EOperation::Disjunction:
                return "|";
            case EOperation::Conjunction:
                return "&";
            case EOperation::Negation:
                return "!";
            case EOperation::Addition:
                return "+";
            case EOperation::Multiplication:
                return "*";
            default:
                assert(false);
                return "";
        }
    }

    [[gnu::pure, nodiscard]] constexpr std::string_view to_string(EToken sign) noexcept {
        switch (sign) {
            case EToken::Turnstile:
                return "|-";
            case EToken::Implication:
                return "->";
            case EToken::Disjunction:
                return "|";
            case EToken::Conjunction:
                return "&";
            case EToken::Negation:
                return "!";
            case EToken::Addition:
                return "+";
            case EToken::Multiplication:
                return "*";
            case EToken::Universal:
                return "@";
            case EToken::Existential:
                return "?";
            case EToken::LeftBrace:
                return "(";
            case EToken::RightBrace:
                return ")";
            case EToken::Comma:
                return ",";
            case EToken::Space:
                return " ";
            case EToken::Tab:
                return "\t";
            case EToken::NewLine:
                return "\r";
            default:
                assert(false);
                return "";
        }
    }
}

struct TOperation {
private:
    const EOperation sign;

public:
    explicit TOperation(EOperation sign) : sign(sign) {}

    [[nodiscard]] std::string to_string() const {
        return NGrammar::to_string(sign).data();
    }

    EOperation get_sign() const {
        return sign;
    }
};

#endif //MATLOG_GRAMMAR_H
