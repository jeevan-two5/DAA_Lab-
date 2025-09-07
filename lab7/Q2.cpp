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
