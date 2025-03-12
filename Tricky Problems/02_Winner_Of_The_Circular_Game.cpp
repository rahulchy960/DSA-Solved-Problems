// This is the Josephus problem solution iteratively -> leetcode 1823
// where the peoples are sitting in a circle and are numbered from 1 to n


int findTheWinner(int n, int k) {
    int ans = 0;  // base  
    int i=1;
    while(i<=n){ // n rounds for n peoples
        ans = (ans+k) % i; // in each round the kth person killed and the gun shifted by k AND %i to maintain the range in every iteration
        i++;
    }
    return ans+1;  // as sitting number 1 to n, so the ans shifted by one
}