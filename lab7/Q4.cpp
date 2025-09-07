
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
