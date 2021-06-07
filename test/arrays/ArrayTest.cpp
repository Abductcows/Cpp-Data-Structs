#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-msc50-cpp"

#include "../../src/arrays/Array.h"
#include <iostream>
#include <random>
#include <ctime>

using namespace std;

template<class T>
void printArray(gb::Array<T> &);

int bmain() {
    int N = 101;

    gb::Array<int> arr(N / 2);


    srand(time(nullptr));
    cout << "Insertions:\n";
    for (int i = 0; i < N; i++) {
        int element = rand() % N;
        cout << element << " ";
        arr.insert(i, element);
    }

    cout << endl << endl << "Size = " << arr.size() << endl;
    cout << "Allocated = " << arr.trueSize() << endl;

    cout << "\nElements:\n";
    printArray(arr);

    return 0;
}

template<class T>
void printArray(gb::Array<T> &arr) {
    for (int i = 0; i < arr.size(); i++) {
        T element;
        arr.get(i, element);
        cout << element << " ";
    }
    cout << "\n\n";
}


#pragma clang diagnostic pop