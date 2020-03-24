#ifndef MATLOG_GRAMMAR_H
#define MATLOG_GRAMMAR_H

#include <memory>
#include <string>
#include <unordered_map>
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

    uint64_t check_axiom(expr const &);

    bool is_axiom(expr const &);

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
    explicit TOperation(EOperation);

    std::string to_string() const;

    EOperation get_sign() const;
};

#endif //MATLOG_GRAMMAR_H
