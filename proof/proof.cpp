#include "proof.h"

bool TProofState::check_state(EProofState) const {
    return false;
}

TAxiom::TAxiom(size_t n, NGrammar::expr e) : num(n), operand(e) {}

EProofState TAxiom::get_state() const {
    return EProofState::Axiom;
}

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

EProofState TAxiomScheme::get_state() const {
    return EProofState::AxiomScheme;
}

bool TAxiomScheme::check_state(EProofState s) const {
    return s == EProofState::AxiomScheme;
}

size_t TAxiomScheme::get_number() const {
    return num;
}

NGrammar::expr TAxiomScheme::get_expr() const {
    return operand;
}

THypothesis::THypothesis(size_t n, NGrammar::expr e) : num(n), operand(e) {}

EProofState THypothesis::get_state() const {
    return EProofState::Hypothesis;
}

bool THypothesis::check_state(EProofState s) const {
    return s == EProofState::Hypothesis;
}

size_t THypothesis::get_number() const {
    return num;
}

NGrammar::expr THypothesis::get_expr() const {
    return operand;
}

TModusPonens::TModusPonens(size_t ln, size_t rn, NGrammar::expr e)
        : lnum(ln), rnum(rn), operand(e) {}

EProofState TModusPonens::get_state() const {
    return EProofState::ModusPonens;
}

bool TModusPonens::check_state(EProofState s) const {
    return s == EProofState::ModusPonens;
}

std::pair<size_t, size_t> TModusPonens::mp_numbers() const {
    return {lnum, rnum};
}

void TModusPonens::renumerate(size_t l, size_t r) {
    lnum = l;
    rnum = r;
}

NGrammar::expr TModusPonens::get_expr() const {
    return operand;
}
