class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int fCount = 0, tCount = 0;
        for(int i=0;i<bills.size();i++){
            if(bills[i] == 5){
                fCount++;
            }
            else if(bills[i] == 10){
                tCount++;
                fCount--;
            }
            else{
                if(tCount == 0){
                    fCount -= 3;
                } else {
                    tCount--;
                    fCount--;
                }
            }

            if(fCount<0 || tCount<0)
                return false;
        }

        return true;
    }
};