class Solution {
public:
    bool wordPattern(string pattern, string s) {
        unordered_map<string, char>map1;
        unordered_map<char, string>map2;
        stringstream ss(s);
        string word;
        int idx=0;
        while(ss >> word){

            if(idx >= pattern.length())
                return false;
            char c = pattern[idx];
            if(map1.count(word) && map2[c] != word)  // cant use find because thats a pointer so have to use count 
                return false;
            if(map2.count(c) && map1[word] != c)
                return false;

            map1[word] = c;
            map2[c] = word;

            idx++;
        }

        return idx == pattern.size();

    }
};