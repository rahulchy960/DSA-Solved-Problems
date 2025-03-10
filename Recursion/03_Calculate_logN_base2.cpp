#include<iostream>
using namespace std;

int logNbase2(int n){
    if(n==1)return 0;
    return 1 + logNbase2(n/2);
}

int main(){
    int n = 10;
    cout<<logNbase2(n);
}