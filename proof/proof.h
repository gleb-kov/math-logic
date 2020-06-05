#ifndef MATLOG_PROOF_H
#define MATLOG_PROOF_H

#include "../grammar/lib.h"

enum class EProofState {
    Axiom,
    AxiomScheme,
    Hypothesis,
    ModusPonens
};

struct IProofState {
    virtual EProofState get_state() const = 0;

    virtual bool check_state(EProofState) const;

    virtual NGrammar::expr get_expr() const = 0;
};

struct TAxiom : IProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    TAxiom(size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    size_t get_number() const;

    NGrammar::expr get_expr() const override;
};

struct TAxiomScheme : IProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    TAxiomScheme(size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    size_t get_number() const;

    NGrammar::expr get_expr() const override;
};

struct THypothesis : IProofState {
private:
    size_t num;
    NGrammar::expr operand;

public:
    explicit THypothesis(size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    size_t get_number() const;

    NGrammar::expr get_expr() const override;
};

struct TModusPonens : IProofState {
private:
    size_t lnum;
    size_t rnum;
    NGrammar::expr operand;

public:
    TModusPonens(size_t, size_t, NGrammar::expr);

    EProofState get_state() const override;

    bool check_state(EProofState) const override;

    std::pair<size_t, size_t> mp_numbers() const;

    void renumerate(size_t, size_t);

    NGrammar::expr get_expr() const override;
};

namespace NProof {
    using pstate = std::unique_ptr<IProofState>;
    using mp_state = std::unique_ptr<TModusPonens>;

    template <typename T>
    [[gnu::pure, nodiscard]] inline T * caster(pstate const &e) {
        return dynamic_cast<T *>(e.get());
    }

    [[gnu::pure, nodiscard]] inline TModusPonens * to_mp(pstate const &e) {
        return caster<TModusPonens>(e);
    }
}

#endif //MATLOG_PROOF_H
