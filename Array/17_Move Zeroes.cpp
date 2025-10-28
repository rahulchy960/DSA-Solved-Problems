class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int res = 0;
        for(int i=0;i<nums.size();i++){
            if(nums[i] != 0){
                swap(nums[res],nums[i]);
                res++;
            }
        }
    }
};