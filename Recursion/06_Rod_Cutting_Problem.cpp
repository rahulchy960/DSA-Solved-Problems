// Given a rope of length N meters, and the rope can be cut in only 3 sizes A, B and C. 
// The task is to maximizes the number of cuts in rope. 
// If it is impossible to make cut then print the number else return -1

#include<bits/stdc++.h>
using namespace std;

int maxCuts(int n, int a, int b, int c){  // time -> O(3^n)  Aux -> O(n)
    if(n<0) return -1;    // If length becomes negative, return -1 (invalid case)
    if(n==0) return 0;    //  If length is zero, no more cuts can be made
    int res = max(max(maxCuts(n-a,a,b,c),maxCuts(n-b, a, b, c)), maxCuts(n-c, a, b, c));  // Recursively try cutting the rod by lengths `a`, `b`, and `c` 
                                                                                          // and take maximum of cuts
    if(res==-1)return -1;   // If no valid cuts are found, return -1
    return res+1;           // If a valid cut is made, increment the result count
}

int main(){
    int n = 7;
    int a = 2;
    int b = 2;
    int c = 2;
    cout<<maxCuts(n, a, b, c)<<endl;    
}