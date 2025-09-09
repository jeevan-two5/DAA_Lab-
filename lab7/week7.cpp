//Q1
#include <bits/stdc++.h>
using namespace std;

// Partition function using a given pivot
int partition(vector<int>& arr, int left, int right, int pivot) {
    int pivotIndex;
    for (int i = left; i <= right; i++) {
        if (arr[i] == pivot) {
            pivotIndex = i;
            break;
        }
    }        
    swap(arr[pivotIndex], arr[right]); // move pivot to end
    pivotIndex = left;
    for (int i = left; i < right; i++) {
        if (arr[i] <= pivot) {
            swap(arr[i], arr[pivotIndex]);
            pivotIndex++;
        }
    }
    swap(arr[pivotIndex], arr[right]); // move pivot back
    return pivotIndex;
}

// Find median of a small group (size <= 5)
int findMedian(vector<int>& arr, int left, int right) {
    sort(arr.begin() + left, arr.begin() + right + 1);
    return arr[left + (right - left) / 2];
}

// Recursive function using Median of Medians
int kthSmallest(vector<int>& arr, int left, int right, int k) {
    if (left == right) return arr[left];

    // Step 1: Divide into groups of 5 and find medians
    vector<int> medians;             
    for (int i = left; i <= right; i += 5) {
        int subRight = min(i + 4, right);
        medians.push_back(findMedian(arr, i, subRight));
    }

    // Step 2: Find median of medians (pivot)
    int medOfMed;
    if (medians.size() == 1)
        medOfMed = medians[0];
    else
        medOfMed = kthSmallest(medians, 0, medians.size() - 1, medians.size() / 2);

    // Step 3: Partition array around pivot
    int pos = partition(arr, left, right, medOfMed);

    int count = pos - left + 1; // position of pivot in sorted order
    if (count == k) return arr[pos];
    else if (k < count) return kthSmallest(arr, left, pos - 1, k);
    else return kthSmallest(arr, pos + 1, right, k - count);
}

int main() {
    vector<int> arr = {7, 10, 4, 11, 8, 3, 20, 15};
    int K = 3;
    cout << "K-th smallest element is " << kthSmallest(arr, 0, arr.size() - 1, K) << endl;
    return 0;
}

//=========Q2=======
#include <bits/stdc++.h>
using namespace std;

int lengthOfLongestSubstring(string s) {
    
   
    vector<int> lastIndex(256, -1); // store last index of each character  , 
    // unordered_map<char,int>lastIndex;
    int left = 0, maxLen = 0;

    for (int right = 0; right < s.size(); right++) {
        // If character already seen, move left pointer
        if (lastIndex[s[right]] >= left) {
            left = lastIndex[s[right]] + 1;
        }
        lastIndex[s[right]] = right; // update last index
        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

int main() {
    string s = "abcabcbb";
    cout << "Length of longest substring: " << lengthOfLongestSubstring(s) << endl;
    return 0;
}

//        ================================================================end=======================
//Using unordered map

int lengthOfLongestSubstring(string s) {
    unordered_map<char, int> lastIndex; // store last seen index of each char
    int left = 0, maxLen = 0;

    for (int right = 0; right < s.size(); right++) {
        char c = s[right];
        // If char is already in map and inside current window
        if (lastIndex.find(c) != lastIndex.end() && lastIndex[c] >= left) {
            left = lastIndex[c] + 1; // move left pointer
        }
        lastIndex[c] = right; // update last index of current char
        maxLen = max(maxLen, right - left + 1);
    }

    return maxLen;
}

//========Q3====

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

//+++++++====Q4

class Solution {
public:
    string minWindow(string s, string t) {
        int m = t.size();
        int n = s.size();
        //int hash[256]={0};
        unordered_map<char,int>hash;
        int l = 0,r = 0; 
        int maxlen= 1e9;
        int SI = -1 ;//starting index
        for(int i = 0; i<m ;i++)  hash[t[i]]++;
        int cnt =0; int minlen = 1e9 ;
        while(r<s.size()){
            if(hash[s[r]] > 0)
                    cnt+=1;
                    hash[s[r]]--;

            while(cnt == m){
                if(r-l+1 < minlen){
                   minlen = r-l+1;
                    SI = l;
                }
                hash[s[l]]++;
                if(hash[s[l]] > 0) cnt = cnt -1;
                 l++;
            }
            
            r = r+1;
        }

        return SI == -1 ? "" : s.substr(SI,minlen);
    }
};

//=============Q5========

class Solution {
    vector<int>f(vector<int>& arr, int n){
        int k = n/3;
        //int c= 0; 
        vector<int>ans;
        unordered_map<int, int>hash;
        for(int i = 0; i<n; i++) hash[arr[i]]++;

        for(int i = 0; i<n;i++){
            if(hash[arr[i]] > k && hash[arr[i]] >0){
                //c = 1;
                ans.push_back(arr[i]);
                hash[arr[i]] = 0;
            }
        }
        return ans;

    }



public:
    vector<int> majorityElement(vector<int>& nums) {
        int n = nums.size();
        return f(nums,n);
    }
};
