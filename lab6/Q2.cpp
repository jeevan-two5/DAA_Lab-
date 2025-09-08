/*
🔹 Intuition

We need the k-th smallest element (like order statistics).

A naive approach: sort the array → O(n log n) → then pick k-th element.

But we can do better:

👉 Use a Quickselect algorithm:

Choose a pivot randomly (to avoid worst-case like QuickSort).

Partition array around pivot (smaller elements left, bigger right).

If pivot index = k → return pivot.

If k < pivot index → recurse left side.

Else recurse right side with adjusted k.

⚡ Expected Time Complexity: O(n) (average)
⚡ Worst-case: O(n²) (very rare with randomization).  */

#include <bits/stdc++.h>
using namespace std;

vector<int> kthLargestStream(vector<int>& A, int n, int k) {
    vector<int> B; // answer array
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap of size k

    for (int i = 0; i < n; i++) {
        minHeap.push(A[i]);

        // Keep only top k largest elements
        if ((int)minHeap.size() > k)
            minHeap.pop();

        // Once we have at least k elements, record the k-th largest
        if (i >= k - 1)
            B.push_back(minHeap.top());
    }

    return B;
}

int main() {
    int n = 8, k = 3;
    vector<int> A = {4, 5, 8, 2, 3, 5, 10, 9};

    vector<int> result = kthLargestStream(A, n, k);

    cout << "Output: ";
    for (int x : result)
        cout << x << " ";
    cout << endl;

    return 0;
}
