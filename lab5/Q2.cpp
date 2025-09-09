/*Intuition

Radix Sort is a non-comparison sorting algorithm.

It sorts numbers digit by digit, starting either from the least significant digit (LSD) or most significant digit (MSD).

For each digit, it uses a stable sorting algorithm (like Counting Sort) to maintain the order of numbers with equal digits.

Why Counting Sort as Auxiliary Sort?

Counting Sort works in O(n + k) where k is the range of digits (0–9).

When used for each digit, the overall Radix Sort runs in *O(d(n + k))**, where d = number of digits in the largest number.

Since k = 10 for digits, the time complexity becomes O(d * n) → very efficient for integers.

Steps of Radix Sort

Find the maximum number to know the number of digits.

For each digit (units, tens, hundreds, ...):

Apply Counting Sort considering only that digit.*/

//         ========================CODE==================
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
