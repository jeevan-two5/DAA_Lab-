//Q1
#include <bits/stdc++.h>
using namespace std;

// Partition function (like QuickSort)
int partition(vector<int>& arr, int l, int r) {
    int pivot = arr[r];
    int i = l;
    for (int j = l; j < r; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[r]);
    return i;
}

// Randomized partition (chooses random pivot)
int randomizedPartition(vector<int>& arr, int l, int r) {
    int pivotIndex = l + rand() % (r - l + 1);
    swap(arr[pivotIndex], arr[r]); // Move random pivot to end
    return partition(arr, l, r);
}

// Randomized Select (Quickselect)
int randomizedSelect(vector<int>& arr, int l, int r, int k) {
    if (l == r)
        return arr[l];

    int pos = randomizedPartition(arr, l, r);
    int rank = pos - l + 1; // Number of elements in left partition + pivot

    if (k == rank)
        return arr[pos]; // Found k-th smallest
    else if (k < rank)
        return randomizedSelect(arr, l, pos - 1, k);
    else
        return randomizedSelect(arr, pos + 1, r, k - rank);
}

int main() {
    srand(time(0)); // Seed random number generator

    vector<int> arr = {10, 25, 3, 1, 15, 11};
    int k = 3; // 3rd smallest

    int result = randomizedSelect(arr, 0, arr.size() - 1, k);

    cout << k << "-th smallest element is: " << result << endl;

    return 0;
}

//Q2
#include <bits/stdc++.h>
using namespace std;

vector<int> kthLargestStream(vector<int>& A, int n, int k) {
    vector<int> B; // answer array
    priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap of size k

    for (int i = 0; i < n; i++) {
        minHeap.push(A[i]);

        // Keep only top k largest elements
        if ((int)minHeap.size() > k)
            minHeap.pop();

        // Once we have at least k elements, record the k-th largest
        if (i >= k - 1)
            B.push_back(minHeap.top());
    }

    return B;
}

int main() {
    int n = 8, k = 3;
    vector<int> A = {4, 5, 8, 2, 3, 5, 10, 9};

    vector<int> result = kthLargestStream(A, n, k);

    cout << "Output: ";
    for (int x : result)
        cout << x << " ";
    cout << endl;

    return 0;
}

//Q3
#include <bits/stdc++.h>

using namespace std;
vector<double> runningMedian(vector<int>& A, int n) {
    // Max-heap for left half
    priority_queue<int> left;
    // Min-heap for right half
    priority_queue<int, vector<int>, greater<int>> right;

    vector<double> B;

    for (int i = 0; i < n; i++) {
        int num = A[i];

        // Step 1: Insert into correct heap
        if (left.empty() || num <= left.top())
            left.push(num);
        else
            right.push(num);

        // Step 2: Balance heaps (size difference ≤ 1)
        if (left.size() > right.size() + 1) {
            right.push(left.top());
            left.pop();
        } else if (right.size() > left.size()) {
            left.push(right.top());
            right.pop();
        }

        // Step 3: Find median
        if (left.size() == right.size()) {
            double median = (left.top() + right.top()) / 2.0;
            B.push_back(median);
        } else {
            B.push_back(left.top()); // left will always have 1 more if uneven
        }
    }

    return B;
}

int main() {
    int n = 6;
    vector<int> A = {4, 5, 8, 2, 3, 1};

    vector<double> result = runningMedian(A, n);

    cout << "Output: ";
    for (double x : result)
        cout << x << " ";
    cout << endl;

    return 0;
}

//Q4
#include <bits/stdc++.h>
using namespace std;

void nextPermutation(vector<int>& arr) {
    int n = arr.size();
    int i = n - 2;

    // Step 1: Find first decreasing element from right
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    if (i >= 0) {
        // Step 2: Find element just larger than arr[i]
        int j = n - 1;
        while (arr[j] <= arr[i]) j--;

        // Step 3: Swap pivot and successor
        swap(arr[i], arr[j]);
    }

    // Step 4: Reverse the suffix
    reverse(arr.begin() + i + 1, arr.end());
}

int main() {
    vector<int> arr = {2, 4, 1, 7, 5, 0};
    nextPermutation(arr);

    cout << "Next permutation: ";
    for (int x : arr) cout << x << " ";
    cout << endl;

    return 0;
}
// Q5
#include <bits/stdc++.h>
using namespace std;

class LinkedList {
    struct Node {
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };

    Node* head;

    // Utility function to split list into two halves
    Node* getMiddle(Node* h) {
        if (!h || !h->next) return h;
        Node* slow = h, *fast = h->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* mid = slow->next;
        slow->next = nullptr;
        return mid;
    }

    // Merge two sorted lists
    Node* merge(Node* l1, Node* l2) {
        if (!l1) return l2;
        if (!l2) return l1;

        if (l1->data < l2->data) {
            l1->next = merge(l1->next, l2);
            return l1;
        } else {
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }

    // Merge Sort
    Node* mergeSort(Node* h) {
        if (!h || !h->next) return h;

        Node* mid = getMiddle(h);
        Node* left = mergeSort(h);
        Node* right = mergeSort(mid);

        return merge(left, right);
    }

public:
    LinkedList(vector<int>& arr) {
        head = nullptr;
        Node* tail = nullptr;
        for (int x : arr) {
            Node* newNode = new Node(x);
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
        }
    }

    void sort() {
        head = mergeSort(head);
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    vector<int> arr = {3, 1, 4, 2};
    LinkedList ll(arr);

    ll.sort();
    ll.print();  // Output: 1 2 3 4

    return 0;
}

//Q6
#include <bits/stdc++.h>
using namespace std;

class LinkedList {
    struct Node {
        double data;
        Node* next;
        Node(double val) : data(val), next(nullptr) {}
    };

    Node* head;
    Node* tail;

    // Split linked list into two halves
    Node* getMiddle(Node* h) {
        if (!h || !h->next) return h;
        Node* slow = h, *fast = h->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        Node* mid = slow->next;
        slow->next = nullptr;
        return mid;
    }

    // Merge two sorted linked lists
    Node* merge(Node* l1, Node* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        if (l1->data < l2->data) {
            l1->next = merge(l1->next, l2);
            return l1;
        } else {
            l2->next = merge(l1, l2->next);
            return l2;
        }
    }

    // Merge sort for linked list
    Node* mergeSort(Node* h) {
        if (!h || !h->next) return h;
        Node* mid = getMiddle(h);
        Node* left = mergeSort(h);
        Node* right = mergeSort(mid);
        return merge(left, right);
    }

public:
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Insert element at end in O(1)
    void insert(double val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    // Sort bucket using merge sort
    void sort() {
        head = mergeSort(head);
    }

    // Traverse bucket and add elements to output
    void collect(vector<double>& result) {
        Node* temp = head;
        while (temp) {
            result.push_back(temp->data);
            temp = temp->next;
        }
    }
};

// Bucket sort function
void bucketSort(vector<double>& arr) {
    int n = arr.size();
    vector<LinkedList> buckets(n);

    // Step 1: Distribute elements into buckets
    for (double val : arr) {
        int idx = n * val; // index based on range [0,1)
        buckets[idx].insert(val);
    }

    // Step 2: Sort each bucket
    for (int i = 0; i < n; i++) {
        buckets[i].sort();
    }

    // Step 3: Collect results back into arr
    arr.clear();
    for (int i = 0; i < n; i++) {
        buckets[i].collect(arr);
    }
}

int main() {
    vector<double> arr = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};

    bucketSort(arr);

    cout << "Sorted array: ";
    for (double x : arr) cout << x <
