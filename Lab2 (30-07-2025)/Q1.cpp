/*Intuition

Since the array is sorted, binary search is the optimal choice (O(log N)).

To find first occurrence:

Perform binary search.

If arr[mid] == x, store mid, but keep searching left (because there might be another occurrence earlier).

To find last occurrence:

Perform binary search.

If arr[mid] == x, store mid, but keep searching right (because there might be another occurrence later).

If x is not found, return -1, -1.*/



#include <iostream>
using namespace std;
// Function to find first occurrence of x
int firstOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;       // store answer
            high = mid - 1;  // go left for first occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// Function to find last occurrence of x
int lastOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;       // store answer
            low = mid + 1;   // go right for last occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    int n, x;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> x;

    int first = firstOccurrence(arr, n, x);
    int last = lastOccurrence(arr, n, x);

    cout << first << " " << last << endl;
    return 0;
}
