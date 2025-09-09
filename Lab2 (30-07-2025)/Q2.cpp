/*Intuition

Observation:

If k is too small, it will take too many days.

If k is very large, you can finish quickly.
→ The answer is monotonic: as k increases, the number of days required decreases.
→ This is perfect for binary search.

How to check if a k works?
For each book with pages[i] pages:

Days needed = ceil(pages[i] / k)

Total days = sum of all these.

If total days ≤ d, then k is valid.

Binary Search Range:

Lower bound = 1 (slowest possible speed).

Upper bound = max(pages) (if k = max book size, you finish each book in ≤ 1 day).

Binary Search Logic:

Mid = (low + high) / 2.

If mid pages/day works, try smaller (high = mid).

Else, increase (low = mid + 1).

Answer = low.*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to check if k pages/day is enough
bool canFinish(vector<int>& pages, int d, int k) {
    long long days = 0;
    for (int p : pages) {
        days += (p + k - 1) / k;  // ceil(p/k)
        if (days > d) return false;
    }
    return days <= d;
}

int minReadingSpeed(vector<int>& pages, int d) {
    int low = 1, high = *max_element(pages.begin(), pages.end());
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (canFinish(pages, d, mid))
            high = mid; // try smaller k
        else
            low = mid + 1; // need faster speed
    }
    return low;
}

int main() {
    int n, d;
    cin >> n;
    vector<int> pages(n);
    for (int i = 0; i < n; i++) cin >> pages[i];
    cin >> d;

    cout << minReadingSpeed(pages, d) << endl;
    return 0;
}
