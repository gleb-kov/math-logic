#include "proof.h"

bool TProofState::check_state(EProofState) const {
    return false;
}

TAxiom::TAxiom(size_t n, NGrammar::expr e) : num(n), operand(e) {}

bool TAxiom::check_state(EProofState s) const {
    return s == EProofState::Axiom;
}

size_t TAxiom::get_number() const {
    return num;
}

NGrammar::expr TAxiom::get_expr() const {
    return operand;
}

TAxiomScheme::TAxiomScheme(size_t n, NGrammar::expr e) : num(n), operand(e) {}

bool TAxiomScheme::check_state(EProofState s) const {
    return s == EProofState::AxiomScheme;
}

size_t TAxiomScheme::get_number() const {
    return num;
}

NGrammar::expr TAxiomScheme::get_expr() const {
    return operand;
}

TModusPonens::TModusPonens(size_t ln, NGrammar::expr l, size_t rn, NGrammar::expr r)
        : lnum(ln), rnum(rn), lhs(l), rhs(r) {}

bool TModusPonens::check_state(EProofState s) const {
    return s == EProofState::ModusPonens;
}

NGrammar::expr TModusPonens::get_lhs() const {
    return lhs;
}

NGrammar::expr TModusPonens::get_rhs() const {
    return rhs;
}

THypothesis::THypothesis(NGrammar::expr e) : operand(e) {}

bool THypothesis::check_state(EProofState s) const {
    return s == EProofState::Hypothesis;
}

NGrammar::expr THypothesis::get_expr() const {
    return operand;
}
