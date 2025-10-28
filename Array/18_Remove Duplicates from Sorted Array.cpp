class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int res = 0;
        for(int i=1; i<nums.size(); i++){
            if(nums[i] != nums[res]){
                res++;
                swap(nums[i], nums[res]);
            }
        }
        return res+1;
    }
};