#include<bits/stdc++.h>
using namespace std;

void generateSubset(string str, int level = 0, string curr = ""){  // the level defined the recursion tree level
    if(level == str.length()){   // when level become len of the given string, means all characters are included 
        cout<<curr<<endl;
        return;
    }                                               // in each level 
    generateSubset(str, level+1, curr);             // dont include the character
    generateSubset(str, level+1, curr+str[level]);  // include the character
}

int main(){
    string str = "ABCD";
    generateSubset(str);    // Time complexity = O(2^n)  Aux Space = O(len(str))
}

