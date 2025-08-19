#include<bits/stdc++.h>
using namespace std;
bool myCmp(pair<int,int>&p1, pair<int,int>&p2){
    if(p1.first == p2.first)
        return p1.second < p2.second;
    return p1.first < p2.first;
}
int buildingBridges(vector<pair<int,int>>&bridges){
    sort(bridges.begin(), bridges.end(), myCmp);
    int n = bridges.size();
    vector<int>lis(n,1);
    for(int i=1;i<n;i++){
        for(int j=0;j<i;j++){
            if(bridges[j].second < bridges[i].second)
                lis[i] = max(lis[i], lis[j]+1);
        }

    }
    return *max_element(lis.begin(), lis.end());
}

int main(){
    // vector<pair<int,int>> bridges = {{8, 1}, {1, 2}, {4, 3}, {3, 4}, {2,6},{6,7},{7,8},{5,5}};
    vector<pair<int,int>> bridges = {{6,2},{4,3},{2,6},{1,5},{1,3}};
    cout << "Maximum number of bridges = " 
             <<buildingBridges(bridges);    
    return 0;
}


/*
==================== REVISION BLOCK — Building Bridges (LIS on south) ====================

Problem
-------
You are given bridge endpoints as pairs (north, south). Build the maximum number of bridges
so that no two bridges cross. Two bridges (a,b) and (c,d) cross if:
    (a < c and b > d) OR (a > c and b < d).

This version treats **ties as allowed** (i.e., multiple bridges may share the same north or
the same south and still be considered non-crossing if the second coordinates are in
non-decreasing order after sorting by the first).

Pattern / Reduction
-------------------
1) **Sort** bridges by (north ASC, and on ties south ASC).
2) After sorting, the problem reduces to finding a **Longest Increasing Subsequence (LIS)**
   on the *south* coordinates. With this comparator, using **strict** LIS (`<`) on south
   gives the maximum count under the “ties allowed” interpretation for north.

Why this works (correctness sketch)
-----------------------------------
- Sorting by north ensures we only compare bridges in left-to-right order on the north bank.
- If we then select a subsequence whose south endpoints are **strictly increasing**, there are
  no inversions on south → no crossings.
- Conversely, any non-crossing selection in this order must have south endpoints in non-decreasing
  order; when souths are distinct it becomes strictly increasing, which the LIS finds.

Algorithm (this code, O(n^2))
-----------------------------
1) Sort bridges by (north ASC, south ASC).
2) Let lis[i] = length of the longest strictly increasing subsequence on south that ends at i.
   For each i, scan all j < i and if south[j] < south[i] update lis[i] = max(lis[i], lis[j] + 1).
3) Answer = max_i lis[i].

Complexity
----------
- Sorting: O(n log n)
- LIS DP : O(n^2)
- Total  : O(n^2), Space O(n)

Pitfalls / Variants
-------------------
- **Classic variant (no two bridges share the same north/south “city”)**:
  sort by (north ASC, **south DESC**) and run **strict** LIS (`<`) on south to prevent
  selecting two equal-north bridges.
- If your judge defines “non-crossing with ties” differently, you may need **non-decreasing**
  LIS (`<=`) on south instead of strict `<`.
  
  bool cmp(const pair<int,int>& a, const pair<int,int>& b){
    if (a.first != b.first) return a.first < b.first; // north ASC
    return a.second > b.second;                        // south DESC (blocks equal north)
  }
 // LIS condition: if (bridges[j].second < bridges[i].second)   // strictly increasing

Optional O(n log n) idea
------------------------
After sorting, compute LIS on south with a patience-sorting array:
- Use `lower_bound` for **strict** LIS; use `upper_bound` for **non-decreasing** LIS.

==========================================================================================
*/

#include<bits/stdc++.h>
using namespace std;

bool myCmp(pair<int,int>& p1, pair<int,int>& p2){
    if(p1.first == p2.first)
        return p1.second < p2.second;  // tie on north → south ASC (ties allowed variant)
    return p1.first < p2.first;        // sort by north ASC
}

int buildingBridges(vector<pair<int,int>>& bridges){
    sort(bridges.begin(), bridges.end(), myCmp);

    int n = bridges.size();
    vector<int> lis(n, 1);             // lis[i] = best chain ending at i (on south)

    for(int i = 1; i < n; i++){
        for(int j = 0; j < i; j++){
            if(bridges[j].second < bridges[i].second)       // STRICT increase on south
                lis[i] = max(lis[i], lis[j] + 1);
        }
    }
    return *max_element(lis.begin(), lis.end());
}

int main(){
    // vector<pair<int,int>> bridges = {{8, 1}, {1, 2}, {4, 3}, {3, 4}, {2,6},{6,7},{7,8},{5,5}};
    vector<pair<int,int>> bridges = {{6,2},{4,3},{2,6},{1,5},{1,3}};
    cout << "Maximum number of bridges = " << buildingBridges(bridges);
    return 0;
}
