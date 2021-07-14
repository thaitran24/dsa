// This is just a test during my time in learning DSA.
// from Introduction to Algorithm by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest and Clifford Stein.
// Created by Thai Tran

#include <iostream>
#include <chrono>
#include <string>
#include <fstream>
#include <deque>
#include <cmath>

using namespace std;
using namespace std::chrono;

//////////////////////////////////////////////////
/** 
 * Please don't modify any of these code below
 * Your implementation is at the bottom of this file
*/
//////////////////////////////////////////////////

template <class T>
struct Node {
    T value;
    Node<T>* next;
    Node() : value(0), next(nullptr) {}
    Node(T _value, Node* _ptr) : value(_value), next(_ptr) {}
};

// Linked list of nodes
template <class T>
struct List {
    Node<T>* head;
    Node<T>* tail;
    int size;
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List();

    void push_back(Node<T>*);
    void clear();
    void print();
};

// Testcase class for generate and check testcase
template <class T>
class Test {
public:

    // Generate testcase with input and expected output
    void genTestcase(List<T>& list, int numberOfElements) {
        list.clear();
        // Generate worst-case input
        for (int i = numberOfElements; i >= 1; --i) {
            Node<T> *newNode = new Node<T>;
            newNode->value = i;
            list.push_back(newNode);
        }
    }

    // Read expected output into array
    void readExpected(deque <Node<T> *> &expected, const List<T> &list) {
        Node<T>* temp = list.head;
        while (temp) {
            expected.push_front(temp);
            temp = temp->next;
        }
    }

    // Check result after sort
    bool checkResult(const List<T>& list, const deque <Node<T> *> &expected) {
        if (list.size != expected.size()) return false;
        Node<T>* temp = list.head;
        int i = 0;
        while (temp) {
            if (temp != expected[i]) return false;
            temp = temp->next;
            ++i;
        }
        return true;
    }
};

template <class T>
void sort(List<T>& list);


int main() {
    const int numberOfTestcase = 10;
    int correct = 0;

    for (int i = 1; i <= numberOfTestcase; i++) {
        Test<int> test;
        List<int> list;
        deque<Node<int> *> expected;
        // int numberOfElements = 10;
        int numberOfElements = 50 * pow(2, i);

        cout << "Testcase " << i << ": " << numberOfElements << " elements" << endl;
        test.genTestcase(list, numberOfElements);
        test.readExpected(expected, list);

        auto start = high_resolution_clock::now();
        sort(list);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<nanoseconds>(stop - start);
        cout << "Execution time: " << duration.count() << " ns" << endl;

        if (test.checkResult(list, expected)) {
            cout << "Correct\n";
            ++correct;
        }
        else cout << "Incorrect\n";
    }
    cout << "\nResult: " << correct << '/' << numberOfTestcase << endl;
}


template <class T>
// Clear node before destroying list
List<T>::~List() {
    this->clear();
}

template <class T>
// Clear list
void List<T>::clear() {
    Node<T>* temp = head;
    while (temp) {
        head = head->next;
        delete temp;
        temp = head;
    }
}

template <class T>
// Insert a node at tail of list
void List<T>::push_back(Node<T>* node) {
    if (head == nullptr) {
        head = tail = node;
        node->next = nullptr;
        ++size;
        return;
    }

    tail->next = node;
    node->next = nullptr;
    tail = node;
    ++size;
}

template <class T>
void List<T>::print() {
    Node<T>* temp = head;
    while (temp) {
        cout << temp->value << ' ';
        temp = temp->next;
    }
    cout << endl;
}

template <class T>
void print(Node<T>* head) {
    while (head) {
        cout << head->value << ' ';
        head = head->next;
    }
    cout << endl;
}
//////////////////////////////////////////////////
/**
 * BEGIN IMPLEMENTATION
*/
//////////////////////////////////////////////////

/**
 * You can add utility functions
 * Or you can add new methods for class List
 * But do not modify code above
*/

template <class T>
void split(Node<T>* head, Node<T>** start, Node<T>** end) {
    Node<T>* iter1 = head;
    Node<T>* iter2 = head->next;

    while (iter1 && iter2 && iter2 != *end) {
        iter2 = iter2->next;
        if (iter2 != nullptr) {
            iter2 = iter2->next;
            iter1 = iter1->next;
        }
    }

    *start = head;
    *end = iter1->next;
    iter1->next = nullptr;
}

template <class T>
Node<T>* merge(Node<T>* list1, Node<T>* list2) {
    Node<T>* res = nullptr;
    if (list1 == nullptr) return list2;
    else if (list2 == nullptr) return list1;

    if (list1->value < list2->value) {
        res = list1;
        list1->next = merge(list1->next, list2);
    }
    else {
        res = list2;
        list2->next = merge(list1, list2->next);
    }
    return res;
}

template <class T>
void mergeSort(Node<T>** listHead) {
    Node<T>* head = *listHead;
    Node<T>* list1;
    Node<T>* list2;
    if (head == nullptr || head->next == nullptr) return;
    split(head, &list1, &list2);
    mergeSort(&list1);
    mergeSort(&list2);

    *listHead = merge(list1, list2);
}

template <class T>
void bubbleSort(List<T>& list) {
    Node<T>* iter1 = list.head;
    Node<T>* prev1 = list.head;

    while (iter1) {
        
        Node<T>* iter2 = iter1->next;
        Node<T>* prev2 = iter1;
        while (iter2) {
            print(iter1);
            print(iter2);
            if (iter2->value < iter1->value) {
                Node<T>* temp = iter1->next;
                prev1->next = iter2;
                prev2->next = iter1;
                iter1->next = iter2->next;
                iter2->next = temp;
            }
        }
        prev1 = iter1;
        prev2 = iter2;
        iter1 = iter1->next;
        iter2 = iter2->next;
    }
}

template <class T>
void sort(List<T>& list) {
    mergeSort(&(list.head));    
}