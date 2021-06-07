#ifndef MAXHEAP_H
#define MAXHEAP_H

#include "BinaryHeap.h"
#include <cstring>

namespace gb {
    template<class T>
    class MaxHeap : public BinaryHeap<T> {
    public:
        MaxHeap();

        explicit MaxHeap(int initialLength);

        MaxHeap(MaxHeap<T> const &);

        ~MaxHeap();

    private:
        int compare(T &, T &);
    };

    template<class T>
    MaxHeap<T>::MaxHeap() : BinaryHeap<T>() {

    }

    template<class T>
    MaxHeap<T>::MaxHeap(int initialLength) : BinaryHeap<T>(initialLength) {

    }

    template<class T>
    MaxHeap<T>::MaxHeap(MaxHeap const &other) : BinaryHeap<T>(other.dataLength) {
        this->elements = other.elements;
        memcpy(this->data.get(), other.data.get(), other.elements * sizeof(T));
    }

    template<class T>
    MaxHeap<T>::~MaxHeap() = default;

    template<class T>
    int MaxHeap<T>::compare(T &e1, T &e2) {
        if (e1 < e2) {
            return 1;
        }
        if (e1 == e2) {
            return 0;
        }
        return -1;
    }
}

#endif // MAXHEAP_H
