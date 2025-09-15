class Solution {
  public:
    static bool myCmp(const pair<int, int>&p1, const pair<int,int>&p2){
        return p1.second < p2.second ;
    }
    int activitySelection(vector<int> &start, vector<int> &finish) {
        // code here
        vector<pair<int, int>>activity;
        for(int i=0;i<start.size();i++)
            activity.push_back({start[i], finish[i]});
        sort(activity.begin(), activity.end(), myCmp);
        int count = 1;
        int prev = 0;
        for(int i=1;i<activity.size();i++){
            if(activity[i].first > activity[prev].second){
                count++;
                prev = i;
            }
        }
        return count;
    }
};