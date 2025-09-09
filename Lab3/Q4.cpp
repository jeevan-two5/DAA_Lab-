/*🔎 Intuition

We want to maximize the total happiness.

If we eat dishes one by one → each contributes only 1 * A[i].

If we group them together → each dish contributes multiple times (because subset size multiplies the sum).

👉 Therefore, positive happiness values should be eaten together in the same step to amplify their effect.

👉 Negative values, however, decrease happiness if grouped with positives, so they should be eaten individually in separate steps.

Step-by-step reasoning:

Separate positive and non-positive dishes.

Positive → group them all together in one step.

Zero or negative → best eaten individually.

Why?

Suppose positives = {2,3,1}. Eating together:
3 * (2+3+1) = 18 (maximized).

If eaten separately: 1*2 + 1*3 + 1*1 = 6 (much smaller).

For negatives, grouping them reduces happiness more because the multiplier grows while the sum stays negative.
Example: {-8, -2}
Together → 2 * (-10) = -20
Separately → -8 + -2 = -10 (better).

Thus, the optimal strategy is:

Eat all positives in one step.

Eat all non-positives individually*/


//          =========================CODE=====================
             
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
