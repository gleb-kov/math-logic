#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

#include "parser/parser.h"

using testfunc = std::function<std::string(TParser &, std::string &)>;

testfunc to_suffix = [](TParser &solver, std::string &str) {
    return solver.parse(str)->to_suffix();
};

testfunc to_string = [](TParser &solver, std::string &str) {
    return solver.parse(str)->to_string();
};

testfunc context_to_string = [](TParser &solver, std::string &str) {
    return solver.parse_context(str)->to_string();
};

bool test(TParser &solver, std::vector<std::string> &samples,
          std::vector<std::string> const &answers, testfunc &func) {
    assert(samples.size() == answers.size());

    for (size_t i = 0; i < samples.size(); i++) {
        if (func(solver, samples[i]) != answers[i]) {
            return false;
        }
        solver.clear();
    }
    return true;
}

bool catch_test(TParser &solver, std::vector<std::string> &samples, testfunc &func) {
    for (auto &sample : samples) {
        try {
            func(solver, sample);
            return false;
        } catch (...) {}
        solver.clear();
    }
    return true;
}

bool task1_tests() {
    std::vector<std::string> samples = {
            "A  &  A",
            "!A&!B->!(A|B)",
            "P1'->!QQ->!R10&S|!T&U&V"
    };
    std::vector<std::string> bad_samples = {
            "P1’->!QQ->!R10&S|!T&U&V",
            "a"
    };
    std::vector<std::string> suffix = {
            "(&,A,A)",
            "(->,(&,(!A),(!B)),(!(|,A,B)))",
            "(->,P1',(->,(!QQ),(|,(&,(!R10),S),(&,(&,(!T),U),V))))"
    };
    std::vector<std::string> normal = {
            "(A & A)",
            "((!A & !B) -> !(A | B))",
            "(P1' -> (!QQ -> ((!R10 & S) | ((!T & U) & V))))"
    };
    TParser solver;
    if (!test(solver, samples, suffix, to_suffix)) return false;
    if (!test(solver, samples, normal, to_string)) return false;
    return catch_test(solver, bad_samples, to_string);
}

bool task2_tests() {
    std::vector<std::string> context = {
            "|- A -> A",
            "A->B, !B |- !A",
            "A, C |- B'"
    };
    std::vector<std::string> answers = {
            "|- (A -> A)",
            "(A -> B), !B |- !A",
            "A, C |- B'"
    };
    TParser solver;
    if (!test(solver, context, answers, context_to_string)) return false;
    return true;
}

bool axiom_tests() {
    std::array<std::string, 10> axioms = {
            "A -> B -> A",
            "(A -> B) -> ((A -> B -> C) -> (A -> C))",
            "A -> B -> A & B",
            "A & B -> A",
            "A & B -> B",
            "A -> A | B",
            "B -> A | B",
            "(A -> C) -> (B -> C) -> (A | B -> C)",
            "(A -> B) -> ((A -> !B) -> !A)",
            "!!A -> A"
    };
    bool flag = true;
    for (size_t i = 0; i < axioms.size(); i++) {
        auto t = NGrammar::check_axiom(TParser().parse(axioms[i]));
        if (t != i + 1) {
            flag = false;
            std::cout << i + 1 << " axiom failed: got " << t << std::endl;
        }
    }
    return flag;
}

bool anti_axiom_tests() {
    std::array<std::string, 11> fake = {
            "A -> B -> B",
            "A | A | A",
            "(A -> A) -> ((A -> B -> C) -> (A -> C))",
            "(A -> B) -> ((A -> B -> C) -> (A -> A))",
            "(A -> B) -> ((B -> B -> C) -> (A -> C))",
            "A & B -> C",
            "A & A -> B",
            "A -> A -> A & B",
            "A -> B -> A & A",
            "A -> B | B",
            // "(A -> C) -> (B -> C) -> (A | B -> C)",
            // "(A -> B) -> ((A -> !B) -> !A)",
            "!!A -> B"
    };
    bool flag = false;
    for (size_t i = 0; i < fake.size(); i++) {
        auto t = NGrammar::check_axiom(TParser().parse(fake[i]));
        if (t != 0) {
            flag = true;
            std::cout << i + 1 << " fake-axiom failed: got " << t << std::endl;
        }
    }
    return !flag;
}

bool start() {
    if (!task1_tests()) return false;
    if (!task2_tests()) return false;
    if (!anti_axiom_tests()) return false;
    if (!axiom_tests()) return false;
    return true;
}

int main() {
    if (!start()) {
        std::cerr << "FAILED";
    } else {
        std::cerr << "PASSED";
    }
    return 0;
}
