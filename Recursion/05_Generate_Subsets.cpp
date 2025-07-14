#include<bits/stdc++.h>
using namespace std;

void generateSubset(string str, int level = 0, string curr = ""){  
    if(level == str.length()){   
        cout<<curr<<endl;
        return;
    }                                               
    generateSubset(str, level+1, curr);             
    generateSubset(str, level+1, curr+str[level]);  
}

int main(){
    string str = "ABCD";
    generateSubset(str);    // Time complexity = O(2^n)  Aux Space = O(len(str))
}



// Algorithm: Generate all subsets of a string using recursion
// -----------------------------------------------
// Problem:
//   - Given a string, generate all possible subsets (the power set).
//   - Each character can either be included or excluded in a subset.
//
// Approach:
//   - Use recursion to explore two choices at each index (level):
//       1. Exclude the current character
//       2. Include the current character
//   - Base case: when `level == str.length()`, print the subset
//
// Time Complexity: O(2^n)
//   - At each character, we make two recursive calls (include/exclude).
//   - For string of length n, total 2^n subsets are generated.
//
// Auxiliary Space: O(n)
//   - Recursion stack depth is at most n (length of string)

void generateSubset(string str, int level = 0, string curr = "") {
    // Base case: all characters considered
    if (level == str.length()) {
        cout << curr << endl;
        return;
    }

    // Recursive case 1: Exclude current character
    generateSubset(str, level + 1, curr);

    // Recursive case 2: Include current character
    generateSubset(str, level + 1, curr + str[level]);
}


