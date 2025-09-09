/* Intuition

Total emotes in triangle:
The sequence is symmetric.
Total = 1 + 2 + … + k + (k-1 + … + 1)
= k*(k+1)/2 + k*(k-1)/2 = k^2.

So max possible emotes = k^2.

We want the prefix length where sum ≥ x.

If x > k^2, you can send all 2k - 1 messages.

Otherwise, find the first index where prefix sum ≥ x.

Efficient prefix sums:

First k messages:
Prefix sum = i*(i+1)/2 after i messages.

After that (descending part):
At message k + j (1 ≤ j ≤ k-1), emotes = k - j.
Total up to there = k^2 - (j*(j+1))/2.

So we can binary search or just simulate until ban. Since k can be large, we’ll prefer math/binary search.*/


#include <bits/stdc++.h>
using namespace std;

// Function to compute how many messages before ban
long long solve(long long k, long long x) {
    long long total = k * k; // total emotes in full triangle
    if (x > total) return 2 * k - 1; // can send all messages
    
    // Binary search over number of messages
    long long low = 1, high = 2 * k - 1, ans = 1;
    while (low <= high) {
        long long mid = (low + high) / 2;
        long long sum = 0;

        if (mid <= k) {
            // first half (increasing)
            sum = mid * (mid + 1) / 2;
        } else {
            // includes decreasing part
            long long j = mid - k; // steps into decreasing side
            sum = k * k - (j * (j + 1)) / 2;
        }

        if (sum >= x) {
            ans = mid; // ban occurs at this message
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return ans;
}

int main() {
    long long k, x;
    cin >> k >> x;
    cout << solve(k, x) << "\n";
    return 0;
}
