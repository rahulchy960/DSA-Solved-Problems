#include<iostream>
using namespace std;

void oneToN(int n){   // print 1 to n
    if(n==0)return;
    oneToN(n-1);
    cout<<n<<" ";
}

void NToOne(int n){   // print n to 1
    if(n==0)return;
    cout<<n<<" ";
    NToOne(n-1);
}

int sumOfN(int n){    // sum of natural number
    if(n==1)return 1;
    return n+sumOfN(n-1);
}

bool checkPalindrome(int arr[], int l, int r){   // check palindrome
    if(arr[l] != arr[r])return false;
    if(l>=r)return true;
    return checkPalindrome(arr, l+1, r-1);
}

int factorial(int n){  // factorial of a number
    if(n==0)return 1;
    return n*factorial(n-1);
}

int nthFibonacci(int n){  // calculate nth fibonacci 
    if(n==0 || n==1)return n;
    else return nthFibonacci(n-1) + nthFibonacci(n-2);
}

int sumOfDigits(int n, int sum=0){  // sum of digits
    if(n<=9){
        sum+=n;
        return sum;
    }
    sum += n%10;
    return sumOfDigits(n/10, sum);
}

int main(){

    oneToN(10);
    cout<<endl;

    NToOne(10);
    cout<<endl;

    cout<<sumOfN(10)<<endl;

    int arr[] = {1,2,2};
    int n = sizeof(arr)/sizeof(arr[0]);
    cout<<checkPalindrome(arr,0,n-1)<<endl;

    cout<<factorial(5)<<endl;

    cout<<nthFibonacci(10)<<endl;

    cout<<sumOfDigits(1359)<<endl;
}