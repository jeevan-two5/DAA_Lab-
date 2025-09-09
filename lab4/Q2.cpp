/*Intuition
We want the minimum daily speed k so that all books can be finished in d days.

Each day you pick one book and read k pages.

If fewer than k pages remain → you finish it early and rest.

So, the number of days required for a book with p pages = ceil(p / k).

Total days required = sum of these across all books.

👉 The task reduces to finding the smallest k such that

i=∑​⌈kpages[i]​⌉≤d       , i = 1 to n
🔹 Observations
If k is too small, required days will be > d.

If k is large enough, required days ≤ d.

This property is monotonic → we can use binary search on k.

🔹 Search Range
Minimum possible k = 1 (slowest).

Maximum possible k = max(pages) (fastest, since one book can be finished in a single day at most) */

// =================================CODE==============================

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Function to check if speed k is enough
bool canFinish(vector<int>& pages, int d, int k) {
    long long days = 0;
    for (int p : pages) {
        days += (p + k - 1) / k; // ceil(p / k)
        if (days > d) return false; // early stop
    }
    return days <= d;
}

int minReadingSpeed(vector<int>& pages, int d) {
    int left = 1, right = *max_element(pages.begin(), pages.end());
    int ans = right;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (canFinish(pages, d, mid)) {
            ans = mid;      // possible, try smaller k
            right = mid - 1;
        } else {
            left = mid + 1; // too slow, increase k
        }
    }
    return ans;
}

int main() {
    int n, d;
    cin >> n >> d;
    vector<int> pages(n);
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << minReadingSpeed(pages, d) << endl;
    return 0;
}
