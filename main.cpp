#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "src/heaps/MinHeap.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

void extractAllAndPrint(gb::MinHeap<int> &heap);

int main() {
    int N = 101;

    gb::MinHeap<int> minh(N / 2);
    //MaxHeap maxh(N/2);


    srand(time(nullptr));
    cout << "Insertions:\n";
    for (int i = 0; i < N; i++) {
        int element = rand() % N;
        cout << element << " ";
        minh.insert(element);
        //maxh.insert(element);
    }

    cout << endl << endl << "Sizes: MinHeap = " << minh.size()

         //<< " MaxHeap = " << maxh.size()
         << endl;

    cout << "Allocated = " << minh.trueSize() << endl;

    cout << "\nExtractions:\n\n";
    cout << "Minheap:\n";
    extractAllAndPrint(minh);
    extractAllAndPrint(minh);

    gb::MinHeap<int> second(minh);
    extractAllAndPrint(second);
    //cout << "\n\nMaxheap:\n";
    //extractAllAndPrint(&maxh);
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