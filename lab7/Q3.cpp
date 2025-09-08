/* 
Let’s define prefix sum:

prefix[i]=arr[0]+arr[1]+...+arr[i]
The sum of subarray arr[l..r] is:

sum(l..r)=prefix[r]−prefix[l−1]
For divisibility:

sum(l..r)%k=0
That means:

prefix[r]%k=prefix[l−1]%k
👉 So two prefix sums with the same remainder modulo k imply the subarray between them is divisible by k.

Key Insight

We don’t need actual sums, only remainders (modulo values).

If the same remainder appears multiple times, each pair of indices forms a valid subarray.

So we:

Traverse the array.

Compute running prefix sum modulo 
𝑘
k.

Keep a frequency map of remainders.

Whenever a remainder repeats, add the frequency of that remainder to our count.
*/

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
