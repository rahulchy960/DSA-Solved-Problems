class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int>set;
        while( n != 1){
            int num = n;
            int sum = 0;

            while(num){
                sum += (num%10) * (num%10);
                num/=10;
            }

            if(set.find(sum) != set.end())
                return false;

            set.insert(sum);
            n = sum;
        }
        return true;
    }
};