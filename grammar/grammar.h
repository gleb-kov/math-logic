#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <array>
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
struct TContext;

namespace NGrammar {
    using expr = std::shared_ptr<TNode>;
    using context = std::shared_ptr<TContext>;

    constexpr std::array<EOperation, 4> BINARY= {
            EOperation::Turnstile,
            EOperation::Implication,
            EOperation::Disjunction,
            EOperation::Conjunction,
    };

    constexpr std::array<EOperation, 1> UNARY = {
            EOperation::Negation
    };

    constexpr std::array<EToken, 11> OPERATIONS = {
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

    bool is_binary(EOperation);

    bool is_unary(EOperation);

    bool is_skippable(EToken);

    bool is_hidden(EToken);

    std::string to_string(EOperation) noexcept;

    std::string to_string(EToken) noexcept;

    const static auto SPACE = NGrammar::to_string(EToken::Space);
    const static auto SEPARATOR = NGrammar::to_string(EToken::Comma);
    const static auto LEFT_BRACE = NGrammar::to_string(EToken::LeftBrace);
    const static auto RIGHT_BRACE = NGrammar::to_string(EToken::RightBrace);
}

struct TOperation {
private:
    const EOperation sign;

public:
    explicit TOperation(EOperation);

    std::string to_string() const;

    EOperation get_sign() const;
};

#endif //MATLOG_GRAMMAR_H
