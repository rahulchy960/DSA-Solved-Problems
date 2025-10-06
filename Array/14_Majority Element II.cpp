class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        unordered_map<int, int>map;
        vector<int>res;

        for(int i=0;i<nums.size();i++){
            map[nums[i]]++;
        }
        for(auto m : map){
            if(m.second > nums.size()/3)
                res.push_back(m.first);
        }
        return res;
    }
};

