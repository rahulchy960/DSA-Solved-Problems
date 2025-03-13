#include<bits/stdc++.h>
using namespace std;

int LCS(string &s1, string &s2, int m, int n){

    if(m==0 || n==0)return 0; // base case: if any of the string become 0;

    if(s1[m-1] == s2[n-1])    // if we find a match in both string
        return 1 + LCS(s1,s2,m-1,n-1); // we recursively call for the remaining part of the strings
    else 
        return max(LCS(s1,s2,m-1,n), LCS(s1,s2,m,n-1)); // we reccur for two cases, In one case we ignore the last char
                                                        // of the first string and other case we remove the last char of
                                                        // 2nd string And take max of both the LCS
}

int main(){
    string s1 = "AGGTAB";
    string s2 = "GXTXAYB";
    int m = s1.length();
    int n = s2.length();
    cout<<LCS(s1,s2,m,n)<<endl;    
}
