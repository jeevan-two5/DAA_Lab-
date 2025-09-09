/* he brute force idea is:
For each pair (i, j), check if Pj votes for Pi. That’s O(N²) checks → too slow.

To optimize, notice the condition:

If j < i:

arr[j] ≥ prefix[i-1] - prefix[j]
⟺ prefix[j] + arr[j] ≥ prefix[i-1]


If j > i:

arr[j] ≥ prefix[j-1] - prefix[i]
⟺ prefix[j-1] ≤ prefix[i] + arr[j]


So instead of summing ranges every time, we reduce the check to comparing prefix sums.

Now the task becomes:

For each i, count how many j < i have prefix[j] + arr[j] ≥ prefix[i-1].

For each i, count how many j > i have prefix[j-1] ≤ prefix[i] + arr[j].

That’s essentially range counting problems:

“How many past values are ≥ X?”

“How many future values are ≤ Y?”

These are classic queries solved by:

Binary Indexed Tree (Fenwick Tree) or

Balanced BST / Ordered multiset

with coordinate compression to handle large values.

We do:

Sweep from left to right to count votes from left side.

Sweep from right to left to count votes from right side.
Each sweep uses a Fenwick tree for fast queries.

🔹 Complexity

Prefix sums: O(N)

Coordinate compression: O(N log N)

Two sweeps (BIT operations):

Each update/query = O(log N)

N updates/queries per sweep → O(N log N)

👉 Total: O(N log N)
👉 Extra space: O(N) (for prefix sums, BIT arrays, compression storage)*/


#include <bits/stdc++.h>
using namespace std;

// Fenwick Tree
struct BIT {
    int n;
    vector<int> bit;
    BIT(int n) : n(n), bit(n+1, 0) {}
    void update(int i, int val) {
        for (++i; i <= n; i += i & -i) bit[i] += val;
    }
    int query(int i) {
        int s = 0;
        for (++i; i > 0; i -= i & -i) s += bit[i];
        return s;
    }
    int rangeQuery(int l, int r) {
        if (l > r) return 0;
        return query(r) - (l ? query(l-1) : 0);
    }
};

int main() {
    int N;
    cin >> N;
    vector<long long> arr(N);
    for (int i = 0; i < N; i++) cin >> arr[i];

    vector<long long> prefix(N);
    prefix[0] = arr[0];
    for (int i = 1; i < N; i++) prefix[i] = prefix[i-1] + arr[i];

    vector<int> votes(N, 0);

    // ---- LEFT to RIGHT (j < i) ----
    vector<long long> vals;
    for (int j = 0; j < N; j++) vals.push_back(prefix[j] + arr[j]);
    for (int i = 0; i < N; i++) if (i > 0) vals.push_back(prefix[i-1]);

    // coordinate compression
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto getIdx = [&](long long x) {
        return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    BIT bit(vals.size());
    for (int i = 0; i < N; i++) {
        if (i > 0) {
            int idx = getIdx(prefix[i-1]);
            // count how many prefix[j]+arr[j] ≥ prefix[i-1]
            votes[i] += bit.rangeQuery(idx, vals.size()-1);
        }
        int idx = getIdx(prefix[i] + arr[i]);
        bit.update(idx, 1);
    }

    // ---- RIGHT to LEFT (j > i) ----
    vals.clear();
    for (int j = 0; j < N; j++) vals.push_back(prefix[j]);
    for (int i = 0; i < N; i++) vals.push_back(prefix[i] + arr[i]);
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    auto getIdx2 = [&](long long x) {
        return (int)(lower_bound(vals.begin(), vals.end(), x) - vals.begin());
    };

    BIT bit2(vals.size());
    for (int i = N-1; i >= 0; i--) {
        // count how many future j satisfy prefix[j-1] ≤ prefix[i] + arr[j]
        // (we stored prefix[j-1] in BIT)
        int idx = getIdx2(prefix[i] + arr[i]);
        votes[i] += bit2.query(idx);
        // insert prefix[i] for future queries
        int idx2 = getIdx2(prefix[i]);
        bit2.update(idx2, 1);
    }

    for (int i = 0; i < N; i++) cout << votes[i] << " ";
    cout << "\n";
}
