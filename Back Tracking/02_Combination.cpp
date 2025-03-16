#include<bits/stdc++.h>
using namespace std;
vector<vector<int>>res;


void helper(int n, int k, vector<int>&arr, vector<int>&temp, int i=0){
    if(temp.size()==k){
        res.push_back(temp);
        return;
    }
    for(int j=i;j<n;j++){
        temp.push_back(arr[j]);
        helper(n, k, arr, temp, j+1);
        temp.pop_back();
    }
}

void Combinations(int n, int k){
    vector<int>arr(n);
    for(int i=0;i<n;i++)
        arr[i] = i+1;
    vector<int>temp;
    helper(n, k, arr, temp);
}

int main(){
    int n = 5;
    int k = 2;
    Combinations(n, k);
    for(auto x : res){
        for(int i=0;i<x.size();i++)
            cout<<x[i]<<" ";
        cout<<endl;
    }
}