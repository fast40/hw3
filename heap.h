#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>
#include <utility>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
        public:
                /**
                 * @brief Construct a new Heap object
                 * 
                 * @param m ary-ness of heap tree (default to 2)
                 * @param c binary predicate function/functor that takes two items
                 *          as an argument and returns a bool if the first argument has
                 *          priority over the second.
                 */
                Heap(int m=2, PComparator c = PComparator());

                /**
                 * @brief Destroy the Heap object
                 * 
                 */
                ~Heap();

                /**
                 * @brief Push an item to the heap
                 * 
                 * @param item item to heap
                 */
                void push(const T& item);

                /**
                 * @brief Returns the top (priority) item
                 * 
                 * @return T const& top priority item
                 * @throw std::underflow_error if the heap is empty
                 */
                T const & top() const;

                /**
                 * @brief Remove the top priority item
                 * 
                 * @throw std::underflow_error if the heap is empty
                 */
                void pop();

                /// returns true if the heap is empty

                /**
                 * @brief Returns true if the heap is empty
                 * 
                 */
                bool empty() const;

                /**
                 * @brief Returns size of the heap
                 * 
                 */
                size_t size() const;

        private:
                /// Add whatever helper functions and data members you need below
                
                std::vector<T> _items;
                int _m;
                PComparator _c;

                int parent(int index) const;
};

// Add implementation of member functions here


template <typename T, typename PComparator>
Heap<T,PComparator>::Heap(int m, PComparator c) : _m(m), _c(c) {}

template <typename T, typename PComparator>
Heap<T,PComparator>::~Heap() {}

template <typename T, typename PComparator>
int Heap<T,PComparator>::parent(int index) const {
        return (index - 1) / _m;
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::push(const T& item) {
        _items.push_back(item);

        int item_index = _items.size() - 1;
        int parent_index = parent(item_index);

        while (item_index > 0) {
                if (_c(_items[parent_index], item)) {
                        break;
                }

                std::swap(_items[item_index], _items[parent_index]);

                item_index = parent_index;
                parent_index = parent(item_index);
        }
}

template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
        if (empty()){
                throw std::underflow_error("Cannot call top on an empty heap.");
        }

        return _items[0];
}

template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
        if (empty()){
                throw std::underflow_error("Cannot call pop on an empty heap.");
        }
        else if (size() == 1) {
                _items.pop_back();
                return;
        }

        std::swap(_items[0], _items[size() - 1]);
        _items.pop_back();

        int index = 0;
        int swap_index = index;

        while (true) {
                swap_index = index;

                for (int child_index = (index * _m) + 1; child_index <= (index * _m) + _m && child_index < static_cast<int>(size()); ++child_index) {
                        if (_c(_items[child_index], _items[swap_index])) {
                                swap_index = child_index;
                        }
                }

                if (swap_index != index) {
                        std::swap(_items[index], _items[swap_index]);
                        index = swap_index;
                }
                else {
                        break;
                }
        }
}

template <typename T, typename PComparator>
bool Heap<T,PComparator>::empty() const {
        return _items.empty();

}

template <typename T, typename PComparator>
size_t Heap<T,PComparator>::size() const {
        return _items.size();
}

#endif
