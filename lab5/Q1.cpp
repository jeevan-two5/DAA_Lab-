/*
Intuition

Heap as Array

Parent of i: (i-1)/2

Left child of i: 2*i+1

Right child of i: 2*i+2

Core Operations

insert(key): Place at end, bubble up to maintain heap property.

getMax(): Return arr[0].

extractMax(): Swap root with last element, shrink heap, call maxHeapify(0).

maxHeapify(i): Push down node at i until heap property restored.

buildHeap(): Call maxHeapify from bottom-most non-leaf up to root.

increaseKey(i, k): Add k to arr[i], bubble up if necessary.  */


#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
    int arr[1000];   // fixed-size array
    int heap_size;   // current number of elements

public:
    MaxHeap() {
        heap_size = 0;
    }

    // Get parent/child indices
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Insert a new key
    void insert(int key) {
        if (heap_size >= 1000) {
            cout << "Heap overflow\n";
            return;
        }
        int i = heap_size++;
        arr[i] = key;

        // Bubble up
        while (i != 0 && arr[parent(i)] < arr[i]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Return max element
    int getMax() {
        if (heap_size <= 0) {
            cout << "Heap is empty\n";
            return INT_MIN;
        }
        return arr[0];
    }

    // Heapify subtree rooted at i
    void maxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap_size && arr[l] > arr[largest])
            largest = l;
        if (r < heap_size && arr[r] > arr[largest])
            largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxHeapify(largest);
        }
    }

    // Extract and return max element
    int extractMax() {
        if (heap_size <= 0) {
            cout << "Heap underflow\n";
            return INT_MIN;
        }
        if (heap_size == 1)
            return arr[--heap_size];

        int root = arr[0];
        arr[0] = arr[--heap_size];
        maxHeapify(0);
        return root;
    }

    // Build heap from array
    void buildHeap(int a[], int n) {
        if (n > 1000) {
            cout << "Too many elements\n";
            return;
        }
        heap_size = n;
        for (int i = 0; i < n; i++) {
            arr[i] = a[i];
        }
        for (int i = (heap_size / 2) - 1; i >= 0; i--) {
            maxHeapify(i);
        }
    }

    // Increase key at index i by k
    void increaseKey(int i, int k) {
        if (i < 0 || i >= heap_size) {
            cout << "Index out of bounds\n";
            return;
        }
        arr[i] += k;
        // Bubble up
        while (i != 0 && arr[parent(i)] < arr[i]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Print heap contents
    void printHeap() {
        for (int i = 0; i < heap_size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Driver
int main() {
    MaxHeap h;

    // Insert manually
    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(30);

    cout << "Heap after insertions: ";
    h.printHeap();

    cout << "Max element: " << h.getMax() << endl;

    cout << "Extracted max: " << h.extractMax() << endl;

    cout << "Heap after extract: ";
    h.printHeap();

    // Build heap from array
    int arr[] = {3, 1, 6, 5, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    h.buildHeap(arr, n);

    cout << "Heap after buildHeap: ";
    h.printHeap();

    // Increase key at index 2
    h.increaseKey(2, 10);

    cout << "Heap after increaseKey: ";
    h.printHeap();

    return 0;
}
#include <bits/stdc++.h>
using namespace std;

class MaxHeap {
    int arr[1000];   // fixed-size array
    int heap_size;   // current number of elements

public:
    MaxHeap() {
        heap_size = 0;
    }

    // Get parent/child indices
    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

    // Insert a new key
    void insert(int key) {
        if (heap_size >= 1000) {
            cout << "Heap overflow\n";
            return;
        }
        int i = heap_size++;
        arr[i] = key;

        // Bubble up
        while (i != 0 && arr[parent(i)] < arr[i]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Return max element
    int getMax() {
        if (heap_size <= 0) {
            cout << "Heap is empty\n";
            return INT_MIN;
        }
        return arr[0];
    }

    // Heapify subtree rooted at i
    void maxHeapify(int i) {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap_size && arr[l] > arr[largest])
            largest = l;
        if (r < heap_size && arr[r] > arr[largest])
            largest = r;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            maxHeapify(largest);
        }
    }

    // Extract and return max element
    int extractMax() {
        if (heap_size <= 0) {
            cout << "Heap underflow\n";
            return INT_MIN;
        }
        if (heap_size == 1)
            return arr[--heap_size];

        int root = arr[0];
        arr[0] = arr[--heap_size];
        maxHeapify(0);
        return root;
    }

    // Build heap from array
    void buildHeap(int a[], int n) {
        if (n > 1000) {
            cout << "Too many elements\n";
            return;
        }
        heap_size = n;
        for (int i = 0; i < n; i++) {
            arr[i] = a[i];
        }
        for (int i = (heap_size / 2) - 1; i >= 0; i--) {
            maxHeapify(i);
        }
    }

    // Increase key at index i by k
    void increaseKey(int i, int k) {
        if (i < 0 || i >= heap_size) {
            cout << "Index out of bounds\n";
            return;
        }
        arr[i] += k;
        // Bubble up
        while (i != 0 && arr[parent(i)] < arr[i]) {
            swap(arr[i], arr[parent(i)]);
            i = parent(i);
        }
    }

    // Print heap contents
    void printHeap() {
        for (int i = 0; i < heap_size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// Driver
int main() {
    MaxHeap h;

    // Insert manually
    h.insert(10);
    h.insert(20);
    h.insert(5);
    h.insert(30);

    cout << "Heap after insertions: ";
    h.printHeap();

    cout << "Max element: " << h.getMax() << endl;

    cout << "Extracted max: " << h.extractMax() << endl;

    cout << "Heap after extract: ";
    h.printHeap();

    // Build heap from array
    int arr[] = {3, 1, 6, 5, 2, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    h.buildHeap(arr, n);

    cout << "Heap after buildHeap: ";
    h.printHeap();

    // Increase key at index 2
    h.increaseKey(2, 10);

    cout << "Heap after increaseKey: ";
    h.printHeap();

    return 0;
}
