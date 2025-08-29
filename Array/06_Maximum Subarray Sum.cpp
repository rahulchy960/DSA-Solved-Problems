class Solution {
  public:
    int maxSubarraySum(vector<int> &arr) {
        // Code here
        int res = INT_MIN;
        int sum = 0;
        for(int i=0;i<arr.size();i++){
            sum+=arr[i];
            res = max(res, sum);
            if(sum<0)
                sum = 0;
        }
        return res;
    }
};