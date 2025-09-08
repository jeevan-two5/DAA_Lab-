/*Goal

Given a sorted array arr[] and a number x.

Find:

First occurrence index of x

Last occurrence index of x

If x is not present → return -1, -1.

🔑 Intuition

Since the array is sorted, we can use Binary Search instead of linear scanning.

First Occurrence:

Use binary search.

When arr[mid] == x, don’t stop immediately.

Keep searching on the left side to check if an earlier occurrence exists.

Last Occurrence:

Similar, but when arr[mid] == x, continue searching on the right side.

Both run in O(log n) time.
*/

#include <iostream>
using namespace std;

int firstOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;        // possible answer
            high = mid - 1;   // search left
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int lastOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;        // possible answer
            low = mid + 1;    // search right
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    int arr1[] = {1, 3, 5, 5, 5, 6};
    int n1 = 6, x1 = 5;
    int first = firstOccurrence(arr1, n1, x1);
    int last = lastOccurrence(arr1, n1, x1);
    cout << first << ", " << last << endl;  // Output: 2, 4

    int arr2[] = {1, 3, 5, 5, 5, 6};
    int n2 = 6, x2 = 4;
    first = firstOccurrence(arr2, n2, x2);
    last = lastOccurrence(arr2, n2, x2);
    cout << first << ", " << last << endl;  // Output: -1, -1

    return 0;
}
