//Q1
#include <iostream>
using namespace std;
// Function to find first occurrence of x
int firstOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;       // store answer
            high = mid - 1;  // go left for first occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

// Function to find last occurrence of x
int lastOccurrence(int arr[], int n, int x) {
    int low = 0, high = n - 1, ans = -1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == x) {
            ans = mid;       // store answer
            low = mid + 1;   // go right for last occurrence
        } else if (arr[mid] < x) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}

int main() {
    int n, x;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];
    cin >> x;

    int first = firstOccurrence(arr, n, x);
    int last = lastOccurrence(arr, n, x);

    cout << first << " " << last << endl;
    return 0;
}

//==========================Q2============

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

//============================Q3==============================

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

//=================================Q4===========================
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

//===================END======================
