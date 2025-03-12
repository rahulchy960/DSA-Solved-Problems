#include<bits/stdc++.h>
using namespace std;

int steps = 0;

int towerOfHonoi(int n, char src, char aux, char target){
    steps++;
    if(n==1){
        cout<<"Move Disk "<<n<<" From "<<src<<" to "<<target<<endl;
        return steps;
    }
    towerOfHonoi(n-1, src, target, aux); // recursively move top n-1 disks from A to B using C as auxilary
    cout<<"Move Disk "<<n<<" From "<<src<<" to "<<target<<endl; // move the buttom disk (nth disk) from A to C
    towerOfHonoi(n-1, aux, src, target);  // then again we recursively move the n-1 disks from B to C using A as auxilary

}

int main(){
    int n = 3;
    char src = 'A';
    char aux = 'B';
    char target = 'C';
    cout<<towerOfHonoi(3, src, aux, target);    
}