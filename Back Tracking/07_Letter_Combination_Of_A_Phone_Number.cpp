#include<bits/stdc++.h>
using namespace std;
vector<string>res;
vector<string>phone = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

void phoneKeypad(string digits, string curr=""){
    if(curr.length()==digits.length()){
        res.push_back(curr);
        return;
    }
    for(int i=0;i<digits.length();i++){
        
    }
}

int main(){
    string digits = "23";
    phoneKeypad(digits);
}