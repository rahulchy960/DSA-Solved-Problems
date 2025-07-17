class Solution {
public:
    vector<vector<int>>res;
    void helper(vector<int>&nums, vector<int>curr, int k, int n, int idx=0){
        if(curr.size()>k || n<0)
            return;
        if(curr.size()==k && n==0){
            res.push_back(curr);
            return;
        }
        for(int i=idx;i<nums.size();i++){
            curr.push_back(nums[i]);
            helper(nums, curr, k, n-nums[i], i+1);
            curr.pop_back();
        }
        
    }
    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int>nums(9);
        for(int i=0;i<9;i++){
            nums[i] = i+1;
        }
        vector<int>curr;
        helper(nums, curr, k, n);
        return res;
    }
};


class Solution {
public:
    vector<vector<int>> res;

    /*
    Algorithm:
    - We are asked to find all possible combinations of `k` numbers from 1 to 9 that sum to `n`.
    - The numbers must be unique and cannot be reused, so we use backtracking starting from index `i+1` in recursion.
    - At each recursive step:
        - If the current combination exceeds size `k` or the remaining sum `n` becomes negative → backtrack.
        - If the combination size is `k` and the sum becomes exactly 0 → store the result.
        - Otherwise, continue adding next elements from `nums[i+1..8]`.

    Time Complexity:
    - O(C(9, k)) since we are choosing k unique numbers from 9
    - For each valid combination, we perform O(k) work to copy it → total complexity is O(C(9, k) * k)

    Space Complexity:
    - O(k) for the recursion stack (depth limited to k)
    - O(C(9, k) * k) for storing all valid combinations in the result vector
    */

    void helper(vector<int>& nums, vector<int> curr, int k, int n, int idx = 0) {
        // Base case: invalid path
        if (curr.size() > k || n < 0)
            return;

        // Valid combination found
        if (curr.size() == k && n == 0) {
            res.push_back(curr);
            return;
        }

        // Try each number from idx onwards
        for (int i = idx; i < nums.size(); i++) {
            curr.push_back(nums[i]);
            helper(nums, curr, k, n - nums[i], i + 1); // move to next index to avoid reuse
            curr.pop_back(); // backtrack
        }
    }

    vector<vector<int>> combinationSum3(int k, int n) {
        vector<int> nums(9);
        for (int i = 0; i < 9; i++) {
            nums[i] = i + 1; // Fill numbers 1 to 9
        }
        vector<int> curr;
        helper(nums, curr, k, n);
        return res;
    }
};
