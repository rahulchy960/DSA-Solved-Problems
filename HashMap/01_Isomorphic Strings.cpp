class Solution {
public:
    bool isIsomorphic(string s, string t) {
        unordered_map<char, int> map1, map2;
        for(int i=0;i<s.length();i++){
            if(map1.find(s[i]) == map1.end()){
                map1.insert({s[i], i});
            } 
            if(map2.find(t[i]) == map2.end()){
                map2.insert({t[i], i});
            } 
            if(map1[s[i]] != map2[t[i]])
                return false;
            
        }
        return true;
    } 
};