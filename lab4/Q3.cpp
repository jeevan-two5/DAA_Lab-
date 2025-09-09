/*🔎 Intuition

We want to spam an emote triangle of size k:

Messages:
1, 2, 3, …, k, k-1, …, 2, 1

Total messages = 2k - 1.

The platform bans us as soon as the total number of emotes ≥ x.
We need to know: how many messages can we send before ban (including the last one that triggers the ban)?

🔹 Plan

Generate the sequence of emotes per message:

for i=1..k → i

for i=k-1..1 → i

Keep a running sum of emotes.

After each message, add count.

If running sum ≥ x, stop and return the number of messages.*/

//=========================================CODE================================================================

#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long k, x;
    cin >> k >> x;

    vector<long long> msgs;
    for (int i = 1; i <= k; i++) msgs.push_back(i);
    for (int i = k - 1; i >= 1; i--) msgs.push_back(i);

    long long sum = 0;
    int count = 0;

    for (long long val : msgs) {
        sum += val;
        count++;
        if (sum >= x) break;
    }

    cout << count << endl;
    return 0;
}
