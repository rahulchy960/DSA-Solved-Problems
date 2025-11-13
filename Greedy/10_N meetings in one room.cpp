bool myCmp(pair<int, int>&p1, pair<int,int>&p2){
        if(p1.second == p2.second)
            return p1.first < p2.first;
        return p1.second < p2.second;
}

class Solution {
  public:
    // Function to find the maximum number of meetings that can
    // be performed in a meeting room.
    int maxMeetings(vector<int>& start, vector<int>& end) {
        // Your code here
        vector<pair<int,int>>meet;
        for(int i=0;i<start.size();i++){
            meet.push_back({start[i], end[i]});
        }
        
        sort(meet.begin(), meet.end(), myCmp);
        int j = 0;
        int count = 1;
        for(int i=1;i<meet.size();i++){
            if(meet[j].second < meet[i].first){
                count++;
                j = i;
            }
        }
        
        return count;
    }
};