/*🔹 Normal Quick Sort Idea

Pick a pivot element from the array.

Partition the array into two halves:

Left half: elements ≤ pivot

Right half: elements > pivot

Recursively sort the left and right halves.

Combine results → sorted array.

➡️ This works in-place (no extra arrays), so space is only from recursion.

🔹 Problem with Normal Quick Sort

If we always pick bad pivots (like smallest or largest element), Quick Sort degenerates into O(N²) time (like Bubble Sort).
Example: sorting an already sorted array with first/last element as pivot.

🔹 Randomization Trick

To avoid consistently bad pivots:

Instead of picking a fixed pivot (like always last element),

Randomly pick a pivot index between low and high.

Swap it with the last element and partition as usual.

💡 Why does this help?
Because the chance of always picking bad pivots is extremely small when pivots are chosen randomly.
So, on average:

Expected time complexity becomes O(N log N).

Worst case still exists (O(N²)), but highly unlikely.*/
#include <iostream>
#include <cstdlib>   // for rand()
#include <ctime>     // for seeding rand()

using namespace std;

// Function to swap two elements
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Standard partition process (Lomuto partition)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];  
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

// Randomized partition
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]); // Place random pivot at end
    return partition(arr, low, high);
}

// Randomized QuickSort
void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

int main() {
    srand(time(0)); // Seed for random pivot

    int N;
    cin >> N;
    int arr[N];

    for (int i = 0; i < N; i++)
        cin >> arr[i];

    randomizedQuickSort(arr, 0, N - 1);

    for (int i = 0; i < N; i++) {
        cout << arr[i];
        if (i != N - 1) cout << ", ";
    }
    cout << endl;

    return 0;
}
