// Tail Recursion: A recursive function is said to be following Tail Recursion if 
// it invokes itself at the end of the function. That is, if all of the statements 
// are executed before the function invokes itself then it is said to be following 
// Tail Recursion.

#include<iostream>
using namespace std;

void printNToOne(int n){   // print N to 1 
    start:
        if(n==0)return;
        cout<<n<<" ";
        n = n-1;
    goto start;
}

int factorial(int n, int k=1){   // factorial
    start:
    if(n==0)return k;
    k = k*n;
    n = n-1;
    goto start;
}

int nCr(int n,int r){   // calculation of nCr

    if(r==0 || r==n)return 1;
    return nCr(n-1, r-1) + nCr(n-1, r);
}

int sumOfN(int n, int sum=0){  // sum of natural numbers
    start:
    if(n==0) return sum;
    sum += n;
    n = n-1;
    goto start;
}

int GCD(int a,int b){  // calculate GCD of two numbers

    if(a==b)return a;
    if(a>b) GCD(a-b,b);
    else GCD(b-a, a);
}

#include<bits/stdc++.h>
using namespace std;
int main(){

    printNToOne(10); 
    cout<<endl;

    cout<<factorial(5)<<endl;  

    cout<<sumOfN(10)<<endl;
}