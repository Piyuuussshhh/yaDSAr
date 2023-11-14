#pragma once

#include <concepts>
#include <vector>
#include <cmath>

#include "min_max_enum.hpp"

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                  DEFINITION                                                    */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T, HeapType type = HeapType::MaxHeap>
        requires std::totally_ordered<T>
    class Heap {
    private:
        std::vector<T> arr;

        void heapify();
        void heapify(const int&);
    public:
        Heap();
        Heap(const T&);

        void push(const T&);
        constexpr size_t size() const;
        bool empty() const;
        T top() const;
        void pop();

        // bool operator==(const Heap&) const;

        ~Heap();
    };

} // namespace data

/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/
/*                                                IMPLEMENTATION                                                  */
/*=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|=|*/

namespace data {

    template <typename T, HeapType type>
    Heap<T, type>::Heap() : {
        this -> arr = vector();
    }

    template <typename T, HeapType type>
    Heap<T, type>::Heap(const T& val) : {
        this -> arr = vector(1, val);
    }

    template <typename T, HeapType type>
    void Heap<T, type>::heapify(const int& idx) {
        int temp = this -> arr[idx], i = idx;
        switch (type) {
            case HeapType::MaxHeap: {
                while (
                    i > 0 &&
                    temp > this -> arr[std::floor(idx / 2)]
                ) {
                    this -> arr[i] = this -> arr[std::floor(idx / 2)];
                    i /= 2;
                }
                this -> arr[i] = temp;

                break;
            }
            case HeapType::MinHeap: {
                while (
                    i > 0 &&
                    temp < this -> arr[std::floor(idx / 2)]
                ) {
                    this -> arr[i] = this -> arr[std::floor(idx / 2)];
                    i /= 2;
                }
                this -> arr[i] = temp;

                break;
            }

            default: return;
        }
    }

    template <typename T, HeapType type>
    bool Heap<T, type>::empty() const {
        return (this -> arr).size() ? true : false;
    }

    template <typename T, HeapType type>
    T Heap<T, type>::top() const {
        return this -> arr[0];
    }

    template <typename T, HeapType type>
    constexpr size_t Heap<T, type>::size() const {
        return (this -> arr).size();
    }

    template <typename T, HeapType type>
    void Heap<T, type>::push(const T& val) {
        (this -> arr).push_back(val);
        heapify(this -> size() - 1);
    }

    template <typename T, HeapType type>
    void Heap<T, type>::pop() {
        (this -> arr).erase((this -> arr).begin());
        heapify();
    }

    template <typename T, HeapType type>
    Heap<T, type>::~Heap() {}

} // namespace data

