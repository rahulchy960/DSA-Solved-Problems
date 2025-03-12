#include<bits/stdc++.h>
using namespace std;

class Print{
    public:
        static int a;
        Print(){
            cout<<a++<<" ";
        }
};

int Print::a = 1; 

int main(){
    int n = 10;
    Print obj[n];
    return 0;
}