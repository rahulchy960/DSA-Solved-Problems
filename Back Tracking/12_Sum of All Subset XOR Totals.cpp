class Solution {
public:
    void helper(vector<int>&nums, int &Xor, int &res, int level=0){
        if(nums.size() == level){
            res+=Xor;
            return;
        }
        int x = Xor^nums[level];
        helper(nums, x, res, level+1);
        helper(nums, Xor, res, level+1);

    }
    int subsetXORSum(vector<int>& nums) {
        int Xor = 0;
        int res=0;
        helper(nums, Xor, res);
        return res;
    }
};



// Algorithm: Subset XOR Sum (Backtracking)
// ----------------------------------------
// Problem:
//   - Given an array of integers, return the sum of XOR of all subsets.
//
// Approach:
//   - Use backtracking to explore all 2^n subsets.
//   - At each index (level):
//       1. Include nums[level] in the current XOR.
//       2. Exclude nums[level] from the current XOR.
//   - When a subset is complete (level == nums.size()), add the current XOR to the result.
//
// Time Complexity: O(2^n)
//   - Each element has 2 choices (include or exclude), total 2^n subsets.
//   - Each subset takes O(1) to calculate XOR (since we maintain it in recursion).
//
// Auxiliary Space: O(n) for recursion stack depth

class Solution {
public:
    // Recursive helper function to explore all subsets
    void helper(vector<int>& nums, int& Xor, int& res, int level = 0) {
        if (nums.size() == level) {
            res += Xor; // Base case: add XOR of current subset
            return;
        }

        // Include nums[level] in XOR
        int x = Xor ^ nums[level];
        helper(nums, x, res, level + 1);

        // Exclude nums[level] from XOR
        helper(nums, Xor, res, level + 1);
    }

    // Main function to initiate recursion
    int subsetXORSum(vector<int>& nums) {
        int Xor = 0;
        int res = 0;
        helper(nums, Xor, res);
        return res;
    }
};
