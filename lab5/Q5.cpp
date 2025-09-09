/*Intuition

Relation between XOR and sum
For any two numbers:

A ⊕ B + 2 × (A & B) = A + B


But here, we don’t need A & B. Still, useful to remember.

Constraint from XOR
If A ⊕ B = C, then for every bit:

If C has bit = 0 → bits of A and B are equal.

If C has bit = 1 → bits of A and B differ.

So (A, B) is completely determined once we decide how to split bits of C.

Binary length restriction
Let L = floor(log2(C)) + 1.
Then A, B < 2^L.

How to maximize product A × B?

For fixed A ⊕ B = C, the sum is:

A + B = C + 2×(A & B)


So maximizing product means making A and B as close as possible, given their sum.
(Recall: For fixed sum, product is maximized when numbers are equal / close).

Key trick
Let msb = highest power of 2 ≤ C.
Then consider numbers in the range [0, 2^L - 1].

The optimal pair is:

A = (2^L - 1) ^ C
B = C


or equivalently (A, B) = (C, (2^L - 1) ^ C).
Because this balances the bits: one takes C, the other takes the "complement" within L bits.

This ensures they differ exactly as required by XOR, and product is maximized (they are close).

🔹 Complexity

Just compute L, then compute one XOR.
👉 Time: O(1)
👉 Space: O(1)*/



#include <bits/stdc++.h>
using namespace std;

int main() {
    long long C;
    cin >> C;

    // find binary length of C
    int L = 64 - __builtin_clzll(C); // number of bits in C
    long long mask = (1LL << L) - 1; // all 1s in L bits

    long long A = mask ^ C;
    long long B = C;

    // ensure product is maximized (swap if needed)
    if (A * B < B * A) swap(A, B);

    cout << A << " " << B << "\n";
    return 0;
}
