#include "../gtest/gtest.h"
#include "../lib/ackermann.h"

// expect n+1
TEST(zerom, simple) {
    ASSERT_EQ(1, ackermann::solve({0, 0})[0]);
    ASSERT_EQ(2, ackermann::solve({1, 0})[0]);
    ASSERT_EQ(3, ackermann::solve({2, 0})[0]);

    ASSERT_EQ(1, ackermann2::solve({0, 0})[0]);
    ASSERT_EQ(2, ackermann2::solve({1, 0})[0]);
    ASSERT_EQ(3, ackermann2::solve({2, 0})[0]);
}

// expect n+2
TEST(onem, simple) {
    ASSERT_EQ(2, ackermann::solve({0, 1})[0]);
    ASSERT_EQ(3, ackermann::solve({1, 1})[0]);

    ASSERT_EQ(2, ackermann2::solve({0, 1})[0]);
    ASSERT_EQ(3, ackermann2::solve({1, 1})[0]);
}

TEST(zeron, simple) {
    for (ull i = 0; i <= 10; i++) {
        ASSERT_EQ(i+1, ackermann::solve({0, i})[0]);
        ASSERT_EQ(i+1, ackermann2::solve({0, i})[0]);
    }
}

TEST(verif, simple) {
    ASSERT_EQ(4, ackermann2::solve({1, 2})[0]);
    ASSERT_EQ(5, ackermann2::solve({2, 1})[0]);

    // infinity time
    // ASSERT_EQ(4, ackermann::solve({1, 2})[0]);
    ASSERT_TRUE(ackermann::validate_ackermann(ackermann::apply_operations({1, 2}, 415800)));
}
