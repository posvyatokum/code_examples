#include <iostream>
#include <vector>

template <
    typename IteratorType,
    typename ValueType = typename std::iterator_traits<IteratorType>::value_type,
    typename Comparator = std::less<ValueType>
>
void Merge(IteratorType first_begin, IteratorType first_end, 
           IteratorType second_begin, IteratorType second_end, 
           IteratorType result, 
           Comparator comparator = Comparator()) {
    while (first_begin != first_end && second_begin != second_end) {
        *(result++) = comparator(*second_begin, *first_begin) ? *(second_begin++) : *(first_begin++);
    }
    while (first_begin != first_end || second_begin != second_end) {
        *(result++) = first_begin != first_end ? *(first_begin++) : *(second_begin++);
    }
}

template <typename IteratorType,
          typename Comparator = std::less<typename IteratorType::value_type>
>
void MergeSort(IteratorType begin, IteratorType end, IteratorType buffer,
               Comparator comparator = Comparator()) {
    if (std::distance(begin, end) < 2) {
        return;
    }
    auto middle = begin;
    std::advance(middle, std::distance(begin, end) / 2);
    MergeSort(begin, middle, buffer, comparator);
    MergeSort(middle, end, buffer, comparator);
    Merge(begin, middle,
          middle, end,
          buffer, comparator);
    std::copy(buffer, buffer + std::distance(begin, end), begin);
}

template <typename IteratorType,
          typename Comparator = std::less<typename IteratorType::value_type>
>
void MergeSort(IteratorType begin, IteratorType end,
               Comparator comparator = Comparator()) {
    std::vector<typename IteratorType::value_type> buffer(std::distance(begin, end));
    MergeSort(begin, end, buffer.begin(), comparator);
}
