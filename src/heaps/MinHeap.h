#ifndef MINHEAP_H
#define MINHEAP_H

#include "BinaryHeap.h"
#include <cstring>

namespace gb {
    template<class T>
    class MinHeap : public BinaryHeap<T> {
    public:
        MinHeap();

        explicit MinHeap(int initialLength);

        MinHeap(MinHeap const &);

        ~MinHeap();

    private:
        int compare(T &, T &);
    };

    template<class T>
    MinHeap<T>::MinHeap() : BinaryHeap<T>() {

    }

    template<class T>
    MinHeap<T>::MinHeap(int initialLength) : BinaryHeap<T>(initialLength) {

    }

    template<class T>
    MinHeap<T>::MinHeap(MinHeap const &other) : BinaryHeap<T>(other.dataLength) {
        this->elements = other.elements;
        memcpy(this->data.get(), other.data.get(), other.elements * sizeof(int));
    }

    template<class T>
    MinHeap<T>::~MinHeap() = default;

    template<class T>
    int MinHeap<T>::compare(T &e1, T &e2) {
        if (e1 < e2) {
            return -1;
        }
        if (e1 == e2) {
            return 0;
        }
        return 1;
    }
}

#endif // MINHEAP_H
