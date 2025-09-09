/* Intuition

Naive approach
Generate all sums a[i] + b[j], sort them, pick top k.

Complexity: O(n² log n²) → not feasible for large n.

Observation

If a and b are both sorted descending, the largest sum must involve the largest elements from both arrays.

Instead of all pairs, we can expand gradually from the maximum using a max-heap (priority queue).

Heap + Set approach

Sort a and b in descending order.

The largest sum is a[0] + b[0].

Push this into a max-heap with indices (0,0).

Repeatedly pop the max sum, and then push its neighbors (i+1,j) and (i,j+1) (if not already pushed).

Use a set to avoid duplicates.

Stop after extracting k sums.

Why it works

Because arrays are sorted, moving right or down decreases the sum.

The heap always keeps the next best candidate.

So we efficiently generate only the top k sums without expanding all pairs.

🔹 Complexity

Sorting a and b: O(n log n)

Each heap push/pop: O(log k)

We do at most k pops and pushes.

👉 Overall: O(n log n + k log k)
👉 Space: O(k) (for heap + set).

Efficient for large n, small/medium k.*/



#include <bits/stdc++.h>
using namespace std;

vector<int> kMaxSums(vector<int>& a, vector<int>& b, int k) {
    int n = a.size();
    sort(a.begin(), a.end(), greater<int>());
    sort(b.begin(), b.end(), greater<int>());

    priority_queue<pair<int, pair<int,int>>> pq; // {sum, {i,j}}
    set<pair<int,int>> seen;

    // start with largest sum
    pq.push({a[0] + b[0], {0,0}});
    seen.insert({0,0});

    vector<int> result;
    while (k-- && !pq.empty()) {
        auto cur = pq.top(); pq.pop();
        int sum = cur.first;
        int i = cur.second.first;
        int j = cur.second.second;
        result.push_back(sum);

        // next candidates
        if (i+1 < n && !seen.count({i+1, j})) {
            pq.push({a[i+1] + b[j], {i+1, j}});
            seen.insert({i+1, j});
        }
        if (j+1 < n && !seen.count({i, j+1})) {
            pq.push({a[i] + b[j+1], {i, j+1}});
            seen.insert({i, j+1});
        }
    }
    return result;
}

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    vector<int> ans = kMaxSums(a, b, k);
    for (int x : ans) cout << x << " ";
    cout << "\n";
}
