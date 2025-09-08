/* 
We want to sort a singly linked list optimally.

Array-based algorithms like QuickSort or HeapSort aren’t suitable for linked lists (random access is missing).

The best choice is Merge Sort, because it works well on linked lists:

Easy to split a list into halves (using slow/fast pointers).

Easy to merge sorted halves.

Naturally O(n log n).

Space complexity = recursion stack = O(log n).

🔑 Intuition

Divide:

Use slow & fast pointers to split the list into two halves.

Conquer:

Recursively sort the left half and right half.

Combine:

Merge the two sorted halves into one sorted list.

⚡ Why Merge Sort for Linked Lists?

Unlike arrays, we don’t need extra space to merge; we just relink pointers.

Merge step is O(n).

Overall time = O(n log n), space = O(log n) (recursion).*/

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
