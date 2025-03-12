#include<bits/stdc++.h>
using namespace std;

int Josephus(int n, int k){  // people sitting in a circle and are numbered from 0 to n-1
    if(n==1) return 0;
     
    return (Josephus(n-1, k) + k) % n;  // at every stemps one person should kill so we do Josephus(n-1, k)
                                        // after every kill the gun handover to the next person so shifted by k so we do Josephus(n-1, k) + k)
                                        // the range must be in between 0 to n so we do (Josephus(n-1, k) + k) % n

}

int main(){
    int n = 8;
    int k = 2;
    cout<<Josephus(n, k)<<endl;   
}