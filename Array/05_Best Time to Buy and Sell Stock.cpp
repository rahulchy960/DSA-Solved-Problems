class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int maxDiff = 0;
        int mini = prices[0];
        for(int i=1;i<prices.size();i++){
            maxDiff = max(maxDiff, prices[i] - mini);
            mini = min(mini, prices[i]);
        }
        return maxDiff;
    }
};