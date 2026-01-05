class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int low = 0;
        int high = nums.size()-1;
        vector<int>ans = {-1, -1};
        while(low <= high){
            int mid = low + (high - low)/2;
            if(nums[mid] < target)
                low = mid + 1;
            else if(nums[mid] > target)
                high = mid - 1;
            else {
                if(mid == 0 || nums[mid] != nums[mid-1]){
                    ans[0] = mid;
                    break;
                } 
                else
                    high = mid - 1;
            }
        }

        low = 0;
        high = nums.size()-1;
        while(low <= high){
            int mid = low + (high - low)/2;
            if(nums[mid] < target)
                low = mid + 1;
            else if(nums[mid] > target)
                high = mid - 1;
            else {
                if(mid == (nums.size() - 1) || nums[mid] != nums[mid+1]){
                    ans[1] = mid;
                    break;
                }
                else
                    low = mid + 1;
            }
        }

        return ans;
    }
};