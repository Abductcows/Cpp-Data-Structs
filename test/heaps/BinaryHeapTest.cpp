#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "../../src/heaps/MinHeap.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

template <class T>
void extractAllAndPrint(gb::MinHeap<T> &);

int amain() {
    int N = 101;

    gb::MinHeap<int> heap(N / 2);
    //gb::MaxHeap<int> heap(N/2);


    srand(time(nullptr));
    cout << "Insertions:\n";
    for (int i = 0; i < N; i++) {
        int element = rand() % N;
        cout << element << " ";
        heap.insert(element);
    }

    cout << endl << endl << "Size = " << heap.size() << endl;
    cout << "Allocated = " << heap.trueSize() << endl;
    cout << "\nExtractions:\n\n";

    extractAllAndPrint(heap);
    return 0;
}

template <class T>
void extractAllAndPrint(gb::MinHeap<T> &heap) {
    while (!heap.isEmpty()) {
        T element = heap.extractRoot();
        cout << element << " ";
    }
    cout << "\n\n";
}


#pragma clang diagnostic pop