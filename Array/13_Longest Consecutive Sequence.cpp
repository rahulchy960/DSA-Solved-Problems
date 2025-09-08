class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        if(nums.size() == 0) return 0;
        unordered_set<int>set(nums.begin(), nums.end());
        int res = 1;
        for(auto s : set){
            if(set.find(s-1) == set.end()){
                int curr = 1;
                while(!set.empty() && set.find(s+curr)!=set.end())
                    curr++;
                res = max(res, curr);
            }
        }
        return res;
    }
};