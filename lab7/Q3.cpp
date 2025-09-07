#include <bits/stdc++.h>
using namespace std;

int subarraysDivByK(vector<int>& arr, int k) {
    unordered_map<int, int> freq;
    freq[0] = 1; // empty prefix remainder

    int prefixSum = 0, count = 0;
    for (int num : arr) {
        prefixSum += num;
        int remainder = prefixSum % k;

        // fix negative remainder
        if (remainder < 0) remainder += k;

        // add subarrays ending here
        count += freq[remainder];

        // record this remainder
        freq[remainder]++;
    }
    return count;
}

int main() {
    vector<int> arr = {-1, 2, 9};
    int k = 2;
    cout << "Number of subarrays: " << subarraysDivByK(arr, k) << endl;
    return 0;
}
