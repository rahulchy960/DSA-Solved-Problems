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
    if(n==1)return k;
    k = k*n;
    n = n-1;
    goto start;
}

int sumOfN(int n, int sum=0){   // // sum of natural numbers
    start:
    if(n==0) return sum;
    sum += n;
    n = n-1;
    goto start;
}

#include<bits/stdc++.h>
using namespace std;
int main(){

    printNToOne(10); 
    cout<<endl;

    cout<<factorial(5)<<endl;  

    cout<<sumOfN(10)<<endl;
}