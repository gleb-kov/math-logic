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
    for (auto & sample : samples) {
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

bool task2_test() {
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

bool start() {
    if (!task1_tests()) return false;
    if (!task2_test()) return false;
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
