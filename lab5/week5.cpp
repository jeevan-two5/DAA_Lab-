//Q1

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



//============================================BELOW CODE IS FOR HEAP SORT=======================================================
/*(b) HeapSort
Intuition

HeapSort works in two steps:

Build a max heap from the array.

Repeatedly extract the max (root), put it at the end of the array, and reduce heap size.

This ensures ascending order.

Build heap → O(n)

Each extract + heapify → O(log n)

Total: O(n log n)*/
#include <iostream>
using namespace std;

void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;
    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void buildHeap(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);
}

void heapSort(int arr[], int n) {
    buildHeap(arr, n);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);   // Move max to end
        maxHeapify(arr, i, 0);  // Heapify reduced heap
    }
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    heapSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}

//===========Q2 =========

#include <iostream>
using namespace std;

// Counting Sort for a specific digit (exp = 1, 10, 100, ...)
void countingSort(int arr[], int n, int exp) {
    int output[n];    // Output array
    int count[10] = {0};  // Count array for digits 0-9

    // Count occurrences of digits
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Change count[i] so that it contains actual positions
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (stable sorting)
    for (int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy back to original array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Radix Sort
void radixSort(int arr[], int n) {
    // Find maximum number to know number of digits
    int maxNum = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > maxNum) maxNum = arr[i];

    // Apply counting sort for each digit
    for (int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSort(arr, n, exp);
}

int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    radixSort(arr, n);

    cout << "Sorted array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}

//===========Q3=========

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, K;
    cin >> n >> K;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // baseline: subtract everywhere
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] - b[i];
    }

    // sort by b[i] descending
    vector<long long> gains;
    for (int i = 0; i < n; i++) {
        if (b[i] > 0) gains.push_back(2 * b[i]);
    }
    sort(gains.rbegin(), gains.rend());

    // apply up to K best gains
    for (int i = 0; i < min(K, (int)gains.size()); i++) {
        sum += gains[i];
    }

    cout << sum << "\n";
    return 0;
}

//===========Q4========
#include <bits/stdc++.h>
using namespace std;

vector<int> kMaxSums(vector<int>& a, vector<int>& b, int k) {
    int n = a.size();
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    priority_queue<pair<int, pair<int,int>>> pq; // {sum, {i,j}}
    set<pair<int,int>> seen;

    // start with largest sum
    pq.push({a[0] + b[0], {0,0}});
    seen.insert({0,0});

    vector<int> result;
    while (k-- && !pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int sum = cur.first;
        int i = cur.second.first;
        int j = cur.second.second;
        result.push_back(sum);

        // next candidates
        if (i+1 < n && !seen.count({i+1, j})) {
            pq.push({a[i+1] + b[j], {i+1, j}});
            seen.insert({i+1, j});
        }
        if (j+1 < n && !seen.count({i, j+1})) {
            pq.push({a[i] + b[j+1], {i, j+1}});
            seen.insert({i, j+1});
        }
    }
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<int> ans = kMaxSums(a, b, k);
    for (int x : ans) cout << x << " ";
    cout << "\n";
}

//==========Q5==========

#include <bits/stdc++.h>
using namespace std;

int main() {
    long long C;
    cin >> C;

    // find binary length of C
    int L = 64 - __builtin_clzll(C); // number of bits in C
    long long mask = (1LL << L) - 1; // all 1s in L bits

    long long A = mask ^ C;
    long long B = C;

    // ensure product is maximized (swap if needed)
    if (A * B < B * A) swap(A, B);

    cout << A << " " << B << "\n";
    return 0;
}
