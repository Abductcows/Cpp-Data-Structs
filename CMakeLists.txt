cmake_minimum_required(VERSION 3.19)
project(CppDataStructs)

set(CMAKE_CXX_STANDARD 14)

add_library(CppDataStructs
        src/heaps/BinaryHeap.h src/heaps/MaxHeap.h src/heaps/MinHeap.h
        test/heaps/BinaryHeapTest.cpp

        src/arrays/Array.h
        test/arrays/ArrayTest.cpp

        )

add_executable(main
        test/heaps/BinaryHeapTest.cpp
        test/arrays/ArrayTest.cpp
        )