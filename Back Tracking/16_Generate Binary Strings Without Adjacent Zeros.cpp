class Solution {
public:
    void helper(vector<string>&res, int n, string str=""){
        if(str.length() >= 2){
            if(str[str.length()-1] == '0' && str[str.length()-2] == '0')
                return;
        }
        if(str.length() == n){
            res.push_back(str);
            return;
        }

        helper(res, n, str + "0");
        helper(res, n, str + "1");
    }
    vector<string> validStrings(int n) {
        vector<string>res;
        helper(res, n);
        return res;
    }
};