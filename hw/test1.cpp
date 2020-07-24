#include "gtest/gtest.h"
#include "recursive.h"

using recursive::ull;
using namespace recursive::operations;

namespace check {
    ull pow(ull l, ull r) {
        ull res = 1;
        while (r) {
            res *= l;
            r--;
        }
        return res;
    }

    ull factorial(ull l) {
        ull res = 1;
        while (l > 1) {
            res *= l;
            l--;
        }
        return res;
    }

    ull plog(ull n, ull p) {
        ull k = 0;
        while (n > 0 && n%p == 0) {
            k++;
            n/=p;
        }
        return k;
    }

    ull isprime(ull n) {
        for (ull i = 2; i * i <= n; i++) {
            if (n%i == 0) return 0;
        }
        return (ull)(n > 1);
    }
}

TEST(add, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 0; j <= 10; j++) {
            ASSERT_EQ(i + j, add<ull>::compute({i, j}));
        }
    }
}

TEST(multiply, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 0; j <= 10; j++) {
            ASSERT_EQ(i * j, mul<ull>::compute({i, j}));
        }
    }
}

TEST(bound_sub1, brute) {
    ASSERT_EQ(0, bounded_sub1<ull>::compute({0}));
    for (ull i = 1; i <= 10; i++) {
        ASSERT_EQ(i - 1, bounded_sub1<ull>::compute({i}));
    }
}

TEST(bound_sub, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 0; j <= i; j++) {
            ASSERT_EQ(i-j, bounded_sub<ull>::compute({i, j}));
            ASSERT_EQ(0, bounded_sub<ull>::compute({j, i}));
        }
    }
}

TEST(less, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 0; j <= 10; j++) {
            ASSERT_EQ((ull)(i < j), less<ull>::compute({i, j}));
        }
    }
}

TEST(div, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 1; j <= 10; j++) {
            ASSERT_EQ(i/j, recursive::operations::div<ull>::compute({i, j}));
        }
    }
}

TEST(modulo, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 1; j <= 10; j++) {
            ASSERT_EQ(i%j, modulo<ull>::compute({i, j}));
        }
    }
}

TEST(pow, brute) {
    for (ull i = 0; i <= 10; i++) {
        for (ull j = 0; j <= 5; j++) {
            ASSERT_EQ(check::pow(i, j), pow<ull>::compute({i, j}));
        }
    }
}

TEST(factorial, brute) {
    for (ull i = 0; i <= 5; i++) {
        ASSERT_EQ(check::factorial(i), factorial<ull>::compute({i}));
    }
}

TEST(plog, brute) {
    for (ull i = 0; i <= 5; i++) {
        for (ull j = 2; j <= 5; j++) {
            ASSERT_EQ(check::plog(i, j), plog<ull>::compute({i, j}));
        }
    }
    ASSERT_EQ(2, plog<ull>::compute({72, 6}));
}

TEST(pair, simple) {
    ASSERT_EQ(1, produce_pair<ull>::compute({0, 0}));
    ASSERT_EQ(2, produce_pair<ull>::compute({1, 0}));
    ASSERT_EQ(3, produce_pair<ull>::compute({0, 1}));
    ASSERT_EQ(6, produce_pair<ull>::compute({1, 1}));

    ASSERT_EQ(1, pi_left<ull>::compute({2}));
    ASSERT_EQ(0, pi_right<ull>::compute({2}));

    ASSERT_EQ(1, pi_left<ull>::compute({6}));
    ASSERT_EQ(1, pi_right<ull>::compute({6}));
}

TEST(isprime, brute) {
    for (ull i = 0; i <= 15; i++) {
        ASSERT_EQ(check::isprime(i), is_prime<ull>::compute({i}));
    }
}

TEST(band, brute) {
    for (ull i = 0; i < 2; i++) {
        for (ull j = 0; j < 2; j++) {
            ASSERT_EQ((ull)(i&j), bitwise_and<ull>::compute({i, j}));
        }
    }
}

TEST(bxor, brute) {
    for (ull i = 0; i < 2; i++) {
        for (ull j = 0; j < 2; j++) {
            ASSERT_EQ((ull)(i^j), bitwise_xor<ull>::compute({i, j}));
        }
    }
}

TEST(firsttt, simple) {
    ull res = firstyy<1, ull, one<ull, 2>>::compute({0, 3});
    ASSERT_EQ(0, res);
    ull res2 = firstyy<1, ull, zero<ull, 2>>::compute({0, 3});
    ASSERT_EQ(3, res2);
    ull res3 = firstyy<1, ull, S2<is_equal<ull>, one<ull, 2>, U<2,2,ull>, ull>>::compute({0, 3});
    ASSERT_EQ(1, res3);
}
