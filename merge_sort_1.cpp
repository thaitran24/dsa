// This is just a test during my time in learning DSA.
// from Introduction to Algorithm by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.
// Created by Thai Tran

#include <iostream>
#include <chrono>
#include <fstream>

using namespace std::chrono;
using namespace std;

/**
 * Print array from left to right
 */
void print(int* arr, int left, int right) {
    cout << "print: " << endl;
    for (int i = left; i <= right; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

/**
 * Insertion sort part of array[left...right]
 */
void insertionSort(int* arr, int left, int right) {
    for (int i = left; i <= right; ++i) {
        int j = i - 1;
        int key = arr[i];
        while (j >= left && key <= arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void merge(int* arr, int start, int mid, int end) {
    // number of elements in 2 subarrays
    int N1 = mid - start + 1;
    int N2 = end - mid;

    int* arr_1 = new int[N1];
    int* arr_2 = new int[N2];

    for (int i = 0; i < N1; i++)
        arr_1[i] = arr[i + start];

    for (int i = 0; i < N2; i++)
        arr_2[i] = arr[i + mid + 1];

    int arr_idx = start;
    int i1 = 0, i2 = 0;
    // merge 2 subarrays, terminate if one reach the end
    while (i1 < N1 && i2 < N2) {
        if (arr_1[i1] < arr_2[i2])
            arr[arr_idx++] = arr_1[i1++];
        else arr[arr_idx++] = arr_2[i2++];
    }

    // assign left 
    while (i1 < N1) {
        arr[arr_idx++] = arr_1[i1++];
    }

    // assign left
    while (i2 < N2) {
        arr[arr_idx++] = arr_2[i2++];
    }
}

void mergeSort(int* arr, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

void mergeSort_insertionSort(int* arr, int start, int end, int length_diff) {
    if (end - start <= length_diff) {
        insertionSort(arr, start, end);
        return;
    }
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

int mergeSort(int* arr, const int N) {
    // calculate time executed
    auto start = high_resolution_clock::now();

    mergeSort(arr, 0, N - 1);

    auto stop = high_resolution_clock::now();
    auto diff = duration_cast<nanoseconds>(stop - start);
    cout << "Execution time: " << diff.count() << " ns" << endl;
    return diff.count();
}

/**
 * Merge sort combine with insertion sort when number of element need sorting is small enough
 */
int mergeSort_combine_insertionSort(int* arr, const int N, int length_diff) {
    auto start = high_resolution_clock::now();

    mergeSort_insertionSort(arr, 0, N - 1, length_diff);

    auto stop = high_resolution_clock::now();
    auto diff = duration_cast<nanoseconds>(stop - start);
    cout << "Execution time: " << diff.count() << " ns" << endl;
    return diff.count();
}

class Testcase {
    int* arr;
    int size;
public:
    Testcase() : arr(nullptr), size(0) {}
    ~Testcase() {
        clear();
    }
    void clear() {
        if (arr != nullptr) delete [] arr;
        arr = nullptr;
        size = 0;
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

    void test(int n_iterations, int num_of_elements) {
        if (n_iterations <= 0 || num_of_elements <= 0) throw invalid_argument("invalid argument");

        cout << "Number of elements: " << size << endl;
        int *diff = new int[n_iterations];
        int *ms = new int[n_iterations];
        int *ms_is = new int[n_iterations];
        for (int i = 0; i < n_iterations; i++) {
            cout << "Test number " << i + 1 << endl;
            genTestcase(num_of_elements);
            ms[i] = mergeSort(arr, size);
            int length_diff = 100;  // when each sub-array split down to this number of elements, 
                                    // it will use insertion sort instead of keeping merge sort
                                    // you can change this value to see the difference
            ms_is[i] = mergeSort_combine_insertionSort(arr, size, length_diff);
            clear();
            cout << '\n';
            diff[i] = ms[i] - ms_is[i];
        }
        int avg_diff = 0, ms_avg = 0, ms_is_avg = 0;
        for (int i = 0; i < n_iterations; i++) {
            avg_diff += diff[i];
            ms_avg += ms[i];
            ms_is_avg += ms_is[i];
        }

        cout << "Average merge sort time: " << ms_avg / n_iterations << " ns" << endl;
        cout << "Average merge sort + insertion sort time: " << ms_is_avg / n_iterations << " ns" << endl;
        cout << "Average time difference: " << avg_diff / n_iterations << " ns" << endl;

        delete [] ms;
        delete [] ms_is;
        delete [] diff;
    }
};

int main() {
    Testcase test;
    int number_of_testcase = 10;             
    int number_of_array_elements = 100000;

    // You can modify the value of 2 variables above to see the difference
    test.test(number_of_testcase, number_of_array_elements);
}