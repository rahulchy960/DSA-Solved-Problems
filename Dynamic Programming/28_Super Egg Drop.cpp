class Solution {
public:
    int superEggDrop(int k, int n) {
        if(n==0 || n==1)
            return n;
        if(k == 1)
            return n;
        int res = 0;
        int minMoves = INT_MAX;
        for(int floor=1; floor<=n; floor++){
            res = 1 + max(superEggDrop(k-1, floor-1), superEggDrop(k, n-floor));
            minMoves = min(minMoves, res);
        }

        return minMoves;
    }
};

/*
==================== REVISION BLOCK — Super Egg Drop (LeetCode 887) ====================

Problem
-------
Given k eggs and a building with n floors, find the minimum number of moves needed in the
worst case to determine the highest floor (threshold) from which an egg can be dropped
without breaking.

Pattern/ Idea
-------------
Minimax + Dynamic Programming.
- Your code does **pure recursion (try every floor)** and takes the worst-case of the two outcomes:
  egg breaks (search below) vs egg survives (search above), and then minimizes over all choices.
- Efficient patterns to fix TLE:
  1) **Top-down DP with memoization** (+ optional binary search due to convexity).
  2) **Moves-based DP**: Let `dp[m][k]` be the max floors solvable with `m` moves and `k` eggs.
     Then `dp[m][k] = dp[m-1][k-1] + dp[m-1][k] + 1`. Increase `m` until `dp[m][k] >= n`.

Algorithm (step-by-step)
------------------------
(As in your recursive solution)
1) Base cases:
   - If n == 0 or n == 1 → answer is n.
   - If k == 1 → must linearly scan → answer is n.
2) For each floor x from 1..n:
   - If egg breaks at x → solve (k-1, x-1).
   - If egg survives at x → solve (k, n-x).
   - Worst-case moves if we try x is 1 + max(break, survive).
3) Take the minimum over all x.

Correctness (sketch)
--------------------
For any chosen floor x, the worst-case moves must account for both outcomes; we add 1 for the drop at x
and take the larger subproblem to cover the worst case. Minimizing over x ensures we pick the floor
that yields the optimal worst-case strategy.

Complexity
----------
Your recursion:
- Time: Exponential O(n^k) (very large due to overlapping subproblems and trying all floors each time).
- Space: O(n) recursion depth (worst case).

Efficient alternatives:
- Memoized + binary search: ~ O(k * n * log n).
- Moves-based DP (recommended): O(k * M) where M is the minimal moves; in practice ~ O(k log n).

Edge Cases / Pitfalls
---------------------
- k == 1 or n <= 1 base cases.
- Large n causes TLE without memoization/DP.
- Stack depth for naive recursion can be high.
- Beware integer overflow if you ever use combinations in closed forms.

Optimization if needed
----------------------
- Add **memoization** to the top-down recursion; also apply **binary search** on floor due to convexity.
- Prefer the **moves-based DP**: increment moves m until `dp[m][k] >= n`; returns minimal m.
========================================================
*/

// -----------------------------
// Your code with line comments:
// -----------------------------
class Solution {
public:
    int superEggDrop(int k, int n) {
        // Base cases: if no floors or one floor, answer is n (0 or 1).
        if (n == 0 || n == 1)
            return n;

        // If only one egg, we have to try every floor from 1..n (linear scan).
        if (k == 1)
            return n;

        int res = 0;
        int minMoves = INT_MAX;

        // Try dropping from every floor 'floor' (1..n)
        for (int floor = 1; floor <= n; floor++) {
            // If egg breaks at 'floor': we must check floors below -> (k-1, floor-1)
            // If egg doesn't break: we must check floors above -> (k, n-floor)
            // We take worst-case between the two (minimax) and add 1 for the current drop.
            res = 1 + max(superEggDrop(k - 1, floor - 1),
                          superEggDrop(k, n - floor));

            // Track the minimum moves over all choices of 'floor'
            minMoves = min(minMoves, res);
        }

        return minMoves;
    }
};


// ---------------------------------------------------------
// (Optional) Faster alternative for your revision notes:
//
// Moves-based DP (recommended): O(k * minimal_moves), very fast in practice.
// ---------------------------------------------------------
//
// Idea:
// dp[m][e] = maximum number of floors we can check with m moves and e eggs.
// Recurrence:
//   dp[m][e] = dp[m-1][e-1] + dp[m-1][e] + 1
// Increase m until dp[m][k] >= n, then m is the answer.
//
// Uncomment and submit this version on LeetCode if you want the optimized solution.
//
// class Solution {
// public:
//     int superEggDrop(int k, int n) {
//         // dp for current moves; we only need 1D rolling array by eggs
//         vector<long long> dp(k+1, 0);
//         int moves = 0;
//         // Keep increasing moves until we can cover >= n floors
//         while (dp[k] < n) {
//             moves++;
//             // Update from high eggs to low eggs to reuse previous move's values
//             for (int e = k; e >= 1; --e) {
//                 // dp[e] (new) = dp[e-1] (prev) + dp[e] (prev) + 1
//                 dp[e] = dp[e-1] + dp[e] + 1;
//             }
//         }
//         return moves;
//     }
// };


class Solution {
public:
    int superEggDrop(int k, int n) {
        if(n==0 || n==1)
            return n;
        if(k == 1)
            return n;
        vector<vector<int>>dp(n+1, vector<int>(k+1, INT_MAX));
        for(int i=1;i<=n;i++)
            dp[i][1] = i;
        for(int j=1;j<=k;j++){
            dp[0][j] = 0;
            dp[1][j] = 1; 
        }
        for(int f=2; f<=n; f++){
            for(int e=2; e<=k; e++){
                for(int x=1; x<=f; x++){
                    int Break = dp[x-1][e-1];
                    int notBreak = dp[f-x][e];
                    int res = 1 + max(Break, notBreak);
                    dp[f][e] = min(dp[f][e], res);
                }
            }
        }
        return dp[n][k];
    }
};

/*
==================== REVISION BLOCK — Super Egg Drop (LeetCode 887) ====================

Problem
-------
Given k eggs and a building with n floors, return the minimum number of moves required
in the worst case to determine the highest floor from which an egg can be dropped without breaking.

Pattern/ Idea
-------------
Minimax Dynamic Programming on (floors, eggs).
- dp[f][e] = minimum moves needed with f floors and e eggs.
- Try dropping from every floor x and take the worst of the two outcomes:
  egg breaks (search below) vs egg survives (search above), then minimize over x.

Algorithm (step-by-step)
------------------------
1) Initialize a 2D table dp of size (n+1) x (k+1) with large values (INT_MAX).
2) Base cases:
   - With 0 floors: dp[0][e] = 0 (no move needed).
   - With 1 floor: dp[1][e] = 1 (one move).
   - With 1 egg:   dp[f][1] = f (linear scan from 1..f).
3) For floors f = 2..n:
     For eggs e = 2..k:
        For trial floor x = 1..f:
           breakCase    = dp[x-1][e-1]    // egg breaks, search below
           surviveCase  = dp[f-x][e]      // egg survives, search above
           worstIfDropX = 1 + max(breakCase, surviveCase)
           dp[f][e] = min(dp[f][e], worstIfDropX)
4) Answer is dp[n][k].

Correctness (sketch)
--------------------
For a chosen trial floor x, the adversarial/worst case must consider both outcomes:
breaking and surviving. Adding 1 for the current drop and taking max(break,survive)
ensures we cover the worst branch. Minimizing over x yields the optimal strategy.

Complexity
----------
Time: O(n^2 * k) due to the triple loop over floors f, eggs e, and trial floor x.
Space: O(n * k) for the dp table.

Edge Cases / Pitfalls
---------------------
- k == 1 (forces linear scan): dp[f][1] = f.
- n == 0 or n == 1 handled by base cases.
- Large n may be slow with O(n^2 * k); consider optimized versions.
- Watch for off-by-one when indexing floors (we use 0..n with meaningful states at 0 and 1).

Optimization if needed
----------------------
- Binary search over x is possible due to convexity (reduces inner loop).
- Best-in-practice: "Moves-based DP" where dp[m][e] = dp[m-1][e-1] + dp[m-1][e] + 1 and
  increment m until dp[m][k] >= n (typically O(k * minimal_moves)).
========================================================
*/

class Solution {
public:
    int superEggDrop(int k, int n) {
        // Handle trivial cases quickly
        if (n == 0 || n == 1) return n; // 0 floors -> 0 moves, 1 floor -> 1 move
        if (k == 1) return n;           // With 1 egg, we must try every floor (linear)

        // dp[f][e] = minimum moves needed with f floors and e eggs
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, INT_MAX));

        // Base cases:
        for (int f = 1; f <= n; ++f) dp[f][1] = f; // 1 egg: linear scan
        for (int e = 1; e <= k; ++e) {
            dp[0][e] = 0; // 0 floors -> 0 moves
            dp[1][e] = 1; // 1 floor  -> 1 move
        }

        // Fill DP for f >= 2 and e >= 2
        for (int f = 2; f <= n; ++f) {
            for (int e = 2; e <= k; ++e) {
                // Try every possible trial floor x
                for (int x = 1; x <= f; ++x) {
                    int Break    = dp[x - 1][e - 1]; // egg breaks -> search below x-1 floors with e-1 eggs
                    int NotBreak = dp[f - x][e];     // egg survives -> search above f - x floors with e eggs
                    int worst    = 1 + max(Break, NotBreak); // 1 move for current drop + worst of the two
                    dp[f][e] = min(dp[f][e], worst);         // minimize over x
                }
            }
        }

        return dp[n][k];
    }
};
