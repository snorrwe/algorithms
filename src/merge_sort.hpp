#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

namespace merge_sort {

/**
 * Sort a range via the merge sort algorithm, It needs to be a random access
 * iterator
 */
template <typename It>
void sort(It begin, It end);

template <typename It>
void sort_impl(It begin, It end, std::random_access_iterator_tag);

template <typename It>
void top_down_split_merge(It B, size_t begin, size_t end, It A);

template <typename It>
void merge(It A, size_t begin, size_t mid, size_t end, It B);

template <typename It>
void sort(It begin, It end) {
    using category = typename std::iterator_traits<It>::iterator_category;
    sort_impl(begin, end, category());
}

template <typename It>
void sort_impl(It begin, It end, std::random_access_iterator_tag) {
    using TValue = typename std::iterator_traits<It>::value_type;
    const auto size = end - begin;

    std::vector<TValue> working_container;
    working_container.reserve(size);
    std::copy(begin, end, std::back_inserter(working_container));

    top_down_split_merge(working_container.begin(), 0, size, begin);
}

template <typename It>
void top_down_split_merge(It B, size_t begin, size_t end, It A) {
    // If length is less than 2 consider the range sorted
    if (end - begin < 2) {
        return;
    }

    auto mid = (end + begin) / 2;

    top_down_split_merge(A, begin, mid, B);
    top_down_split_merge(A, mid, end, B);

    merge(B, begin, mid, end, A);
}

template <typename It>
void merge(It A, size_t begin, size_t mid, size_t end, It B) {
    auto i = begin, j = mid;
    for (; begin < end; ++begin) {
        if (i < mid && (j >= end || *(A + i) <= *(A + j))) {
            *(B + begin) = *(A + i);
            ++i;
        } else {
            *(B + begin) = *(A + j);
            ++j;
        }
    }
}

}  // namespace merge_sort
