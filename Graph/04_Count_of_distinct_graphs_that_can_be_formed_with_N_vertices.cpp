/*
==================== REVISION BLOCK — Count of Labeled Undirected Graphs ====================

Problem
-------
Given n labeled vertices, how many **simple undirected graphs** (no self-loops, no multi-edges)
can be formed? Return the count modulo 1e9+7.

Key Idea
--------
Between any distinct pair of vertices there is **one possible undirected edge** that can be
either present or absent, independently of others.

- Number of possible edges = C(n, 2) = n*(n-1)/2
- Each edge has 2 choices (present/absent)
- Total graphs = 2^(C(n,2))

Algorithm
---------
1) Compute x = C(n,2) = n*(n-1)/2   // use 64-bit to avoid overflow
2) Compute pow_mod(2, x, MOD) using **binary exponentiation** (fast power).

Correctness (sketch)
--------------------
Every subset of the set of possible edges defines a unique simple undirected graph.
There are exactly 2^(|edges|) such subsets.

Complexity
----------
- Binary exponentiation runs in O(log x) multiplications.
- Here x = Θ(n^2), so time = O(log (n^2)) = O(log n).
- Space = O(1).

Pitfalls / Notes
----------------
- Cast to 64-bit before `n*(n-1)` to avoid 32-bit overflow for large n:
  `1LL * n * (n - 1) / 2`.
- This counts **labeled** graphs. Unlabeled (non-isomorphic) counts are different.
- Variants:
  * Directed (no self-loops): 2^(n*(n-1))
  * Allow self-loops (undirected): 2^(C(n,2) + n)

============================================================================================
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

// Fast exponentiation: returns (x^y) % MOD
long long power(long long x, long long y, int MOD){
    long long res = 1;
    while (y > 0) {
        if (y & 1) res = (res * x) % MOD; // include current base when bit is 1
        x = (x * x) % MOD;                // square base
        y >>= 1;                          // shift exponent
    }
    return res;
}

long long countGraphs(int n){
    long long x = 1LL * n * (n - 1) / 2; // C(n,2) in 64-bit
    return power(2, x, MOD);
}

int main(){
    int n = 1000;
    cout << countGraphs(n) << '\n'; // For n=3: C(3,2)=3 → 2^3 = 8
    return 0;
}
