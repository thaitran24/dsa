// This is just a test during my time in learning DSA.
// from Introduction to Algorithm by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.
// Created by Thai Tran

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <cmath>

using namespace std;
using namespace std::chrono;

template <class T>
void insertionSort(T*, const int);

template <class T> 
void mergeSort(T*, const int);

void testcaseGen(int, string, string);
template <class T>
void readTestcase(T*, string);

template <class T>
void print(T*, const int);

template <class T>
bool checkResult(T*, T*, int);

int main() {
    const string fileTestcase = "sort_testcase.txt";
    const string fileExpected = "sort_expected.txt";
    const int numberOfTestcase = 10;
    int correct = 0;

    for (int i = 1; i <= numberOfTestcase; i++) {
        int numberOfElements = 100 * pow(2, i);
        cout << "Testcase " << i << ": " << numberOfElements << " elements" << endl;
        
        int* arr_1 = new int[numberOfElements];
        int *arr_2 = new int[numberOfElements];
        int* res = new int[numberOfElements];

        testcaseGen(numberOfElements, fileTestcase, fileExpected);
        readTestcase(arr_1, fileTestcase);
        readTestcase(arr_2, fileTestcase);
        readTestcase(res, fileExpected);

        insertionSort(arr_1, numberOfElements);
        if (checkResult(arr_1, res, numberOfElements)) ++correct;

        mergeSort(arr_2, numberOfElements);
        if (checkResult(arr_2, res, numberOfElements)) ++correct;

        delete[] res;
        delete[] arr_1;
        delete[] arr_2;
        cout << endl;

    }
    cout << "Result: " << correct << '/' << numberOfTestcase * 2 << endl;
}

/**
 * Generate worst case for ascending sorting
 */
void testcaseGen(int numberOfElements, string fileTestcase, string fileExpected) {
    fstream fileOut(fileTestcase, ios::out);
    for (int i = numberOfElements; i > 0; --i)
        fileOut << i << ' ';
    
    fstream fileOut_1(fileExpected, ios::out);
    for (int i = 1; i <= numberOfElements; ++i)
        fileOut_1 << i << ' ';
}

/**
 * Read testcase from file
 */
template <class T>
void readTestcase(T *arr, string fileName) {
    fstream fileIn(fileName, ios::in);
    int i = 0;
    while (fileIn.good()) {
        fileIn >> arr[i];
        ++i;
    }
}

template <class T>
void insertionSort(T* arr, const int N) {
    // calculate time executed
    auto start = high_resolution_clock::now();

    // insertion sort
    for (int i = 1; i < N; ++i) {
        int j = i - 1;
        T key = arr[i];
        while (j >= 0 && key <= arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }

    auto stop = high_resolution_clock::now();
    auto diff = duration_cast<nanoseconds>(stop - start);
    cout << "Execution time: " << diff.count() << " ns" << endl;
}

template <class T>
void insertionSort(T* arr, int left, int right) {
    for (int i = left; i <= right; ++i) {
        int j = i - 1;
        T key = arr[i];
        while (j >= left && key <= arr[j]) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

template <class T>
void merge(T* arr, int start, int mid, int end) {
    // number of elements in 2 subarrays
    int N1 = mid - start + 1;
    int N2 = end - mid;

    T* arr_1 = new T[N1];
    T* arr_2 = new T[N2];

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

template <class T>
void mergeSort(T* arr, int start, int end) {
    if (start < end) {
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

template <class T>
void mergeSort(T* arr, const int N) {
    // calculate time executed
    auto start = high_resolution_clock::now();

    mergeSort(arr, 0, N - 1);

    auto stop = high_resolution_clock::now();
    auto diff = duration_cast<nanoseconds>(stop - start);
    cout << "Execution time: " << diff.count() << " ns" << endl;
}

template <class T>
void print(T* arr, const int N) {
    for (int i = 0; i < N; i++)
        cout << arr[i] << ' ';
    cout << endl;
}

template <class T>
bool checkResult(T* arr, T* res, int numberOfElements) {
    for (int i = 0; i < numberOfElements; i++) {
        if (arr[i] != res[i]) 
            return false;
    }
    return true;
}