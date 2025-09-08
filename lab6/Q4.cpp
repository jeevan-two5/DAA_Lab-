/*
Goal

Given a permutation (unique integers in some order), find the next lexicographically greater permutation.

If no such permutation exists (we’re already at the last one), return the smallest (sorted ascending) permutation.

🔑 Intuition

Think of the permutation as digits of a number:

[2, 4, 1, 7, 5, 0] → like 241750.

We want the next bigger number that can be formed using the same digits.

Steps:

Find a pivot: Scan from right to left and find the first index i such that arr[i] < arr[i+1].

This is the place where we can still make the permutation bigger.

If no such i exists → the array is in descending order → last permutation → just reverse it.

Find the successor: From the right side, find the smallest number greater than arr[i].

Swap pivot and successor.

Reverse the suffix (the part after i) to make it the smallest possible order.

This ensures the result is the next greater permutation.  */

#include <bits/stdc++.h>
using namespace std;

void nextPermutation(vector<int>& arr) {
    int n = arr.size();
    int i = n - 2;

    // Step 1: Find first decreasing element from right
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i >= 0) {
        // Step 2: Find element just larger than arr[i]
        int j = n - 1;
        while (arr[j] <= arr[i]) j--;

        // Step 3: Swap pivot and successor
        swap(arr[i], arr[j]);
    }

    // Step 4: Reverse the suffix
    reverse(arr.begin() + i + 1, arr.end());
}

int main() {
    vector<int> arr = {2, 4, 1, 7, 5, 0};
    nextPermutation(arr);

    cout << "Next permutation: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
