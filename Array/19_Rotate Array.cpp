void reverse(vector<int>&nums, int left, int right){
    while(left<=right){
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
        left++;
        right--;
    }
}
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        if(n==1)return ;
        if(n<=k)k = k%n;
        reverse(nums,0,n-1-k);
        reverse(nums,n-k,n-1);
        reverse(nums,0,n-1);
    }
};