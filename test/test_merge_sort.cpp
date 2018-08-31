#include "merge_sort.hpp"
#include "gtest/gtest.h"
#include <vector>

namespace {
TEST(MergeSort, Easy)
{
    std::vector v { 2, 1, 3 };
    merge_sort::sort(v.begin(), v.end());

    auto begin = v.begin();
    auto next = begin + 1;

    for (; next != v.end(); ++begin, ++next) {
        EXPECT_LE(*begin, *next);
    }
}

TEST(MergeSort, AlreadySorted)
{
    std::vector v { 1, 2, 3 };
    merge_sort::sort(v.begin(), v.end());

    auto begin = v.begin();
    auto next = begin + 1;

    for (; next != v.end(); ++begin, ++next) {
        EXPECT_LE(*begin, *next);
    }
}

TEST(MergeSort, InReverseOrder)
{
    std::vector v { 3, 2, 1 };
    merge_sort::sort(v.begin(), v.end());

    auto begin = v.begin();
    auto next = begin + 1;

    for (; next != v.end(); ++begin, ++next) {
        EXPECT_LE(*begin, *next);
    }
}
}

