#include<bits/stdc++.h>
using namespace std;

void addEdge(int u, int v, vector<vector<bool>> &mat){
    mat[u][v] = 1;
    mat[v][u] = 1; // for undirected graph 
}

void printGraph(const vector<vector<bool>> &mat){
    for(int u=0;u<mat.size();u++){
        for(int v=0;v<mat[0].size();v++){
            cout<<mat[u][v]<<" ";
        }
        cout<<endl;
    }
}

int main(){
    int u = 4;
    int v = 4;
    vector<vector<bool>>mat(u, vector<bool>(v, 0));
    addEdge(0,1,mat);
    addEdge(0,2,mat);
    addEdge(1,2,mat);
    addEdge(2,3,mat);
    printGraph(mat);

}