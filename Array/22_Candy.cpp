class Solution {
public:
    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n == 1)
            return 1;
        vector<int>res(n, 1);

        for(int i=1;i<n;i++){
            if(ratings[i] > ratings[i-1])
                res[i] = res[i-1] + 1;
        }
        for(int i=n-1;i>0;i--){
            if(ratings[i-1] > ratings[i])
                res[i-1] = max(res[i] + 1, res[i-1]);
        }
       
        
        int sum = 0;
        for(auto x: res)
            sum += x;
        
        return sum;
    }
};

/*
==================== REVISION BLOCK — LeetCode 135: Candy ====================

Problem
-------
There are n children standing in a line, each with a rating.
You must give candies to children such that:
1) Each child has at least one candy.
2) Children with a higher rating than their immediate neighbors get more candies.
Return the minimum number of candies needed.

Pattern/ Idea
-------------
Greedy + Two-Pass (Left-to-Right, then Right-to-Left).
Key idea: 
- First pass ensures the condition with the left neighbor.
- Second pass fixes violations with the right neighbor while keeping candies minimal.

Algorithm (step-by-step)
------------------------
1) Initialize an array res of size n with all values = 1 (minimum one candy each).
2) Left-to-right pass (i = 1 to n-1):
   - If ratings[i] > ratings[i-1], then res[i] = res[i-1] + 1.
3) Right-to-left pass (i = n-1 down to 1):
   - If ratings[i-1] > ratings[i], then
     res[i-1] = max(res[i-1], res[i] + 1).
4) Sum all values in res and return the sum.

Correctness (sketch)
--------------------
- Initialization guarantees every child gets at least one candy.
- Left-to-right pass ensures: if a child has a higher rating than the left neighbor,
  they get more candies.
- Right-to-left pass ensures the same condition with the right neighbor, without
  breaking the left condition due to the max() check.
- After both passes, both neighbor constraints are satisfied with minimum candies.

Complexity
---------
Time: O(n)
Space: O(n)

Edge Cases / Pitfalls
---------------------
- n = 1 → answer is 1.
- Strictly increasing ratings → candies increase sequentially.
- Strictly decreasing ratings → fixed by right-to-left pass.
- Peaks/valleys → handled by combining both passes.

Optimization if needed
----------------------
Space can be optimized to O(1) using slope-counting, but the logic becomes more complex.
This solution is optimal and preferred in interviews for clarity.

========================================================
*/
