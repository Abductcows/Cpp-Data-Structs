#ifndef CPPDATASTRUCTS_ARRAY_H
#define CPPDATASTRUCTS_ARRAY_H

#include <memory>
#include <cstring>
#include <utility>

namespace gb {
    /**
     * Base unsorted template dynamic array class
     *
     * @tparam T the element type of the array
     */
    template<class T>
    class Array {
    public:
        Array() noexcept;

        /**
         * Creates a new array object with the specified initial capacity
         *
         * @param initialCapacity the desired initial capacity of the array
         */
        explicit Array(int initialCapacity) noexcept;

        virtual ~Array() = default;

        /**
         * Inserts the argument element into the array at the index specified
         *
         * @param index the index of the insertion
         * @param element the element to be inserted
         * @return success status of the insertion
         */
        bool insert(int index, T const &element) noexcept;

        /**
         * Retrieves the element at the specified index into the argument element by reference
         *
         * @param index the index of the retrieval operation
         * @param result storage destination of the retrieved object
         * @return success status of the retrieval
         */
        bool get(int index, T &result) const noexcept;

        /**
         * Updates the element at the specified index with the new argument element
         *
         * @param index index of the update operation
         * @param element the new element to be stored at that index
         * @return success status of the update
         */
        bool set(int index, T const &element) noexcept;

        /**
         * Retrieves and removes the element at the specified index from the array by reference
         *
         * @param index index of the remove operation
         * @param result destination of the removed element
         * @return success status of the removal
         */
        bool remove(int index, T &result) noexcept;

        /// Returns the number of elements in the array
        int size() const;

        /// Returns the current max number of elements allocated by the array
        int trueSize() const;

        bool isEmpty() const;

        /**
         * Resizes the current max number of elements of the array to the desired new size. If the new size is less than
         * the current, the rest of the elements are truncated.
         *
         * @param newSize the new size of the array
         * @return success status of the resize operation
         */
        bool resize(int newSize) noexcept;

        /**
         * Resizes the max number of elements to fit exactly the current number of elements. This is equivalent to
         * `resize(size())`.
         *
         * @return success status of the resize operation
         */
        bool trimToSize() noexcept;

    protected:
        static int const DEFAULT_SIZE = 10;

        std::unique_ptr<T[]> data;
        /// current number of elements
        int elements{0};
        /// length of the data array
        int dataLength{0};

        /**
         * Checks if another element can be inserted into the array and resizes it if necessary. Returns false if no
         * more elements can be inserted.
         *
         * @return wether or not another element can be inserted
         */
        bool ensureCapacity() noexcept;

        /**
         * Doubles the size of the array. Resizes to `DEFAULT_SIZE` if size is 0.
         *
         * @return success status of the resize operation
         */
        bool doubleSize() noexcept;

        /// Index check; returns 0 <= index < val
        bool indexLessThan(int index, int val) const;

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
    bool Array<T>::insert(int index, T const &element) noexcept {
        if (!indexLessThan(index, elements + 1) || !ensureCapacity()) return false;

        std::memmove(data.get() + index + 1, data.get() + index, (elements - index) * sizeof(T);
        data[index] = element;

        return true;
    }

    template<class T>
    bool Array<T>::get(int index, T &result) const noexcept {
        if (!indexLessThan(index, elements)) return false;
        result = data[index];
        return true;
    }

    template<class T>
    bool Array<T>::set(int index, T const &element) noexcept {
        if (!indexLessThan(index, elements)) return false;
        data[index] = element;
        return true;
    }

    template<class T>
    bool Array<T>::remove(int index, T &result) noexcept {
        if (!indexLessThan(index, elements)) return false;
        result = data[index];
        std::memmove(data.get() + index, data.get() + index + 1, (elements - index - 1) * sizeof(T))
        return true;
    }

    template<class T>
    int Array<T>::size() const {
        return elements;
    }

    template<class T>
    int Array<T>::trueSize() const {
        return dataLength;
    }

    template<class T>
    bool Array<T>::isEmpty() const {
        return elements == 0;
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

    template<class T>
    bool Array<T>::indexLessThan(int index, int val) const {
        return 0 <= index && index < val;
    }

}


#endif //CPPDATASTRUCTS_ARRAY_H
