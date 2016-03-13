#include <iostream>
#include <vector>

using std::vector;

namespace heap {
    template <typename ValueType, 
              typename Comparator = std::less <ValueType>
             >
    class Heap {
        vector<ValueType> heap_;
        vector<size_t> point_to_id_;
        vector<size_t> id_to_point_;
        Comparator comparator;

        size_t Parent(size_t point) const {
            return point / 2;
        }

        size_t LeftChild(size_t point) const {
            return point * 2 < heap_.size() ? point * 2 : 0;
        }

        size_t RightChild(size_t point) const {
            return (1 + point * 2) < heap_.size() ? 1 + point * 2 : 0;
        }

        void Swap (size_t first_point, size_t second_point) {
            std::swap(heap_[first_point], heap_[second_point]);
            std::swap(point_to_id_[first_point], point_to_id_[second_point]);
            std::swap(id_to_point_[point_to_id_[first_point]], id_to_point_[point_to_id_[second_point]]);
        }

        void SiftUp(size_t point) {
            while (Parent(point) && comparator(heap_[point], heap_[Parent(point)])) {
                Swap(point, Parent(point));
                point = Parent(point);
            }
        }

        void SiftDown(size_t point) {
            while ((LeftChild(point) && comparator(heap_[LeftChild(point)], heap_[point])) ||
                    (RightChild(point) && comparator(heap_[RightChild(point)], heap_[point]))) {
                if (!RightChild(point)) {
                    Swap(point, LeftChild(point));
                    point = LeftChild(point);
                    continue;
                }
                if (comparator(heap_[LeftChild(point)], heap_[RightChild(point)])) {
                    Swap(point, LeftChild(point));
                    point = LeftChild(point);
                } else {
                    Swap(point, RightChild(point));
                    point = RightChild(point);
                }
            }
        }

        public:
        explicit Heap(int max_num, Comparator comparator = Comparator()): 
            heap_(1), 
            point_to_id_(1), 
            id_to_point_(max_num), 
            comparator(comparator) 
        {}

        void insert(const ValueType &value, size_t id) {
            heap_.push_back(value);
            point_to_id_.push_back(id);
            id_to_point_[id] = point_to_id_.size() - 1;
            SiftUp(heap_.size() - 1);
        }

        void extract_min() {
            Swap(1, heap_.size() - 1);
            heap_.pop_back();
            id_to_point_[point_to_id_[point_to_id_.size() - 1]] = 0;
            point_to_id_.pop_back();
            SiftDown(1);
        }

        void decrease (size_t id, const ValueType &val) {
            size_t point = id_to_point_[id];
            heap_[point] = val;
            SiftUp(point);
        }

        const ValueType &get_min() const {
            return heap_[1];
        }

        size_t size() const {
            return heap_.size() - 1;
        }

        bool empty() const {
            return size() == 0;
        }
    };
}

