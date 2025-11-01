class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>>map;
        for(auto x : strs){
            string str = x;
            sort(str.begin(),str.end());
            map[str].push_back(x);
        }

        vector<vector<string>>res;
        for(auto itr = map.begin();itr!=map.end();itr++){
            res.push_back(itr->second);
        }
        return res;
    }
};