#include<bits/stdc++.h>
using namespace std;

void addEdge(int u, int v, int wt, vector<pair<int, int>> adj[]){
    adj[u].push_back(make_pair(v, wt));
    adj[v].push_back(make_pair(u, wt));
}

void printList(const vector<pair<int, int>> adj[], int u){
    for(int i=0;i<u;i++){
        for(auto x: adj[i]){
            cout<<i<<" -> "<<x.first<<" = "<<x.second<<"   ";
        }
        cout<<endl;
    }
}

int main(){
    int u=4;
    vector<pair<int, int>>adj[u];
    addEdge(0,1,10,adj);
    addEdge(0,2,20,adj);
    addEdge(1,2,30,adj);
    addEdge(2,3,40,adj);
    printList(adj,u);

}