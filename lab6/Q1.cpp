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

// Partition function (like QuickSort)
int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r];
    int i = l;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

// Randomized partition (chooses random pivot)
int randomizedPartition(vector<int>& arr, int l, int r) {
    int pivotIndex = l + rand() % (r - l + 1);
    swap(arr[pivotIndex], arr[r]); // Move random pivot to end
    return partition(arr, l, r);
}

// Randomized Select (Quickselect)
int randomizedSelect(vector<int>& arr, int l, int r, int k) {
    if (l == r)
        return arr[l];

    int pos = randomizedPartition(arr, l, r);
    int rank = pos - l + 1; // Number of elements in left partition + pivot

    if (k == rank)
        return arr[pos]; // Found k-th smallest
    else if (k < rank)
        return randomizedSelect(arr, l, pos - 1, k);
    else
        return randomizedSelect(arr, pos + 1, r, k - rank);
}

int main() {
    srand(time(0)); // Seed random number generator

    vector<int> arr = {10, 25, 3, 1, 15, 11};
    int k = 3; // 3rd smallest

    int result = randomizedSelect(arr, 0, arr.size() - 1, k);

    cout << k << "-th smallest element is: " << result << endl;

    return 0;
}
