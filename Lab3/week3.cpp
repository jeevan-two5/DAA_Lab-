//Q1
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
//============Q2

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Swap helper
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition function (Lomuto scheme)
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }
    swap(arr[i], arr[high]);
    return i;
}

// Randomized partition
int randomizedPartition(int arr[], int low, int high) {
    int randomIndex = low + rand() % (high - low + 1);
    swap(arr[randomIndex], arr[high]);
    return partition(arr, low, high);
}

// QuickSelect: find kth smallest (0-indexed)
int quickSelect(int arr[], int low, int high, int k) {
    if (low <= high) {
        int pi = randomizedPartition(arr, low, high);

        if (pi == k) return arr[pi];
        else if (pi > k) return quickSelect(arr, low, pi - 1, k);
        else return quickSelect(arr, pi + 1, high, k);
    }
    return -1; // should not happen
}

int main() {
    srand(time(0));

    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++) cin >> arr[i];

    if (n % 2 == 1) {
        // odd length → middle element
        int median = quickSelect(arr, 0, n - 1, n / 2);
        cout << median << endl;
    } else {
        // even length → average of two middle elements
        int m1 = quickSelect(arr, 0, n - 1, n / 2 - 1);
        int m2 = quickSelect(arr, 0, n - 1, n / 2);
        cout << (m1 + m2) / 2.0 << endl; // print as double
    }

    return 0;
}

//===========Q3

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

double findMedianSortedArrays(vector<int>& arr1, vector<int>& arr2) {
    int m = arr1.size();
    int n = arr2.size();
    
    // Ensure arr1 is smaller
    if (m > n) return findMedianSortedArrays(arr2, arr1);

    int low = 0, high = m;
    while (low <= high) {
        int i = (low + high) / 2;           // partition arr1
        int j = (m + n + 1) / 2 - i;        // partition arr2

        int left1 = (i == 0) ? INT_MIN : arr1[i - 1];
        int right1 = (i == m) ? INT_MAX : arr1[i];
        
        int left2 = (j == 0) ? INT_MIN : arr2[j - 1];
        int right2 = (j == n) ? INT_MAX : arr2[j];

        if (left1 <= right2 && left2 <= right1) {
            // Correct partition
            if ((m + n) % 2 == 0) {
                return (max(left1, left2) + min(right1, right2)) / 2.0;
            } else {
                return max(left1, left2);
            }
        }
        else if (left1 > right2) {
            high = i - 1;  // too many elements from arr1
        } else {
            low = i + 1;   // too few elements from arr1
        }
    }
    return 0.0; // should never reach here
}

int main() {
    int m, n;
    cin >> m;
    vector<int> arr1(m);
    for (int i = 0; i < m; i++) cin >> arr1[i];
    cin >> n;
    vector<int> arr2(n);
    for (int i = 0; i < n; i++) cin >> arr2[i];

    cout << findMedianSortedArrays(arr1, arr2) << endl;
    return 0;
}

//===============Q4

#include <iostream>
#include <vector>
using namespace std;

long long maxHappiness(vector<int>& A) {
    long long total = 0;
    long long posSum = 0;
    int posCount = 0;

    for (int x : A) {
        if (x > 0) {
            posSum += x;
            posCount++;
        } else {
            total += x; // eat negatives (and zeros) individually
        }
    }

    // if there are positives, eat them all together in one step
    if (posCount > 0) {
        total += posCount * posSum;
    }

    return total;
}

int main() {
    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];

    cout << maxHappiness(A) << endl;
    return 0;
}

// now strassen multiplication
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;


void print_matrix(vector<vector<int>> &matrix) {
    for (auto &row : matrix) {
        for (auto &col : row) {
            cout << col << " ";
        }
        cout << endl;
    }
}

vector<vector<int>> add_matrix(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2) {
    int row = matrix1.size();
    int col = matrix1[0].size();
    vector<vector<int>> result(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
        for (int j = 0 ; j < col; j++) {
            result[i][j] = matrix1[i][j] + matrix2[i][j];
        }
    }
    return result;
}

vector<vector<int>> sub_matrix(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2) {
    int row = matrix1.size();
    int col = matrix1[0].size();
    vector<vector<int>> result(row, vector<int>(col, 0));
    for (int i = 0; i < row; i++) {
        for (int j = 0 ; j < col; j++) {
            result[i][j] = matrix1[i][j] - matrix2[i][j];
        }
    }
    return result;
}

vector<vector<int>> strassen_matrix_multiplication(vector<vector<int>> &matrix1, vector<vector<int>> &matrix2) {
    int row = matrix1.size();
    int col = matrix1[0].size();
    vector<vector<int>> result(row, vector<int>(col, 0));
    if (row == 1 && col == 1) {
        result[0][0] = matrix1[0][0] * matrix2[0][0];
        return result;
    }
    int new_row = row / 2;
    int new_col = col / 2;
    vector<vector<int>> a(new_row, vector<int>(new_col, 0));
    vector<vector<int>> b(new_row, vector<int>(new_col, 0));
    vector<vector<int>> c(new_row, vector<int>(new_col, 0));
    vector<vector<int>> d(new_row, vector<int>(new_col, 0));
    vector<vector<int>> e(new_row, vector<int>(new_col, 0));
    vector<vector<int>> f(new_row, vector<int>(new_col, 0));
    vector<vector<int>> g(new_row, vector<int>(new_col, 0));
    vector<vector<int>> h(new_row, vector<int>(new_col, 0));
    for (int i = 0; i < new_row; i++) {
        for (int j = 0; j < new_col; j++) {
            a[i][j] = matrix1[i][j];
            b[i][j] = matrix1[i][j + new_col];
            c[i][j] = matrix1[i + new_row][j];
            d[i][j] = matrix1[i + new_row][j + new_col];
            e[i][j] = matrix2[i][j];
            f[i][j] = matrix2[i][j + new_col];
            g[i][j] = matrix2[i + new_row][j];
            h[i][j] = matrix2[i + new_row][j + new_col];
        }
    }


    vector<vector<int>> ts1 = sub_matrix(f, h);
    vector<vector<int>> ts2 = add_matrix(a, b);
    vector<vector<int>> ts3 = add_matrix(c, d);
    vector<vector<int>> ts4 = sub_matrix(g, e);
    vector<vector<int>> ts5 = add_matrix(a, d);
    vector<vector<int>> ts6 = add_matrix(e, h);
    vector<vector<int>> ts7 = sub_matrix(b, d);
    vector<vector<int>> ts8 = add_matrix(g, h);
    vector<vector<int>> ts9 = sub_matrix(a, c);
    vector<vector<int>> ts10 = add_matrix(e, f);

    vector<vector<int>> p1 = strassen_matrix_multiplication(a,ts1);
    vector<vector<int>> p2 = strassen_matrix_multiplication(ts2,h);
    vector<vector<int>> p3 = strassen_matrix_multiplication(ts3,e);
    vector<vector<int>> p4 = strassen_matrix_multiplication(d,ts4);
    vector<vector<int>> p5 = strassen_matrix_multiplication(ts5,ts6);
    vector<vector<int>> p6 = strassen_matrix_multiplication(ts7,ts8);
    vector<vector<int>> p7 = strassen_matrix_multiplication(ts9,ts10);

    vector<vector<int>> tempA1 = add_matrix(p5,p4);
    vector<vector<int>> tempA2 = sub_matrix(tempA1,p2);
    vector<vector<int>> c11 = add_matrix(tempA2,p6);
    vector<vector<int>> c12 = add_matrix(p1,p2);
    vector<vector<int>> c21 = add_matrix(p3,p4);
    vector<vector<int>> tempA3 = add_matrix(p5,p1);
    vector<vector<int>> tempA4 = sub_matrix(tempA3,p3);
    vector<vector<int>> c22 = sub_matrix(tempA4,p7);
    
    for (int i = 0; i < new_row; i++) {
        for (int j = 0; j < new_col; j++) {
            result[i][j] = c11[i][j];
            result[i][j + new_col] = c12[i][j];
            result[i + new_row][j] = c21[i][j];
            result[i + new_row][j + new_col] = c22[i][j];
        }
    }
    return result;
}

int main(void) {
    /*
    
        Input format:

        First enter an integer n denoting size of the 2 matrices of size N x N.
        Then enter n*n integers for matrix1.
        Then enter n*n integers for matrix2.
    
    
    
    */

    int n;
    cout << "enter size of matrix: "<< endl;
    cin >> n;

    vector<vector<int>> matrix1(n, vector<int>(n, 0));
    vector<vector<int>> matrix2(n, vector<int>(n, 0));

    cout << "enter matrix1: " << endl;
    for (auto &row : matrix1) {
        for (auto &col : row) {
            cin >> col;
        }
    }

    cout << "enter matrix2: " << endl;
    for (auto &row : matrix2) {
        for (auto &col : row) {
            cin >> col;
        }
    }

    vector<vector<int>> result = strassen_matrix_multiplication(matrix1, matrix2);
    
    cout << "result: " << endl;
    print_matrix(result);
    return 0;
}
//=====end
