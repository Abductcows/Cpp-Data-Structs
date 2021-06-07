#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "../../src/heaps/MinHeap.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

void extractAllAndPrint(gb::MinHeap<int> &heap);

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
        //maxh.insert(element);
    }

    cout << endl << endl << "Sizes: MinHeap = " << heap.size()

         //<< " MaxHeap = " << maxh.size()
         << endl;

    cout << "Allocated = " << heap.trueSize() << endl;

    cout << "\nExtractions:\n\n";
    extractAllAndPrint(heap);
    extractAllAndPrint(heap);

    gb::MinHeap<int> second(heap);
    extractAllAndPrint(second);
    return 0;
}

void extractAllAndPrint(gb::MinHeap<int> &heap) {
    while (!heap.isEmpty()) {
        int element = heap.extractRoot();
        cout << element << " ";
    }
    cout << "\n\n";
}


#pragma clang diagnostic pop