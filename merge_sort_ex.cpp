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
 * Do not modify any of these code below
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
            Node<T>* newNode = new Node<T>;
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
    Test<int> test;
    const int numberOfTestcase = 10;
    int correct = 0;

    for (int i = 1; i <= numberOfTestcase; i++) {
        List<int> list;
        deque<Node<int> *> expected;
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
        cout << endl;
    }
    cout << "\nResult: " << correct << '/' << numberOfTestcase << endl;
}


// Clear node before destroying list
template <class T>
List<T>::~List() {
    this->clear();
}

// Clear list
template <class T>
void List<T>::clear() {
    Node<T>* temp = head;
    while (temp) {
        head = head->next;
        delete temp;
        temp = head;
    }
    this->tail = nullptr;
    this->size = 0;
}

// Insert a node at tail of list
template <class T>
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
void sort(List<T>& list) {
    
    // to do
    
}