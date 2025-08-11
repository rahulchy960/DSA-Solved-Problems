
bool canJump(vector<int>& nums) {
        int n = nums.size();
        int jump = n-1;
        for(int i=n-2;i>=0;i--){
            if( i + nums[i] >= jump)
                jump = min(jump, i);
        }
        return (jump == 0) ? true : false;
    }


/*
==================== REVISION BLOCK ====================

Problem (Jump Game — super clear):
- You start at index 0 of an array nums.
- At index i, nums[i] tells you the *maximum* steps you can jump forward.
- From i, you may move to any j such that i < j <= i + nums[i].
- Question: Can you reach the last index (n-1)? Return true/false.

Tiny examples:
- [2,3,1,1,4] → true (0→1→4)
- [3,2,1,0,4] → false (you get stuck at index 3 because nums[3]=0)

Pattern:
- Greedy (scan from right to left). Track the leftmost index that can reach the end.

Algorithm:
1) Set goal = n-1 (last index).
2) For i from n-2 down to 0:
   - If i + nums[i] >= goal, set goal = i (i can reach the current goal).
3) Return (goal == 0).

Why it works (invariant):
- “goal” is always the leftmost index known to reach the end.
- When i can reach goal, i also reaches the end, so move goal left to i.

Complexity:
- Time: O(n) — single backward pass.
- Space: O(1) — only the goal index stored.

Edge notes:
- n == 1 is trivially true (already at the last index).
- Zeros only matter if they appear before the current goal and block reaching it.

========================================================
*/

bool canJump(vector<int>& nums) {
    // Greedy: track the leftmost index that can reach the end.
    int n = nums.size();
    int jump = n - 1;                 // 'jump' = current goal index

    for (int i = n - 2; i >= 0; i--) {
        if (i + nums[i] >= jump)
            jump = min(jump, i);      // same as: jump = i; (kept your exact logic)
    }
    return (jump == 0);
}
