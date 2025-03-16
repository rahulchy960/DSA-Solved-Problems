#include<bits/stdc++.h>
using namespace std;
vector<string>res;
vector<string>phone = {"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};

void phoneKeypad(string digits, string curr="", int i=0){
    // Base case: If the current combination length matches the input digits length
    if(curr.length()==digits.length()){
        res.push_back(curr);
        return;
    }
     // Get the current digit's corresponding string and length
    int len = phone[digits[i]-'0'].length();
    string letter = phone[digits[i]-'0'];

    // Loop through all possible characters for the current digit
    for(int j=0;j<len;j++){
        curr.push_back(letter[j]);  // Add the character to the current combination
        phoneKeypad(digits,curr,i+1);   // Recursive call for the next digit
        curr.pop_back();    // Backtrack to try other options
    }

    
}

int main(){
    string digits = "2";
    phoneKeypad(digits);
    for(auto x : res){
        cout<<x<<" ";
    }
}