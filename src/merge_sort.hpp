#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

namespace merge_sort {

/**
 * Sort a range via the Merge sort algorithm,
 * # TODO check if forward iterator suffices( it should )
 * `It` has to be a random access iterator 
 * For the algorithm used see https://en.wikipedia.org/wiki/Merge_sort
 * The algorithm's memory complexity is O(2n) where n := length of the input
 */
template <typename It>
void sort(It begin, It end);

template <typename It>
void sort_impl(It begin, It end, std::random_access_iterator_tag);

template <typename It>
void top_down_split_merge(It B, size_t begin, size_t end, It A);

template <typename It>
void merge(It A, size_t begin, size_t mid, size_t end, It B);

/************************* Implementation *************************/

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
    if (end - begin < 2) {
        // If length is less than 2 consider the range sorted
        return;
    }

    auto mid = (end + begin) / 2;

    // Swap buffers
    top_down_split_merge(A, begin, mid, B);
    top_down_split_merge(A, mid, end, B);

    // Merge in the original order
    merge(B, begin, mid, end, A);
}

template <typename It>
void merge(It A, size_t begin, size_t mid, size_t end, It B) {
    for (auto i = begin, j = mid; begin < end; ++begin) {
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
