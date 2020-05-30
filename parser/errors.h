#ifndef MATLOG_ERRORS_H
#define MATLOG_ERRORS_H

#include <stdexcept>

class parser_error : public std::runtime_error {
public:
    using std::runtime_error::what;

    parser_error() : std::runtime_error("Parsing error") {}

    explicit parser_error(const char *m) : std::runtime_error(m) {}
};

class proof_error : public std::runtime_error {
private:
    static constexpr std::string_view v1 = "Proof is incorrect";

    static constexpr std::string_view v2 = "The proof proves different expression.";

public:
    using std::runtime_error::what;

    explicit proof_error(bool verbose = false) : std::runtime_error(decide(verbose)) {}

    proof_error(bool verbose, std::string const &m) : std::runtime_error(decide(verbose, m)) {}

private:
    static constexpr const char *decide(bool verbose) {
        return (verbose ? v2.data() : v1.data());
    }

    static const char *decide(bool verbose, std::string const &m) {
        return (verbose ? m.data() : v1.data());
    }
};


[[noreturn]] inline void generate_proof_error(bool verbose, size_t n) noexcept(false) {
    throw proof_error(verbose, "Expression " + std::to_string(n) + " is not proved.");
}

/*[[noreturn]] inline void generate_proof_error(bool verbose, size_t n, TVariable const &) noexcept(false) {
    throw proof_error(verbose, "Expression " + std::to_string(n) + ": variable v occurs free in ?@-rule.");
}

[[noreturn]] inline void generate_proof_error(bool verbose,
                                              size_t n,
                                              TVariable const &,
                                              NGrammar::expr const &) noexcept(false) {
    throw proof_error(verbose, "Expression " + std::to_string(n) + ": variable v is not free for term t in ?@-axiom");
}*/

#endif //MATLOG_ERRORS_H
