/*🔹 Intuition
Naïve Way

Merge both arrays (O(m+n)) → pick middle.

Works, but not optimal.

Optimal Way (Binary Search Partition)

We want to partition both arrays such that:

Left half has exactly (m+n+1)/2 elements (so it contains the median(s)).

All elements in left half ≤ all elements in right half.

Formally:

Choose i = number of elements from arr1 in left half.

Then j = (m+n+1)/2 - i = number of elements from arr2.

Conditions:

arr1[i-1] <= arr2[j]   AND   arr2[j-1] <= arr1[i]


If this holds → correct partition.

Median Calculation

If (m+n) is odd → median = max(arr1[i-1], arr2[j-1]).

If even → median = (max(arr1[i-1], arr2[j-1]) + min(arr1[i], arr2[j])) / 2.

We binary search on i (O(log(min(m,n)))).*/

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

double findMedianSortedArrays(vector<int>& arr1, vector<int>& arr2) {
    int m = arr1.size();
    int n = arr2.size();
    
    // Ensure arr1 is smaller
    if (m > n) return findMedianSortedArrays(arr2, arr1);

    int low = 0, high = m;
    while (low <= high) {
        int i = (low + high) / 2;           // partition arr1
        int j = (m + n + 1) / 2 - i;        // partition arr2

        int left1 = (i == 0) ? INT_MIN : arr1[i - 1];
        int right1 = (i == m) ? INT_MAX : arr1[i];
        
        int left2 = (j == 0) ? INT_MIN : arr2[j - 1];
        int right2 = (j == n) ? INT_MAX : arr2[j];

        if (left1 <= right2 && left2 <= right1) {
            // Correct partition
            if ((m + n) % 2 == 0) {
                return (max(left1, left2) + min(right1, right2)) / 2.0;
            } else {
                return max(left1, left2);
            }
        }
        else if (left1 > right2) {
            high = i - 1;  // too many elements from arr1
        } else {
            low = i + 1;   // too few elements from arr1
        }
    }
    return 0.0; // should never reach here
}

int main() {
    int m, n;
    cin >> m;
    vector<int> arr1(m);
    for (int i = 0; i < m; i++) cin >> arr1[i];
    cin >> n;
    vector<int> arr2(n);
    for (int i = 0; i < n; i++) cin >> arr2[i];

    cout << findMedianSortedArrays(arr1, arr2) << endl;
    return 0;
}
