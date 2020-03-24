#include "proof.h"

void TExprList::add(NGrammar::expr const &e) {
    size_t pos = ++cnt;
    table[e->get_hash()] = pos;
    list.emplace_back(e);
    /*if (e->is_operation(EOperation::Implication)) {

    }*/
}

size_t TExprList::get_index(NGrammar::expr const &e) {
    auto pos = table.find(e->get_hash());
    return (pos == table.end() ? 0 : pos->second);
}

bool TExprList::contains(NGrammar::expr const &e) {
    return get_index(e) != 0;
}

/*std::vector<size_t>::iterator TExprList::rev_impl_begin(NGrammar::expr const &rhs) {
    return rev_impl[rhs->get_hash()].begin();
}

std::vector<size_t>::iterator TExprList::rev_impl_end(NGrammar::expr const &rhs) {
    return rev_impl[rhs->get_hash()].end();
}*/

size_t TExprList::size() const {
    return cnt;
}

NGrammar::expr TExprList::operator[](size_t index) {
    return list[index];
}

std::vector<NGrammar::expr>::iterator TExprList::begin() {
    return list.begin();
}

std::vector<NGrammar::expr>::iterator TExprList::end() {
    return list.end();
}

TContext::TContext() : sign(EOperation::Turnstile), separator(EToken::Comma) {}

void TContext::add_hypothesis(NGrammar::expr const &hyp) {
    hypothesis.add(hyp);
}

void TContext::set_statement(NGrammar::expr const &res) {
    result = res;
}

size_t TContext::get_hypothesis(NGrammar::expr const &hyp) {
    return hypothesis.get_index(hyp);
}

bool TContext::has_hypothesis(NGrammar::expr const &hyp) {
    return hypothesis.contains(hyp);
}

size_t TContext::size() const {
    return hypothesis.size();
}

std::string TContext::to_suffix() {
    return to_string();
}

std::string TContext::to_string() {
    std::string res;
    for (size_t i = 0; i < hypothesis.size(); i++) {
        res += hypothesis[i]->to_string();
        if (i + 1 < hypothesis.size()) {
            res += NGrammar::to_string(separator);
        }
        res += NGrammar::to_string(EToken::Space);
    }
    res += sign.to_string() + NGrammar::to_string(EToken::Space);
    res += result->to_string();
    return res;
}

std::ostream &operator<<(std::ostream &s, TContext &e) {
    s << e.to_string();
    return s;
}
