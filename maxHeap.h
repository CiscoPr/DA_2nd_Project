#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <class T>
struct MaxHeap {
private:
    std::vector<
            std::pair<int, T>> A;

    int PARENT(int i){ return (i - 1) / 2; }
    int LEFT(int i)  { return (2*i + 1);   }
    int RIGHT(int i) { return (2*i + 2);   }

    void swapValues(pair<int, T> &V1,pair<int, T> &V2){
        auto temp = V1;
        V1 = V2;
        V2 = temp;
    }

    void heapify_down(int i)
    {
        int left = LEFT(i);
        int right = RIGHT(i);

        int largest = i;


        if (left < size() && A[left].first > A[i].first) {
            largest = left;
        }

        if (right < size() && A[right].first > A[largest].first ) {
            largest = right;
        }

        if (largest != i)
        {
            swapValues(A[i], A[largest]);
            heapify_down(largest);
        }
    }

    void heapify_up(int i)
    {
        if (i && A[PARENT(i)].first < A[i].first)
        {
            // swap the two if heap property is violated
            swapValues(A[i], A[PARENT(i)]);

            // call heapify-up on the parent
            heapify_up(PARENT(i));
        }
    }

public:
    // return size of the heap
    unsigned int size() {
        return A.size();
    }

    // Function to check if the heap is empty or not
    bool empty() {
        return size() == 0;
    }

    // insert key into the heap
    void push(int i, T value)
    {
        // insert a new element at the end of the vector
        A.push_back(
                pair<int, T>(
                        i,
                        value
                ));

        // get element index and call heapify-up procedure
        int index = size() - 1;
        heapify_up(index);
    }

// Function to remove an element with the highest priority (present at the root)
    void pop()
    {
        try {
            // if the heap has no elements, throw an exception
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                                        "index is out of range(Heap underflow)");
            }

            // replace the root of the heap with the last element
            // of the vector
            A[0] = A.back();
            A.pop_back();

            // call heapify-down on the root node
            heapify_down(0);
        }
            // catch and print the exception
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
// Function to return an element with the highest priority (present at the root)
    pair<int, T> top()
    {
        try {
            // if the heap has no elements, throw an exception
            if (size() == 0)
            {
                throw out_of_range("Vector<X>::at() : "
                                        "index is out of range(Heap underflow)");
            }

            // otherwise, return the top (first) element
            return A.at(0);        // or return A[0];
        }
            // catch and print the exception
        catch (const out_of_range &oor) {
            cout << endl << oor.what();
        }
    }
};

/*#include <unordered_map>
#include <vector>

#define LEFT(i) (2 * (i))
#define RIGHT(i) (2 * (i) + 1)
#define PARENT(i) ((i) / 2)

using namespace std;

// Binary min-heap to represent integer keys of type K with values (priorities)
// of type V
template <class K, class V> class MaxHeap {
    struct Node { // An element of the heap: a pair (key, value)
        K key;
        V value;
    };

    int size;                  // Number of elements in heap
    int maxSize;               // Maximum number of elements in heap
    vector<Node> a;            // The heap array
    unordered_map<K, int> pos; // maps a key into its position on the array a
    const K KEY_NOT_FOUND;

    void upHeap(int i);
    void downHeap(int i);
    void swap(int i1, int i2);

public:
    MaxHeap(int n,
            const K &notFound); // Create a min-heap for a max of n pairs (K,V)
    // with notFound returned when empty
    int getSize();              // Return number of elements in the heap
    bool hasKey(const K &key);  // Heap has key?
    void insert(const K &key,
                const V &value); // Insert (key, value) on the heap
    void decreaseKey(const K &key, const V &value); // Decrease value of key
    K removeMin();        // remove and return key with smaller value
    Node removeMinNode(); // remove and return key with smaller value
};

// ----------------------------------------------

// Make a value go "up the tree" until it reaches its position
template <class K, class V> void MaxHeap<K, V>::upHeap(int i) {
    while (i > 1 &&
           a[i].value > a[PARENT(i)].value) { // while pos smaller than parent,
        // keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}

// Make a value go "down the tree" until it reaches its position
template <class K, class V> void MaxHeap<K, V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i) <= size && a[RIGHT(i)].value > a[j].value)
            j = RIGHT(i); // choose smaller child
        if (a[i].value > a[j].value)
            break;  // node already smaller than children, stop
        swap(i, j); // otherwise, swap with smaller child
        i = j;
    }
}

// Swap two positions of the heap (update their positions)
template <class K, class V> void MaxHeap<K, V>::swap(int i1, int i2) {
    Node tmp = a[i1];
    a[i1] = a[i2];
    a[i2] = tmp;
    pos[a[i1].key] = i1;
    pos[a[i2].key] = i2;
}

// ----------------------------------------------

// Create a min-heap for a max of n pairs (K,V) with notFound returned when
// empty
template <class K, class V>
MaxHeap<K, V>::MaxHeap(int n, const K &notFound)
        : KEY_NOT_FOUND(notFound), size(0), maxSize(n), a(n + 1) {}

// Return number of elements in the heap
template <class K, class V> int MaxHeap<K, V>::getSize() { return size; }

// Heap has key?
template <class K, class V> bool MaxHeap<K, V>::hasKey(const K &key) {
    return pos.find(key) != pos.end();
}

// Insert (key, value) on the heap
template <class K, class V>
void MaxHeap<K, V>::insert(const K &key, const V &value) {
    if (size == maxSize)
        return; // heap is full, do nothing
    if (hasKey(key))
        return; // key already exists, do nothing
    a[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

// Decrease value of key to the indicated value
template <class K, class V>
void MaxHeap<K, V>::decreaseKey(const K &key, const V &value) {
    if (!hasKey(key))
        return; // key does not exist, do nothing
    int i = pos[key];
    if (value < a[i].value)
        return; // value would increase, do nothing
    a[i].value = value;
    upHeap(i);
}

// remove and return key with smaller value
template <class K, class V> K MaxHeap<K, V>::removeMin() {
    if (size == 0)
        return KEY_NOT_FOUND;
    K min = a[1].key;
    pos.erase(min);
    a[1] = a[size--];
    downHeap(1);
    return min;
}

// remove and return key, value pair with smaller value
template <class K, class V> auto MaxHeap<K, V>::removeMinNode() -> Node {
    if (size == 0)
        return {KEY_NOT_FOUND, KEY_NOT_FOUND};
    Node min = a[1];
    pos.erase(min.key);
    a[1] = a[size--];
    downHeap(1);
    return min;
}*/