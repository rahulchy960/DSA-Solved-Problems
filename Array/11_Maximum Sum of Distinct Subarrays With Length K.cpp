class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        unordered_map<long, long>map;
        long sum = 0;
        long res = 0;
        for(int i=0;i<k;i++){
            map[nums[i]]++;
            sum += nums[i];
        }
        if(map.size()==k) res = sum;

        for(int i=k;i<n;i++){
            sum += nums[i];
            sum -= nums[i-k];
            map[nums[i]]++;
            map[nums[i-k]]--;
            if(map[nums[i-k]] == 0)
                map.erase(nums[i-k]);   
            
            if(map.size() == k)
                res = max(res, sum);
        }

        return res;
        
    }
};