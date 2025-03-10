#include<iostream>
using namespace std;

void to_binary(int n){
    if(n==0)return;
    to_binary(n/2);
    cout<<(n%2);
}

int main(){
    int n = 10;
    to_binary(n);
}