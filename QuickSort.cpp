#include <iostream>
#include <vector>

template <typename IteratorType,
          typename ValueType,
          typename Comparator = std::less<ValueType>
>
IteratorType Partition(IteratorType begin, IteratorType end,
                       ValueType value, Comparator comparator = Comparator()) {
    while (begin < end) {
        if (comparator(*begin, value)) {
            ++begin;
        } else if (!comparator(*(end - 1), value)) {
            --end;
        } else {
            std::iter_swap(begin++, --end);
        }
    }
    return begin;
}

template <typename IteratorType,
          typename Comparator = std::less<typename IteratorType::value_type>
>
void QuickSort(IteratorType begin, IteratorType end, 
               Comparator comparator = Comparator()) {
    if (std::distance(begin, end) < 2) {
        return;
    }
    auto pivot_iter = begin;
    std::advance(pivot_iter, std::rand() % std::distance(begin, end));
    auto pivot = *pivot_iter;

    auto middle = Partition(begin, end, pivot, comparator);

    QuickSort(begin, middle);
    while (middle != end && *middle == pivot) {
        ++middle;
    }
    QuickSort(middle, end);
}

