#ifndef MATLOG_PROOF_H
#define MATLOG_PROOF_H

#include "../grammar/lib.h"

enum class EProofState {
    Axiom,
    AxiomScheme,
    Hypothesis,
    ModusPonens
};

struct TProofState {
    virtual EProofState get_state() const = 0;

    virtual bool check_state(EProofState) const;

    virtual NGrammar::expr get_expr() const = 0;

    virtual size_t get_number() const = 0;

    virtual std::pair<size_t, size_t> mp_numbers() const = 0;
};

struct TAxiom : TProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    TAxiom(size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    size_t get_number() const override;

    NGrammar::expr get_expr() const override;
};

struct TAxiomScheme : TProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    TAxiomScheme(size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    size_t get_number() const override;

    NGrammar::expr get_expr() const override ;
};

struct THypothesis : TProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    explicit THypothesis(size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    size_t get_number() const override;

    NGrammar::expr get_expr() const override;
};

struct TModusPonens : TProofState {
private:
    size_t lnum;
    size_t rnum;
    NGrammar::expr operand;

public:
    TModusPonens(size_t, size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    std::pair<size_t, size_t> mp_numbers() const override;

    void renumerate(size_t, size_t);

    NGrammar::expr get_expr() const override;
};

#endif //MATLOG_PROOF_H
