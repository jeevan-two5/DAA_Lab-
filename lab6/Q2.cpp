/*Intuition

Naive thought:

For every prefix, sort the numbers and pick the k-th largest.

Too expensive → sorting each prefix is O(n² log n).

Key insight:

We don’t need all numbers sorted.

We only care about the k largest numbers so far.

The smallest among those k is exactly the k-th largest overall.

How to maintain efficiently?

Use a min-heap of size k:

Insert every incoming number.

If heap size > k → remove the smallest (throw away useless small numbers).

Now heap contains only the top k numbers seen so far.

The root (top) of the min-heap is always the k-th largest.
The heap ensures we never store more than k elements.

By always discarding the smallest when size > k, we guarantee the heap holds only the k biggest numbers.

The smallest among them (= heap root) is the k-th largest in the stream.

⏱️ Efficiency

Each step: insert + possible pop → O(log k).

Across n elements → O(n log k).

Much faster than sorting prefixes.

✨ So the whole trick is: maintain only the k largest elements in a min-heap → its top gives the k-th largest after each step.*/

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
