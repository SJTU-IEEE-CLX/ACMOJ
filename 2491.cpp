#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int nthUglyNumber(int n) {
    if (n <= 0) return 0;
    priority_queue<long, vector<long>, greater<long>> pq;
    unordered_set<long> seen;
    vector<int> primes = {2, 3, 5};
    pq.push(1);
    seen.insert(1);
    long ugly = 1;
    
    for (int i = 1; i <= n; ++i) {
        ugly = pq.top();
        pq.pop();
        for (int prime : primes) {
            long next = ugly * prime;
            if (seen.find(next) == seen.end()) {
                pq.push(next);
                seen.insert(next);
            }
        }
    }
    
    return ugly;
}

int main() {
    int n;
    cin >> n;
    cout << nthUglyNumber(n) << endl;
    return 0;
}