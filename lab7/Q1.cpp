#include <bits/stdc++.h>
using namespace std;

// Partition function using a given pivot
int partition(vector<int>& arr, int left, int right, int pivot) {
    int pivotIndex;
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            pivotIndex = i;
            break;
        }
    }        
    swap(arr[pivotIndex], arr[right]); // move pivot to end
    pivotIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            swap(arr[i], arr[pivotIndex]);
            pivotIndex++;
        }
    }
    swap(arr[pivotIndex], arr[right]); // move pivot back
    return pivotIndex;
}

// Find median of a small group (size <= 5)
int findMedian(vector<int>& arr, int left, int right) {
    sort(arr.begin() + left, arr.begin() + right + 1);
    return arr[left + (right - left) / 2];
}

// Recursive function using Median of Medians
int kthSmallest(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];

    // Step 1: Divide into groups of 5 and find medians
    vector<int> medians;             
    for (int i = left; i <= right; i += 5) {
        int subRight = min(i + 4, right);
        medians.push_back(findMedian(arr, i, subRight));
    }

    // Step 2: Find median of medians (pivot)
    int medOfMed;
    if (medians.size() == 1)
        medOfMed = medians[0];
    else
        medOfMed = kthSmallest(medians, 0, medians.size() - 1, medians.size() / 2);

    // Step 3: Partition array around pivot
    int pos = partition(arr, left, right, medOfMed);

    int count = pos - left + 1; // position of pivot in sorted order
    if (count == k) return arr[pos];
    else if (k < count) return kthSmallest(arr, left, pos - 1, k);
    else return kthSmallest(arr, pos + 1, right, k - count);
}

int main() {
    vector<int> arr = {7, 10, 4, 11, 8, 3, 20, 15};
    int K = 3;
    cout << "K-th smallest element is " << kthSmallest(arr, 0, arr.size() - 1, K) << endl;
    return 0;
}

