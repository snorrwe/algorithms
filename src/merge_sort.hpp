#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

namespace merge_sort {

template <typename T, typename It>
class MergeSortImpl;

template <typename It>
void sort(It begin, It end)
{
    using category = typename std::iterator_traits<It>::iterator_category;
    using value_type = typename std::iterator_traits<It>::value_type;
    auto sorter = MergeSortImpl<value_type, It> { begin, end, category() };
    sorter.sort();
}

template <typename T, typename It>
class MergeSortImpl {
    using Container = std::vector<T>;

    It begin;
    It end;
    Container A;
    Container B;

public:
    MergeSortImpl(It begin, It end, std::random_access_iterator_tag)
        : begin(begin)
        , end(end)
    {
    }

    void sort()
    {
        auto size = end - begin;
        A.reserve(size);
        std::copy(begin, end, std::back_inserter(A));
        B.reserve(size);
        std::copy(begin, end, std::back_inserter(B));

        top_down_split_merge(B, 0, size - 1, A);

        // Copy the result back to the original range
        std::copy(A.begin(), A.end(), begin);
    }

private:
    static void top_down_split_merge(Container& B, size_t begin, size_t end, Container& A)
    {
        // If length is less than 2 consider the range sorted
        if (end - begin < 2)
            return;

        auto mid = (end - begin) / 2;

        top_down_split_merge(A, begin, mid, B);
        top_down_split_merge(A, mid, end, B);

        merge(B, begin, mid, end, A);
    }

    static void merge(Container& A, size_t begin, size_t mid, size_t end, Container& B)
    {
        auto i = begin, j = mid;
        for (; begin != end; ++begin) {
            if (begin <= mid && (j >= end || A[i] <= A[j])) {
                A[begin] = B[i];
                ++i;
            } else {
                A[begin] = B[j];
                ++j;
            }
        }
    }
};

} // namespace merge_sort

