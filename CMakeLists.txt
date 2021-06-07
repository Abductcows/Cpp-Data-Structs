cmake_minimum_required(VERSION 3.19)
project(CppDataStructs)

set(CMAKE_CXX_STANDARD 14)

add_library(CppDataStructs src/heaps/BinaryHeap.h src/heaps/MaxHeap.h src/heaps/MinHeap.h main.cpp)
add_executable(main main.cpp)