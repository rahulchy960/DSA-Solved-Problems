class Solution {
public:
    int minJump(vector<int>& nums, int n) {
        if(n==1) return 0;
        int res = INT_MAX;
        for(int i=0;i<n-1;i++){
            if(i + nums[i] >= n-1){
                int subRes = minJump(nums, i+1);
                if(subRes != INT_MAX){
                    res = min(res, subRes+1);
                }
            }
        }
        return res;
    }
    int jump(vector<int>& nums, int idx = 0) {
        return minJump(nums, nums.size());
    }
};

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        vector<int>dp(n, INT_MAX);
        dp[0] = 0;
        for(int i=1;i<n;i++){
            for(int j=0;j<i;j++){
                if(j + nums[j] >= i){
                    if(dp[j] != INT_MAX)
                        dp[i] = min(dp[i], dp[j]+1);
                }
            }
        }
        return dp[n-1];
    }
};

/*
==================== REVISION BLOCK ====================

Problem (Jump Game II — Minimum Jumps):
- You start at index 0. From index i, you can jump forward up to nums[i] steps.
- Find the minimum number of jumps needed to reach the last index (n-1).
- If unreachable, conceptually the answer is “infinite” (this code returns INT_MAX).

Pattern:
- Divide & Conquer (Top-down recursion over the “last jump” position).

Core Intuition:
- To reach index (n-1), the LAST jump must start from some index i where i + nums[i] ≥ n-1.
- So answer(n) = 1 + min over all such i of answer(i+1), where answer(k) = min jumps to reach index (k-1).
- Base: answer(1) = 0 (already at start).

Algorithm (this implementation):
1) Base: if n == 1, return 0 (0 jumps needed when subarray length is 1).
2) Initialize res = INT_MAX (best answer so far for length n).
3) For i from 0 to n-2:
   - If i + nums[i] ≥ n-1 (i can jump to the end in one hop),
     recursively compute subRes = minJump(nums, i+1) (min jumps to reach index i).
   - If subRes is valid (≠ INT_MAX), update res = min(res, subRes + 1).
4) Return res.

Correctness (sketch):
- Completeness: The loop tries every feasible last-jump anchor i that can reach the end.
- Optimality: Taking the minimum over all anchors ensures the minimal jump count is chosen.
- Base case anchors the recursion at the start (length 1 → 0 jumps).

Complexity (of THIS recursive approach):
- Time: Exponential in worst case (≈ O(2^n)).
  Reason: Overlapping subproblems (same prefixes i+1 are recomputed many times).
  A rough recurrence: T(n) ≈ Σ T(i) for i = 1..n-1 ⇒ T(n) = O(2^n) (plus O(n) loop per level).
- Space: O(n) recursion depth in the worst case (call stack).

Edge Cases:
- n == 1 → 0.
- Large blocks of zeros: many prefixes become unreachable; code returns INT_MAX.
- Safe add: The code checks subRes != INT_MAX before subRes + 1, avoiding overflow.

Dry Run (nums = [2,3,1,1,4]):
- n=5: candidates i s.t. i+nums[i] ≥ 4 → i=1 (1+3=4), i=2 (2+1=3<4 no), i=3 (3+1=4), i=0 (0+2=2<4 no)
- Try i=1: res ← min(res, minJump(n=2)+1) = min(∞, 1) after recursion finds 0 for n=2, etc.
- Eventually res = 2 (0→1→4).

Better Approaches (not implemented here):
- Memoized DP (top-down): O(n^2) time, O(n) space.
- Bottom-up DP: O(n^2) time, O(n) space.
- Greedy (classic optimal): O(n) time, O(1) space:
  Maintain current range [start..end] you can reach with “jumps” jumps and extend to the farthest index; when i reaches end, increment jumps and set new end=farthest.

========================================================
*/

class Solution {
public:
    // Returns the minimum jumps to reach index (n-1) from start (index 0)
    // for the prefix nums[0..n-1]. If unreachable, returns INT_MAX.
    int minJump(vector<int>& nums, int n) {
        if (n == 1) return 0;                   // Base: already at start → 0 jumps

        int res = INT_MAX;                      // Best (minimum) jumps for length n

        // Try every index i as the LAST jump anchor to reach (n-1)
        for (int i = 0; i < n - 1; i++) {
            // If from i we can jump to (or past) the last index of this prefix
            if (i + nums[i] >= n - 1) {
                // Recurse: min jumps to reach i (i.e., prefix length i+1)
                int subRes = minJump(nums, i + 1);

                // Only update if prefix i is reachable
                if (subRes != INT_MAX) {
                    res = std::min(res, subRes + 1);  // +1 for the final jump i → (n-1)
                }
            }
        }
        return res;                             // May be INT_MAX if unreachable
    }

    // LeetCode-style wrapper: returns min jumps to reach the last index.
    int jump(vector<int>& nums, int idx = 0) {
        (void)idx; // idx not used in this version; kept to preserve your signature.
        return minJump(nums, nums.size());
    }
};


/*
==================== REVISION BLOCK ====================

Problem (Jump Game II — Minimum Jumps):
- You start at index 0. From index i you can jump forward up to nums[i] steps.
- Find the minimum number of jumps needed to reach index n-1. (If unreachable, think “infinite”.)

Pattern:
- Dynamic Programming (bottom-up). Equivalent to shortest-path on a DAG of forward edges.

State & Meaning:
- dp[i] = minimum jumps needed to reach index i from index 0.
- Answer = dp[n-1].

Intuition:
- To reach i, you must come from some j < i that can jump to i (i.e., j + nums[j] ≥ i).
- Pick the best such j with the fewest jumps so far and add 1 for the jump j → i.

Algorithm (this code):
1) Let n = nums.size(); initialize dp[0] = 0 and dp[i] = +∞ (INT_MAX) for i > 0.
2) For i = 1..n-1:
     For j = 0..i-1:
       If j + nums[j] ≥ i (j can reach i) and dp[j] != +∞:
          dp[i] = min(dp[i], dp[j] + 1).
3) Return dp[n-1].

Correctness (sketch):
- dp[0]=0 is correct.
- For each i, we consider *all* valid predecessors j able to reach i and take the minimum,
  so dp[i] is the optimal (fewest) jumps to i by induction on increasing i.

Complexity:
- Time: O(n^2) due to the nested loops over (i, j).
- Space: O(n) for the dp array.

Edge Cases:
- n == 1 → 0 (already at the last index).
- Zeros inside nums: allowed; positions beyond an unreachable zero remain INT_MAX.
- Avoid overflow: Only do dp[j] + 1 after confirming dp[j] != INT_MAX (handled in code).

Dry Run (nums = [2,3,1,1,4]):
- dp = [0, ∞, ∞, ∞, ∞]
  i=1: j=0 (0+2≥1) → dp[1]=min(∞,0+1)=1
  i=2: j=0 (0+2≥2) → dp[2]=1; j=1 also reaches 2 → dp[2]=min(1,1+1)=1
  i=3: j=1 (1+3≥3) → dp[3]=dp[1]+1=2
  i=4: j=1 (1+3≥4) → dp[4]=dp[1]+1=2  (answer=2)

Note:
- A classic greedy solution achieves O(n) time and O(1) space by expanding the farthest
  reachable range per jump (BFS-by-level idea). This DP is simpler to reason about but slower.

========================================================
*/

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        std::vector<int> dp(n, INT_MAX);
        dp[0] = 0; // 0 jumps needed to be at the start

        for (int i = 1; i < n; i++) {
            for (int j = 0; j < i; j++) {
                // Can j reach i in one jump?
                if (j + nums[j] >= i) {
                    // Only use j if it's reachable itself
                    if (dp[j] != INT_MAX) {
                        dp[i] = std::min(dp[i], dp[j] + 1);
                    }
                }
            }
        }
        return dp[n - 1]; // If INT_MAX, end is unreachable under given constraints
    }
};
