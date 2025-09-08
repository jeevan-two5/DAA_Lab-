/*
Goal

Sort floating-point numbers in [0,1).

Use Bucket Sort:

Create n buckets (where n = array size).

Distribute each element into a bucket based on its value.

Sort each bucket individually (here, using a linked list with merge sort).

Concatenate all buckets to get the final sorted array.

🔑 Intuition

Why buckets?

Numbers are uniformly distributed in [0,1).

So, elements spread evenly across buckets.

Each bucket will have only a few elements, so sorting inside them is efficient.

Linked list for each bucket:

Insert elements in O(1) time using a tail pointer.

Later, sort each bucket using merge sort on linked lists (O(m log m) per bucket, but overall O(n) expected).

Final step:

Merge all buckets in order to form the final sorted result.

⚡ Expected time complexity: O(n) (assuming uniform distribution). */

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

