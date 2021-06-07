#ifndef BINARYHEAP_H
#define BINARYHEAP_H

#include <memory>
#include <cstring>
#include <utility>

namespace gb {
    template<class T>
    class BinaryHeap {
    public:
        BinaryHeap();

        explicit BinaryHeap(int initialCapacity);

        virtual ~BinaryHeap();

        void insert(T element) noexcept;

        T peek() const;

        T extractRoot();

        int size() const;

        int trueSize() const;

        bool isEmpty() const;

    protected:
        static int const DEFAULT_SIZE = 10;

        std::unique_ptr<T[]> data;

        int elements{0};

        int dataLength{0};

        virtual int compare(T &, T &) = 0;

    private:
        bool doubleSize();

        void heapifyUp(int index);

        void heapifyDown(int index);
    };


    template<class T>
    BinaryHeap<T>::BinaryHeap() : BinaryHeap(BinaryHeap<T>::DEFAULT_SIZE) {

    }

    template<class T>
    BinaryHeap<T>::BinaryHeap(int initialCapacity) {
        // check for non-positive value of length
        if (initialCapacity <= 0) {
            initialCapacity = BinaryHeap::DEFAULT_SIZE;
        }
        // set the data array length to the specified length
        dataLength = initialCapacity;
        // allocate memory for the data array
        data = std::make_unique<T[]>(initialCapacity);
        // set the current # of elements to 0
        elements = 0;
    }

    template<class T>
    BinaryHeap<T>::~BinaryHeap() = default;

    template<class T>
    void BinaryHeap<T>::insert(T element) noexcept {
        // if heap is full, resize
        if (elements == dataLength) {
            doubleSize();
        }
        // add element after current last
        data[elements] = element;
        // increment size
        elements = elements + 1;
        // heapify up from the new element to restore heap property
        heapifyUp(elements - 1);
    }

    template<class T>
    T BinaryHeap<T>::peek() const {
        return data[0];
    }

    template<class T>
    T BinaryHeap<T>::extractRoot() {
        // get root element value
        int result = peek();

        // swap final element with root
        std::swap(data[0], data[elements - 1]);
        // decrement size
        elements = elements - 1;
        // heapify down from root to restore heap property
        heapifyDown(0);

        return result;
    }

    template<class T>
    int BinaryHeap<T>::size() const {
        return elements;
    }

    template<class T>
    int BinaryHeap<T>::trueSize() const {
        return dataLength;
    }

    template<class T>
    bool BinaryHeap<T>::isEmpty() const {
        return size() == 0;
    }

    template<class T>
    void BinaryHeap<T>::heapifyUp(int index) {
        // get parent index
        int parentIndex = (index - 1) / 2;

        // if current is less than parent, swap and continue up
        if (parentIndex >= 0
            && compare(data[index], data[parentIndex]) < 0) {
            std::swap(data[index], data[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    template<class T>
    void BinaryHeap<T>::heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = leftChild + 1;
        int minChildIndex;

        // find if it has 2, 0 or 1 children in that order
        // (optimal since it is called at root)

        if (rightChild < elements) {        // 2 children
            minChildIndex = compare(data[leftChild], data[rightChild]) < 0 ? leftChild : rightChild;
        } else if (rightChild > elements) { // leaf node
            return;
        } else {                            // 1 child, the left one
            std::swap(data[leftChild], data[index]);
            return;
        }

        // if min child is less than current, swap and continue down
        if (compare(data[minChildIndex], data[index]) < 0) {
            std::swap(data[minChildIndex], data[index]);
            heapifyDown(minChildIndex);
        }
    }

    template<class T>
    bool BinaryHeap<T>::doubleSize() {
        // create new array

        int newLength = dataLength * 2;
        std::unique_ptr<T[]> tempData;
        try {
            tempData = std::make_unique<T[]>(newLength);
        } catch (std::bad_alloc &e) {
            return false;
        }

        // copy all elements to the new array
        memcpy(tempData.get(), data.get(), elements * sizeof(T));

        // swap the pointers and delete the temp pointer
        data.swap(tempData);
        tempData.reset();

        // set pointer bounds to the new value
        dataLength = newLength;
        return true;
    }
}

#endif //BINARYHEAP_H
