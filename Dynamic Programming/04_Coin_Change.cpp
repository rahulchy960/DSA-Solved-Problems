/*  Recursive Solution

int helper(vector<int>& coins, int amount, int n, vector<int>curr){
        if(amount==0) return curr.size();
        if(n==0) return INT_MAX;

        int case1 = helper(coins, amount, n-1, curr);
        
        int case2 = INT_MAX;
        if(amount>=coins[n-1]){
            curr.push_back(coins[n-1]);
            case2 = helper(coins, amount-coins[n-1], n, curr);
        }
        return min(case1, case2);
    }
    int coinChange(vector<int>& coins, int amount) {
        vector<int>curr;
        int res = helper(coins, amount, coins.size(), curr);
        if(res==INT_MAX)return -1;
        return res;
    }

*/
