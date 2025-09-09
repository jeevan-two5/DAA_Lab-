/* Intuition

Effect of choosing + or -

If we pick add at index i:
Contribution = a[i] + b[i].

If we pick subtract at index i:
Contribution = a[i] - b[i].

Difference between add and subtract =

(a[i] + b[i]) - (a[i] - b[i]) = 2 * b[i]


So, picking add instead of subtract gives a gain of 2 * b[i].

Strategy

If b[i] > 0: add is beneficial (gain positive).

If b[i] < 0: add is harmful (gain negative), better to subtract.

If b[i] = 0: doesn’t matter.

✅ So, we should sort indices by descending 2 * b[i] (i.e., by b[i]),
and pick the top K positive b[i] to add.

All other indices → subtract.

Initial sum baseline
If we subtract everywhere:

baseline = Σ (a[i] - b[i])


Then, for each chosen index where we add instead, we add back 2 * b[i].

Greedy correctness
Since each "add" gives independent gain of 2*b[i], best is to take the largest K positive b[i] values.

🔹 Complexity

Compute baseline sum: O(n).

Sort b[]: O(n log n).

Pick top K positive b[i]: O(K).

👉 Overall: O(n log n)
👉 Space: O(1) extra (ignoring input).*/






#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, K;
    cin >> n >> K;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // baseline: subtract everywhere
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i] - b[i];
    }

    // sort by b[i] descending
    vector<long long> gains;
    for (int i = 0; i < n; i++) {
        if (b[i] > 0) gains.push_back(2 * b[i]);
    }
    sort(gains.rbegin(), gains.rend());

    // apply up to K best gains
    for (int i = 0; i < min(K, (int)gains.size()); i++) {
        sum += gains[i];
    }

    cout << sum << "\n";
    return 0;
}
