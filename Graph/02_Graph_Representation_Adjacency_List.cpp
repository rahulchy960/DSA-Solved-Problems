#include<bits/stdc++.h>
using namespace std;

void addEdge(int u, int v, vector<vector<int>> &list){
    list[u].push_back(v);
    list[v].push_back(u);
}

void printList(const vector<vector<int>> &list){
    for(auto u: list){
        for(auto v: u){
            cout<<v<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int u = 4;
    vector<vector<int>>list(u);
    addEdge(0,1,list);
    addEdge(0,2,list);
    addEdge(1,2,list);
    addEdge(2,3,list);
    printList(list);
}