/*🔹 Intuition

Median Definition

If n is odd → median is element at index n/2 in sorted order.

If n is even → median is average of elements at indices n/2 - 1 and n/2.

Naïve Method (Sorting)

Sort array in O(n log n).

Pick the middle element(s).
❌ Too slow for this problem.

QuickSelect Method (O(n) average)

Choose a random pivot.

Partition array like QuickSort.

After partition:

If pivot index = k → found the k-th smallest element.

If pivot index > k → recurse on left side.

If pivot index < k → recurse on right side.

This way, we only recurse on one side, not both, making expected time O(n).

For Median

If n is odd → find element at position n/2.

If n is even → find elements at positions n/2 - 1 and n/2, then average them.*/
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Swap helper
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function (Lomuto scheme)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

// Randomized partition
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

// QuickSelect: find kth smallest (0-indexed)
int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pi = randomizedPartition(arr, low, high);

        if (pi == k) return arr[pi];
        else if (pi > k) return quickSelect(arr, low, pi - 1, k);
        else return quickSelect(arr, pi + 1, high, k);
    }
    return -1; // should not happen
}

int main() {
    srand(time(0));

    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    if (n % 2 == 1) {
        // odd length → middle element
        int median = quickSelect(arr, 0, n - 1, n / 2);
        cout << median << endl;
    } else {
        // even length → average of two middle elements
        int m1 = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int m2 = quickSelect(arr, 0, n - 1, n / 2);
        cout << (m1 + m2) / 2.0 << endl; // print as double
    }

    return 0;
}
