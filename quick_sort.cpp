// This is just a test during my time in learning DSA.
// from Introduction to Algorithm by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.
// Created by Thai Tran

#include <iostream>
#include <random>
#include <chrono>
#include <string>
#include <fstream>

using namespace std::chrono;
using namespace std;

void print(int* arr, int left, int right) {
    cout << "print: " << endl;
    for (int i = left; i <= right; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

void swap(int& a, int& b) {
    int tmp = a;
    a = b;
    b = tmp;
}

class QuickSort {
public:
    int partition(int* arr, int left, int right) {
        int indx = left - 1;
        for (int i = left; i <= right - 1; i++) {
            if (arr[i] <= arr[right]) {
                indx++;
                swap(arr[i], arr[indx]);
            }
        }
        indx++;
        swap(arr[indx], arr[right]);
        return indx;
    }

    void quicksort(int* arr, int left, int right) {
        if (left < right) {
            int p = partition(arr, left, right);
            quicksort(arr, left, p - 1);
            quicksort(arr, p + 1, right);
        }
    }

    int quicksort(int* arr, int size) {
        auto start = high_resolution_clock::now();
        quicksort(arr, 0, size - 1);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Quick sort execution time: " << duration.count() << " ns\n";
        string fileName = "quicksort_result.txt";
        fstream fileOut(fileName, ios::out);
        for (int i = 0; i < size; i++)
            fileOut << arr[i] << ' ';
        return duration.count();
    }
};

class HeapSort {
public:
    void maxHeapify(int* arr, int i, int size) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int largest = i;
        if (l < size && arr[l] > arr[largest]) {
            largest = l;
        }

        if (r < size && arr[r] > arr[largest]) {
            largest = r;
        }

        if (largest != i) {
            swap(arr[largest], arr[i]);
            maxHeapify(arr, largest, size);
        }
    }

    void buildMaxHeap(int* arr, int size) {
        for (int i = size / 2 - 1; i >= 0; i--) {
            maxHeapify(arr, i, size);
        }
    }

    int heapSort(int* arr, int size) {
        auto start = high_resolution_clock::now();
        buildMaxHeap(arr, size);
        for (int i = size - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            maxHeapify(arr, 0, i);
        }
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Heap sort execution time: " << duration.count() << " ns\n";
        string fileName = "heapsort_result.txt";
        fstream fileOut(fileName, ios::out);
        for (int i = 0; i < size; i++)
            fileOut << arr[i] << ' ';
        return duration.count();
    }
};

class Testcase {
    int* arr;
    int size;
public:
    Testcase() : arr(nullptr), size(0) {}
    ~Testcase() {
        clear();
    }

    void genTestcase(int _size) {
        if (_size <= 0) throw invalid_argument("invalid argument");

        this->size = _size;
        arr = new int[size];
        srand(time(0));
        for (int i = 0; i < this->size; i++) {
            arr[i] = rand();
        }
        string fileName = "testcase.txt";
        fstream fileOut(fileName, ios::out);
        for (int i = 0; i < this->size; i++)
            fileOut << arr[i] << ' ';
    }

    void test(QuickSort& quick_sort, HeapSort& heap_sort, int number_of_testcase, int num_of_elements) {
        if (number_of_testcase <= 0 || num_of_elements <= 0) throw invalid_argument("invalid argument");

        int *qs_execution_time = new int[number_of_testcase];
        int *hs_execution_time = new int[number_of_testcase];
        cout << "Number of elements: " << size << endl;
        for (int i = 0; i < number_of_testcase; i++) {
            cout << "Test number " << i + 1 << endl;
            genTestcase(num_of_elements);
            qs_execution_time[i] = quick_sort.quicksort(arr, size);
            hs_execution_time[i] = heap_sort.heapSort(arr, size);
            clear();
            cout << '\n';
        }
        int avg_hs = 0, avg_qs = 0;
        for (int i = 0; i < number_of_testcase; i++) {
            avg_hs += hs_execution_time[i];
            avg_qs += qs_execution_time[i];
        }
        cout << "Quicksort average: " << avg_qs / number_of_testcase << " ns" << endl;
        cout << "Heapsort average: " << avg_hs / number_of_testcase << " ns" << endl;
    }

    void clear() {
        if (arr != nullptr) 
            delete [] arr;
        arr = nullptr;
        size = 0;
    }

};

int main() {
    // Comparing running time of quick sort and heap sort
    QuickSort quick_sort;
    HeapSort heap_sort;
    Testcase test;
    int number_of_elements = 100000;
    int number_of_testcase = 10;
    // you can change the value of 2 vaiables above to see the difference
    test.test(quick_sort, heap_sort, number_of_testcase, number_of_elements);
}