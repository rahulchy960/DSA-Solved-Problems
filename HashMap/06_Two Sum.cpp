class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int>map;
        vector<int>res;
        for(int i=0;i<nums.size();i++){
            if(map.find(target-nums[i]) != map.end()){
                res.push_back(map[target-nums[i]]);
                res.push_back(i);
                break;
            }
            map.insert({nums[i],i});
        }
        return res;
    }
};