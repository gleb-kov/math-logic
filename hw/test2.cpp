#include "gtest/gtest.h"

#include "godel.h"

using namespace godel;

TEST(cons, brute) {
    ASSERT_EQ(1, cons<ull>::compute({0, 0}));
    ASSERT_EQ(2, cons<ull>::compute({1, 0}));
    ASSERT_EQ(4, cons<ull>::compute({2, 0}));

    ASSERT_EQ(1, cons<ull>::compute({0, 1}));
    ASSERT_EQ(3, cons<ull>::compute({0, 2}));
    ASSERT_EQ(5, cons<ull>::compute({0, 3}));
    ASSERT_EQ(9, cons<ull>::compute({0, 4}));
    ASSERT_EQ(7, cons<ull>::compute({0, 5}));
}

TEST(head, brute) {
    ASSERT_EQ(0, head<ull>::compute({1}));
    ASSERT_EQ(1, head<ull>::compute({2}));
    ASSERT_EQ(0, head<ull>::compute({3}));
    ASSERT_EQ(2, head<ull>::compute({4}));
    ASSERT_EQ(0, head<ull>::compute({5}));
    ASSERT_EQ(1, head<ull>::compute({6}));
    ASSERT_EQ(0, head<ull>::compute({7}));
    ASSERT_EQ(3, head<ull>::compute({8}));
}

TEST(tail, brute) {
    ASSERT_EQ(0, tail<ull>::compute({1}));
    ASSERT_EQ(1, tail<ull>::compute({2}));
    ASSERT_EQ(1, tail<ull>::compute({3}));
    ASSERT_EQ(2, tail<ull>::compute({4}));
    ASSERT_EQ(1, tail<ull>::compute({5}));
    ASSERT_EQ(1, tail<ull>::compute({6}));
    ASSERT_EQ(1, tail<ull>::compute({7}));
    ASSERT_EQ(3, tail<ull>::compute({8}));
}

TEST(len, brute) {
    ASSERT_EQ(0, len<ull>::compute({0}));
    ASSERT_EQ(1, len<ull>::compute({1}));
    ASSERT_EQ(1, len<ull>::compute({2}));
    ASSERT_EQ(2, len<ull>::compute({3}));
    ASSERT_EQ(1, len<ull>::compute({4}));
    ASSERT_EQ(3, len<ull>::compute({5}));
    ASSERT_EQ(2, len<ull>::compute({6}));
    ASSERT_EQ(4, len<ull>::compute({7}));
    ASSERT_EQ(1, len<ull>::compute({8}));
}

TEST(concat, brute) {
    ASSERT_EQ(1, concatenate<ull>::compute({1, 0}));
    ASSERT_EQ(2, concatenate<ull>::compute({2, 0}));
    ASSERT_EQ(3, concatenate<ull>::compute({3, 0}));
    ASSERT_EQ(4, concatenate<ull>::compute({4, 0}));
    ASSERT_EQ(5, concatenate<ull>::compute({5, 0}));

    ASSERT_EQ(0, concatenate<ull>::compute({0, 0}));
    ASSERT_EQ(1, concatenate<ull>::compute({0, 1}));
    ASSERT_EQ(2, concatenate<ull>::compute({0, 2}));
    ASSERT_EQ(3, concatenate<ull>::compute({0, 3}));
    ASSERT_EQ(4, concatenate<ull>::compute({0, 4}));
    ASSERT_EQ(5, concatenate<ull>::compute({0, 5}));

    ASSERT_EQ(3, concatenate<ull>::compute({1, 2})); // 01
    ASSERT_EQ(6, concatenate<ull>::compute({2, 2})); // 11
    ASSERT_EQ(15, concatenate<ull>::compute({3, 2})); // 011
    ASSERT_EQ(12, concatenate<ull>::compute({4, 2})); // 21
    ASSERT_EQ(35, concatenate<ull>::compute({5, 2})); // 0011

    ASSERT_EQ(15, concatenate<ull>::compute({1, 6})); // 011
    ASSERT_EQ(30, concatenate<ull>::compute({2, 6})); // 111
    ASSERT_EQ(105, concatenate<ull>::compute({3, 6})); // 0111
    ASSERT_EQ(60, concatenate<ull>::compute({4, 6})); // 211
}
