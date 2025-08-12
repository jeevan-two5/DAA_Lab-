// Q1  Given an integer arr ,  find three numbers whose product is the maximum and return maximum product
#include <bits/stdc++.h>
using namespace std;

// int findProd(int ind, int cnt, vector<int> &a){
//     if(cnt <= 0) return 1;
//     if(ind < 0) return 0;

//     int notTake = findProd(ind-1, cnt, a);
//     int take = a[ind]*findProd(ind-1, cnt-1, a);

//     return max(take, notTake);
// }

int main(){
    int n;
    cin >> n;
    
    if(n < 3){
        cout << "Array must contain atleast 3 elements" << endl;
        return 0;
    }

    vector<int> a(n);
    for(auto &it:a) 
        cin >> it;
    
    // if(n == 3){
    //     cout << a[0]*a[1]*a[2] << endl;
    // }

    // cout << findProd(n-1, 3, a) << endl;

    sort(a.begin(), a.end());
    cout << a[n-1]*a[n-2]*a[n-3] << endl;

    return 0;
}

// an integer k , return the kth largest element in arr


#include <bits/stdc++.h>
using namespace std;

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[left];

    int l = left + 1;
    int r = right;

    while (l <= r) {
        if (arr[l] < pivot && arr[r] > pivot) {
            swap(arr[l], arr[r]);
            l++ ;
            r-- ;
        }
        if (arr[l] >= pivot) {
            l++;
        }
        if (arr[r] <= pivot) {
            r--;
        }
    }

    swap(arr[left], arr[r]);

    return r;
}

int find_Kth_largest(vector<int> &a, int k){
    int left = 0, right = a.size() - 1;

    while (left <= right) {
        int ind = partition(a, left, right);

        if (ind == k - 1) {
            return a[ind];
        }

        if (ind < k - 1) {
            left = ind + 1;
        } else {
            right = ind - 1;
        }
    }

    return -1;
}

int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for(auto &it:a) 
        cin >> it;

    int k; 
    cin >> k;

    cout << find_Kth_largest(a, k) << endl;
    
    return 0;
}

// You are given an integer N , your task is to find and return the Nth Fibonacci number using matrix exponentiation  

#include <bits/stdc++.h>
using namespace std;

void multiply(int f[2][2], int m[2][2]){
    int a = f[0][0]*m[0][0] + f[0][1]*m[1][0];
    int b = f[0][0]*m[0][1] + f[0][1]*m[1][1];
    int c = f[1][0]*m[0][0] + f[1][1]*m[1][0];
    int d = f[1][0]*m[0][1] + f[1][1]*m[1][1];

    f[0][0] = a;
    f[0][1] = b;
    f[1][0] = c;
    f[1][1] = d;

    return;
}

void power(int f[2][2], int n){
    if(n == 0 || n == 1)
        return;
    
    int m[2][2] = {{1, 1}, {1, 0}};

    power(f, n/2);

    multiply(f, f);

    if(n%2 != 0)
        multiply(f, m);
    
    return;
}

int Nth_fibonacci(int n){
    int f[2][2] = {{1, 1}, {1, 0}};

    if(n == 0) 
        return 0;
    
    power(f, n-1);

    return f[0][0];
}

int main(){
    int n;
    cin >> n;

    cout << Nth_fibonacci(n) << endl;
    
    return 0;
}

// Given unsorted array , find and return the smallest positive integer that is missing from the array

#include <bits/stdc++.h>
using namespace std;

int findSmallestPositiveAbsent(vector<int> &a){
    int n = a.size();

    for(int i=0; i<n;){
        if(a[i] <= 0 || a[i] > n){
            i++;
            continue;
        }

        int correctInd = a[i]-1;

        if(a[i] != a[correctInd])
            swap(a[i], a[correctInd]);
        else
            i++;
    }

    for (int i=0; i<n; i++){
        if(a[i] != i+1){
            return i+1;
        }
    }
    
    return n+1;
}

int main(){
    int n;
    cin >> n;

    vector<int> a(n);
    for(auto &it:a) 
        cin >> it;

    cout << findSmallestPositiveAbsent(a) << endl;
    
    return 0;
}

//  You are given an array consisting of N integers. Sort the array in non-decreasing order using the Heap sort algorithm , making use of heapify() and buildHeap() 
#include <bits/stdc++.h>
using namespace std;

void print(vector<int> &v) {
    for (auto it : v)
        cout << it << " ";
    cout << endl;
    return;
}

void heapify(vector<int> &a, int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest])
        largest = l;

    if (r < n && a[r] > a[largest])
        largest = r;

    if (largest != i) {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }

    return;
}

void buildHeap(vector<int> &a) {
    int n = a.size();

    // last non-leaf node index
    int startInd = (n / 2) - 1;

    for (int i = startInd; i >= 0; i--) {
        heapify(a, n, i);
    }

    return;
}

void heapSort(vector<int> &a) {
    int n = a.size();

    buildHeap(a);

    for (int i = n - 1; i > 0; i--) {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }

    return;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    heapSort(a);

    print(a);

    return 0;
}

// Given a string s , rearrange its characters in such a way that no two adjacent characters are the same . TC: O(NlogN) SC: O(1)
#include <bits/stdc++.h>
using namespace std;

string rearrange(string s) {
    int n = s.size();

    if (n == 1)
        return s;

    unordered_map<char, int> mp;
    for (auto i : s) {
        mp[i]++;
    }

    priority_queue<pair<int, char>> pq;
    for (auto it : mp) {
        pq.push({it.second, it.first});
    }

    string ans = "";

    int maxCnt = pq.top().first;
    if (maxCnt > (n + 1) / 2)
        return ans;

    while (!pq.empty()) {
        auto i = pq.top();
        pq.pop();

        if (pq.empty()) {
            ans += i.second;
            break;
        }

        auto j = pq.top();
        pq.pop();

        i.first--;
        j.first--;

        ans += i.second;
        ans += j.second;

        if (i.first > 0)
            pq.push({i.first, i.second});
        if (j.first > 0)
            pq.push({j.first, j.second});
    }

    return ans;
}

int main() {
    string s;
    cin >> s;

    cout << rearrange(s) << endl;

    return 0;
}

// You have been given K different arrays , which are sorted individually . You need to merge aal the given arrays such that output array is sorted in non decreasing order
#include <bits/stdc++.h>
using namespace std;

void print(vector<int> &v) {
    for (auto it : v)
        cout << it << " ";
    cout << endl;
    return;
}

vector<int> merge(vector<int> &a, vector<int> &b) {
    int n = a.size();
    int m = b.size();

    vector<int> ans(n + m);

    int i = 0, j = 0, k = 0;

    while (i < n && j < m) {
        if (a[i] < b[j])
            ans[k++] = a[i++];
        else
            ans[k++] = b[j++];
    }

    while (i < n)
        ans[k++] = a[i++];

    while (j < m)
        ans[k++] = b[j++];

    return ans;
}

vector<int> merge_k_arrays(vector<vector<int>> &a, int i, int j) {
    int k = j - i + 1;

    if (k == 1)
        return a[i];

    if (k == 2)
        return merge(a[i], a[j]);

    vector<int> temp1 = merge_k_arrays(a, i, i + k / 2);
    vector<int> temp2 = merge_k_arrays(a, i + k / 2 + 1, j);

    return merge(temp1, temp2);
}

int main() {
    int k;
    cin >> k;

    vector<vector<int>> a;

    for (int i = 0; i < k; i++) {
        int n;
        cin >> n;

        vector<int> temp(n);
        for (int j = 0; j < n; j++)
            cin >> temp[j];

        a.push_back(temp);
    }

    vector<int> ans = merge_k_arrays(a, 0, k - 1);

    print(ans);

    return 0;
}

// find kth smallest element in a given array using Median of Median

#include <bits/stdc++.h>
using namespace std;

int findMedian(vector<int> &a, int start, int n) {
    sort(a.begin() + start, a.begin() + start + n);
    return a[start + n / 2];
}

int partition(vector<int> &a, int low, int high, int pivot) {
    for (int i = low; i < high; i++) {
        if (a[i] == pivot) {
            swap(a[i], a[high]);
            break;
        }
    }

    int pivotValue = a[high];
    int i = low;

    for (int j = low; j < high; j++) {
        if (a[j] < pivotValue) {
            swap(a[i], a[j]);
            i++;
        }
    }

    swap(a[i], a[high]);

    return i;
}

int kthSmallest(vector<int> &a, int low, int high, int k) {
    if (low == high)
        return a[low];

    int n = high - low + 1;
    int numMedians = (n + 4) / 5;

    vector<int> medians(numMedians);

    for (int i = 0; i < numMedians; i++) {
        int groupStart = low + i * 5;
        int groupSize = min(5, n - i * 5);
        medians[i] = findMedian(a, groupStart, groupSize);
    }

    int medianOfMedians = (numMedians == 1) ? medians[0] : kthSmallest(medians, 0, numMedians - 1, numMedians / 2);

    int pivotIndex = partition(a, low, high, medianOfMedians);

    int length = pivotIndex - low + 1;

    if (length == k)
        return a[pivotIndex];
    else if (k < length)
        return kthSmallest(a, low, pivotIndex - 1, k);
    return kthSmallest(a, pivotIndex + 1, high, k - length);
}

int findKthSmallest(vector<int> &a, int k) {
    return kthSmallest(a, 0, a.size() - 1, k);
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int k;
    cin >> k;

    cout << findKthSmallest(a, k) << endl;

    return 0;
}

// Sort an array using counting sort
#include <bits/stdc++.h>
using namespace std;

void print(vector<int> &a) {
    for (auto &it : a)
        cout << it << " ";
    cout << endl;
    return;
}

vector<int> counting_sort(vector<int> &a) {
    int n = a.size();

    int maxx = *max_element(a.begin(), a.end());
    vector<int> count(maxx + 1, 0);

    for (int i = 0; i < n; i++) {
        count[a[i]]++;
    }

    for (int i = 1; i <= maxx; i++) {
        count[i] += count[i - 1];
    }

    vector<int> b(n);
    for (int i = n - 1; i >= 0; i--) {
        b[count[a[i]] - 1] = a[i];
        count[a[i]]--;
    }

    return b;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> ans = counting_sort(a);

    print(ans);

    return 0;
}

// sort an arr by bucket sort
#include <bits/stdc++.h>
using namespace std;

void print(vector<double> &a) {
    for (auto &it : a)
        cout << it << " ";
    cout << endl;
    return;
}

void bucket_sort(vector<double> &a) {
    int n = a.size();

    vector<vector<double>> bucket(n);

    for (int i = 0; i < n; i++) {
        int hash = n * a[i];
        bucket[hash].push_back(a[i]);
    }

    for (int i = 0; i < n; i++) {
        sort(bucket[i].begin(), bucket[i].end());
    }

    int ind = 0;
    for (int i = 0; i < n; i++) {
        for (auto &it : bucket[i]) {
            a[ind++] = it;
        }
    }

    return;
}

int main() {
    int n;
    cin >> n;

    vector<double> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    bucket_sort(a);

    print(a);

    return 0;
}

//given arr and int K , task: return the number of good subarrays , good subarray = contiguous part of the array that contains exactly k different intergers

#include <bits/stdc++.h>
using namespace std;

int at_most_k_diff_elements(vector<int> &a, int k) {
    int n = a.size();

    int count = 0, left = 0, right = 0;

    unordered_map<int, int> mpp;

    while (right < n) {
        if (mpp.find(a[right]) == mpp.end())
            mpp[a[right]] = 0;

        mpp[a[right]]++;

        while (mpp.size() > k) {
            mpp[a[left]]--;

            if (mpp[a[left]] == 0)
                mpp.erase(a[left]);

            left++;
        }

        count += (right - left);

        right++;
    }

    return count;
}

int count_good_subarrays(vector<int> &a, int k) {
    return at_most_k_diff_elements(a, k) - at_most_k_diff_elements(a, k - 1);
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int k;
    cin >> k;

    cout << count_good_subarrays(a, k) << endl;

    return 0;
}

// given A , containing n integers , perform operation k no of times , the operation will be choosing an index i , and multiply A[i] by m ,
//Here m is also given  , find the minimum possible sum of the array A after k operations. this sum may be large so you have to print mudulo 10^9  + 7 

#include <bits/stdc++.h>
using namespace std;

int MOD = 1e9 + 7;

int binary_exponentiation(int x, int n) {
    int ans = 1, k = x;

    while (n) {
        if (n % 2)
            ans = ans * (k % MOD) % MOD;

        k = ((k % MOD) * (k % MOD)) % MOD;

        n /= 2;
    }

    return ans;
}

int min_sum(vector<int> &a, int k, int m) {
    int n = a.size();

    multiset<int> ms;

    for (auto &it : a)
        ms.insert(it);

    while (k > 0 && (*ms.begin() * m < *ms.rbegin())) {
        int it = *ms.begin();
        ms.erase(ms.find(it));
        ms.insert(it * m);
        k--;
    }

    auto x = ms.begin();
    for (auto &it : a) {
        it = *(x++);
    }

    for (auto &it : a) {
        it = (it * binary_exponentiation(m, k / n)) % MOD;
    }

    for (int i = 0; i < k % n; i++) {
        a[i] = (a[i] * m) % MOD;
    }

    int sum = 0;
    for (auto &it : a) {
        sum = (sum + it) % MOD;
    }

    return sum;
}

int main() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int k, m;
    cin >> k >> m;

    cout << min_sum(a, k, m) << endl;

    return 0;
}






