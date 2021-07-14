// This is just a test during my time in learning DSA.
// from Introduction to Algorithm by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.
// Created by Thai Tran

#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

void maxHeapify(int* arr, int i, int size) {
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int tmp = 0;
    int largest = i;
    if (l < size && arr[l] > arr[largest]) {
        largest = l;
    }

    if (r < size && arr[r] > arr[largest]) {
        largest = r;
    }

    if (largest != i) {
        tmp = arr[largest];
        arr[largest] = arr[i];
        arr[i] = tmp;
        maxHeapify(arr, largest, size);
    }
}

void buildMaxHeap(int* arr, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, i, size);
    }
}

void heapSort(int* arr, int size) {
    buildMaxHeap(arr, size);
    for (int i = size - 1; i > 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        maxHeapify(arr, 0, i);
    }
}

int main() {
    int arr[5] = {1, 4, 2, 6, 5};
    heapSort(arr, 5);
    for (int i = 0; i < 5; i++)
        cout << arr[i] << ' ';
}