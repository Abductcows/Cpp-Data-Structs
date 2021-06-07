//
// Created by abduc on 6/7/2021.
//

#ifndef CPPDATASTRUCTS_ARRAY_H
#define CPPDATASTRUCTS_ARRAY_H

#include <memory>
#include <cstring>
#include <utility>

namespace gb {
    template<class T>
    class Array {
    public:
        Array();

        explicit Array(int initialCapacity) noexcept;

        virtual ~Array() = default;

        bool insert(T element) noexcept;

        bool get(int index, T &result) const noexcept;

        bool set(int index, T element) noexcept;

        bool remove(int index, T &result) noexcept;

        int size() const;

        int trueSize() const;

        bool isEmpty() const;

        bool resize(int newSize) noexcept;

        bool trimToSize() noexcept;

    protected:
        static int const DEFAULT_SIZE = 10;

        std::unique_ptr<T[]> data;
        int elements{0};
        int dataLength{0};

        bool ensureCapacity() noexcept;

        bool doubleSize() noexcept;

    private:


    };

    template<class T>
    Array<T>::Array() : Array(DEFAULT_SIZE) {

    }

    template<class T>
    Array<T>::Array(int initialCapacity) noexcept {
        if (initialCapacity < 0) {
            initialCapacity = DEFAULT_SIZE
        }

        data = std::make_unique<T[]>(initialCapacity);
        dataLength = initialCapacity;
        elements = 0;
    }

    template<class T>
    bool Array<T>::insert(T element) noexcept {
        return false;
    }

    template<class T>
    bool Array<T>::get(int index, T &result) const noexcept {
        return false;
    }

    template<class T>
    bool Array<T>::set(int index, T element) noexcept {
        return false;
    }

    template<class T>
    bool Array<T>::remove(int index, T &result) noexcept {
        return false;
    }

    template<class T>
    int Array<T>::size() const {
        return 0;
    }

    template<class T>
    int Array<T>::trueSize() const {
        return 0;
    }

    template<class T>
    bool Array<T>::isEmpty() const {
        return false;
    }

    template<class T>
    bool Array<T>::resize(int newSize) {
        if (newSize < 0) {
            return false;
        }

        // create temp pointer and copy
        std::unique_ptr<T[]> newData;
        try {
            newData = std::make_unique<T[]>(newSize);
        } catch (std::bad_alloc &e) {
            return false;
        }
        std::memcpy(newData.get(), data.get(), newSize * sizeof(T));

        // move to data and delete temp pointer
        data.swap(newData);
        newData.reset();

        // update size fields
        dataLength = newSize;
        // if elements were truncated, update count
        elements = std::min(elements, newSize);
        return true;
    }

    template<class T>
    bool Array<T>::trimToSize() {
        if (dataLength == elements) {
            // (already trimmed)
            return true;
        }

        return resize(elements);
    }

    template<class T>
    bool Array<T>::ensureCapacity() {
        if (dataLength > elements) {
            return true; // not yet full
        }
        // try to double size
        return doubleSize();
    }

    template<class T>
    bool Array<T>::doubleSize() {
        if (dataLength == 0) {
            return resize(DEFAULT_SIZE);
        }
        return resize(2 * dataLength);
    }

}


#endif //CPPDATASTRUCTS_ARRAY_H
