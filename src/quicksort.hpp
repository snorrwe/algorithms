#pragma once
#include <iterator>
#include <utility>

namespace quicksort {

template <typename It>
void sort(It begin, It end);

template <typename It>
void sort_impl(It begin, It end, std::random_access_iterator_tag);

template <typename It>
void sort(It begin, It end) {
    using category = typename std::iterator_traits<It>::iterator_category;
    sort_impl(begin, end, category());
}

template <typename It>
void sort_impl(It begin, It end, std::random_access_iterator_tag tag) {
    using TValue = typename std::iterator_traits<It>::value_type;

    if (begin == end) {
        return;
    }

    auto part = partition(begin, end);
    sort_impl(begin, part, tag);
    sort_impl(part + 1, end, tag);
}

template <typename It>
auto partition(It begin, It end) {
    using std::swap;

    --end;
    auto pivot = end;
    auto i = begin;
    for (auto j = begin; j != end; ++j) {
        if (*j < *pivot) {
            swap(*i, *j);
            ++i;
        }
    }
    swap(*i, *pivot);
    return i;
}
}  // namespace quicksort
