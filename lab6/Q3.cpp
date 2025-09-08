/*      Intuition

For each prefix of the array, we need the median.

If we sort every prefix, it would be O(n² log n) (too slow).

👉 Optimal approach: Use two heaps

Max-heap (left side): stores the smaller half of numbers.

Min-heap (right side): stores the larger half of numbers.

Balancing: sizes of heaps differ by at most 1.

Median:

If both heaps are equal size → average of tops.

Else → top of the larger heap.

⚡ Each insertion takes O(log n), so total = O(n log n) (optima   */


#include <bits/stdc++.h>

using namespace std;
vector<double> runningMedian(vector<int>& A, int n) {
    // Max-heap for left half
    priority_queue<int> left;
    // Min-heap for right half
    priority_queue<int, vector<int>, greater<int>> right;

    vector<double> B;

    for (int i = 0; i < n; i++) {
        int num = A[i];

        // Step 1: Insert into correct heap
        if (left.empty() || num <= left.top())
            left.push(num);
        else
            right.push(num);

        // Step 2: Balance heaps (size difference ≤ 1)
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }

        // Step 3: Find median
        if (left.size() == right.size()) {
            double median = (left.top() + right.top()) / 2.0;
            B.push_back(median);
        } else {
            B.push_back(left.top()); // left will always have 1 more if uneven
        }
    }

    return B;
}

int main() {
    int n = 6;
    vector<int> A = {4, 5, 8, 2, 3, 1};

    vector<double> result = runningMedian(A, n);

    cout << "Output: ";
    for (double x : result)
        cout << x << " ";
    cout << endl;

    return 0;
}
