class Solution {
public:
    int minPos(vector<int>& nums){
        int pos = -1;
        int mini = INT_MAX;
        for(int i=0;i<nums.size()-1;i++){
            if(nums[i] + nums[i+1] < mini){
                mini = nums[i] + nums[i+1];
                pos = i;
            }
        }
        return pos;
    }
    int minimumPairRemoval(vector<int>& nums) {
        int ops = 0;
        while(!is_sorted(nums.begin(), nums.end())){
            int pos = minPos(nums);
            nums[pos] = nums[pos] + nums[pos+1];
            nums.erase(nums.begin() + pos + 1);
            ops++;
        }

        return ops;
    }
};




/*
==================== REVISION BLOCK — (Likely) LeetCode: Minimum Pair Removal to Sort Array (Greedy Simulation) ====================

Problem
-------
Given an array nums, repeatedly choose an adjacent pair (i, i+1), replace nums[i]
with nums[i] + nums[i+1], and remove nums[i+1] (i.e., merge the pair into one element).
Count the minimum number of such operations needed to make the array non-decreasing
(sorted in ascending order).

Note: The exact platform/name may vary; your code matches a “merge adjacent pair until sorted”
style problem.

Pattern/ Idea
-------------
Greedy + Simulation.
Your idea:
- While the array is not sorted, pick the adjacent pair with the minimum sum,
  merge it, and count one operation.
- Repeat until the array becomes sorted.

Algorithm (step-by-step)
------------------------
Helper minPos(nums):
1) Initialize pos = -1, mini = +INF
2) For i from 0 to n-2:
   - If nums[i] + nums[i+1] < mini:
       mini = nums[i] + nums[i+1]
       pos = i
3) Return pos (index of left element of minimum-sum adjacent pair)

Main minimumPairRemoval1(nums):
1) ops = 0
2) While nums is not sorted:
   a) pos = minPos(nums)
   b) nums[pos] = nums[pos] + nums[pos+1]   (merge pair)
   c) erase nums[pos+1]                     (remove second element)
   d) ops++
3) Return ops

Correctness (sketch)
--------------------
This code correctly simulates the operation sequence you chose (minimum-sum adjacent merges)
and stops only when the array becomes non-decreasing.

Important: This is a *valid algorithm*, but it is not proven here that choosing the minimum-sum
pair at each step always yields the *minimum possible* number of operations. Greedy choice needs
a proof or counterexample check depending on the original problem statement.

Complexity
---------
Let n be initial length.
- Each iteration does:
  - is_sorted: O(n) check
  - minPos scan: O(n)
  - erase from vector: O(n) shift
So each op is O(n), and there can be up to (n-1) ops.
Total worst-case time: O(n^2)
Space: O(1) extra (in-place), ignoring vector internal reallocations

Edge Cases / Pitfalls
---------------------
- nums.size() <= 1: already sorted, loop never runs, returns 0 (fine).
- Potential integer overflow if nums values are large and summed repeatedly (use long long if needed).
- This greedy may fail to be optimal if the actual task asks for *minimum* operations globally.
- erase() inside loop is costly; can TLE for big constraints.

Optimization if needed
----------------------
- Use long long for sums if constraints allow large values.
- Avoid O(n) erase by using a linked structure (list) or a “next pointer” array simulation.
- If the original problem truly requires minimum operations, look for:
  - DP, monotonic stack, or priority queue + union-find style merging (depends on constraints).
  - A proof-backed greedy (not just minimum-sum pair).

========================================================
*/
