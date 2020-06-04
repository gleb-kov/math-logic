#ifndef MATLOG_PROOF_H
#define MATLOG_PROOF_H

#include "../grammar/lib.h"

enum class EProofState {
    Axiom,
    AxiomScheme,
    ModusPonens,
    Hypothesis
};

struct TProofState {
    virtual bool check_state(EProofState) const;
};

struct TAxiom : TProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    TAxiom(size_t, NGrammar::expr);

    bool check_state(EProofState) const override;

    size_t get_number() const;

    NGrammar::expr get_expr() const;
};

struct TAxiomScheme : TProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    TAxiomScheme(size_t, NGrammar::expr);

    bool check_state(EProofState) const override;

    size_t get_number() const;

    NGrammar::expr get_expr() const;
};

struct TModusPonens : TProofState {
private:
    size_t lnum;
    size_t rnum;
    NGrammar::expr lhs;
    NGrammar::expr rhs;

public:
    TModusPonens(size_t, NGrammar::expr, size_t, NGrammar::expr);

    bool check_state(EProofState) const override;

    NGrammar::expr get_lhs() const;

    NGrammar::expr get_rhs() const;
};

struct THypothesis : TProofState {
private:
    NGrammar::expr operand;

public:
    explicit THypothesis(NGrammar::expr);

    bool check_state(EProofState) const override;

    NGrammar::expr get_expr() const;
};

#endif //MATLOG_PROOF_H
