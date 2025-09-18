class Solution {
public:
    int helper(vector<int> nums){
        int n = nums.size();
        vector<int>dp(n, 0);
        dp[0] = nums[0];
        dp[1] = max(nums[0],nums[1]);
        for(int i=2; i<n; i++){
            int looted = nums[i] + dp[i-2];
            int notLooted = dp[i-1];
            dp[i] = max(looted, notLooted);
        }
        return dp[n-1];

    }
    int rob(vector<int>& nums) {
        if(nums.size() == 1) return nums[0];
        if(nums.size() == 2) return max(nums[0], nums[1]);
        int n = nums.size();
        return max(
            helper(vector<int>(nums.begin(), nums.end()-1)),
            helper(vector<int>(nums.begin()+1, nums.end()))
        );
        // if we pick the nums[0] we cant pick nums[n-1] and
        // if we pick nums[n-1] we cant pick nums[0]
    }
};