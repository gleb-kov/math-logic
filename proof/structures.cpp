#include <utility>

#include "structures.h"

void TExprList::add(expr const &e) {
    size_t pos = ++cnt;
    size_t h = e->get_hash();
    table[h] = pos;
    list.emplace_back(e);
    if (e->check_sign(EOperation::Implication)) {
        size_t rhs_hash = NGrammar::to_binary(e)->get_rhs()->get_hash();
        rev_impl[rhs_hash].push_back(pos);
    }
}

size_t TExprList::get_index(expr const &e) const {
    auto pos = table.find(e->get_hash());
    return (pos == table.end() ? 0 : pos->second);
}

bool TExprList::contains(expr const &e) const {
    return get_index(e) != 0;
}

bool TExprList::contains_rev(const expr & e) const {
    return (rev_impl.find(e->get_hash()) != rev_impl.end());
}

std::vector<size_t>::const_iterator TExprList::rev_impl_begin(expr const &rhs) {
    return rev_impl[rhs->get_hash()].cbegin();
    auto pos = rev_impl.find(rhs->get_hash())->second;
    return pos.cbegin();
}

std::vector<size_t>::const_iterator TExprList::rev_impl_end(expr const &rhs) {
    return rev_impl[rhs->get_hash()].cend();
    auto pos = rev_impl.find(rhs->get_hash())->second;
    return pos.cend();
}

size_t TExprList::size() const {
    return cnt;
}

NGrammar::expr TExprList::back() const {
    return list.back();
}

// 3rd party indexation starts with 1
NGrammar::expr TExprList::operator[](size_t index) {
    assert(index > 0);
    return list[index - 1];
}

// 3rd party indexation starts with 1
NGrammar::expr TExprList::operator[](size_t index) const {
    assert(index > 0);
    return list[index - 1];
}

std::vector<NGrammar::expr>::iterator TExprList::begin() {
    return list.begin();
}

std::vector<NGrammar::expr>::iterator TExprList::end() {
    return list.end();
}

TContext::TContext() : sign(EOperation::Turnstile), separator(EToken::Comma) {}

void TContext::add_hypothesis(expr const &hyp) {
    hypothesis.add(hyp);
}

void TContext::set_statement(expr const &res) {
    result = res;
}

size_t TContext::get_hypothesis(expr const &hyp) const {
    return hypothesis.get_index(hyp);
}

bool TContext::has_hypothesis(expr const &hyp) const {
    return hypothesis.contains(hyp);
}

NGrammar::expr TContext::get_statement() const {
    return result;
}

size_t TContext::size() const {
    return hypothesis.size();
}

std::string TContext::to_string() const {
    std::string res;
    for (size_t i = 1; i <= hypothesis.size(); i++) {
        res += hypothesis[i]->to_string();
        if (i < hypothesis.size()) {
            res += ',';
        }
        res += ' ';
    }
    res += sign.to_string() + ' ';
    res += result->to_string();
    return res;
}

void TProof::set_context(NGrammar::context ctx) {
    head = std::move(ctx);
}

void TProof::add_state(TProof::pstate ps) {
    proof_state.push_back(std::move(ps));
}

void TProof::minimize_body() {
    size_t last = proof_state.size();
    std::vector<size_t> renumeration(last + 1, 0);
    std::queue<size_t> dep({last});
    renumeration[last] = 1;
    while (!dep.empty()) {
        size_t cur = dep.front();
        dep.pop();
        if (proof_state[cur - 1]->get_state() == EProofState::ModusPonens){
            auto t = NProof::to_mp(proof_state[cur - 1])->mp_numbers();
            if (renumeration[t.first] == 0) {
                renumeration[t.first] = 1;
                dep.push(t.first);
            }
            if (renumeration[t.second] == 0) {
                renumeration[t.second] = 1;
                dep.push(t.second);
            }
        }
    }
    size_t cnt = 0;
    for (size_t i = 1; i < renumeration.size(); i++) {
        cnt += renumeration[i];
        if (renumeration[i]) renumeration[i] = cnt;
        if (proof_state[i - 1]->get_state() == EProofState::ModusPonens) {
            auto t = NProof::to_mp(proof_state[i - 1])->mp_numbers();
            NProof::to_mp(proof_state[i-1])->renumerate(renumeration[t.first], renumeration[t.second]);
        }
    }
    for (size_t i = renumeration.size(); i > 1;) {
        i--;
        if (renumeration[i]) continue;
        proof_state.erase(proof_state.begin() + i - 1);
    }
}

std::pair<size_t, size_t> NProof::check_modus_ponens(TExprList &proof, NGrammar::expr const &e) {
    for (auto it = proof.rev_impl_begin(e); it != proof.rev_impl_end(e); it++) {
        size_t rhs_ind = *it;
        auto rhs = proof[rhs_ind];
        auto needed_lhs = NGrammar::to_binary(rhs)->get_lhs();
        size_t lhs_ind = proof.get_index(needed_lhs);
        if (lhs_ind) return {rhs_ind, lhs_ind};
    }
    return {0, 0};
}

bool NProof::is_modus_ponens(TExprList &proof, NGrammar::expr const &e) {
    auto mp = check_modus_ponens(proof, e);
    return mp.first != 0 && mp.second != 0;
}

std::ostream &operator<<(std::ostream &s, TContext &e) {
    s << e.to_string();
    return s;
}

std::ostream &operator<<(std::ostream &s, TProof &p) {
    s << p.head->to_string() << std::endl;
    for (size_t i = 0; i < p.proof_state.size(); i++) {
        s << '[' << i + 1 << ". ";
        switch (p.proof_state[i]->get_state()) {
            case EProofState::Axiom:{
                s << "Ax. " << NProof::caster<TAxiom>(p.proof_state[i])->get_number();
                break;
            }
            case EProofState::AxiomScheme:{
                s << "Ax. sch. " << NProof::caster<TAxiomScheme>(p.proof_state[i])->get_number();
                break;
            }
            case EProofState::ModusPonens:{
                auto t = NProof::to_mp(p.proof_state[i])->mp_numbers();
                s << "M.P. " << t.first << ", " << t.second;
                break;
            }
            case EProofState::Hypothesis:{
                s << "Hypothesis " << NProof::caster<THypothesis>(p.proof_state[i])->get_number();
                break;
            }
        }
        s << "] " << p.proof_state[i]->get_expr()->to_string() << std::endl;
    }
    return s;
}