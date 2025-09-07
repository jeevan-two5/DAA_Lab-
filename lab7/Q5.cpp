
//Done by sravani

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
