class Solution {
public:
    static bool myCmp(const vector<int> &x1, const vector<int> &x2){
        return x1[1] > x2[1];
    }
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        sort(boxTypes.begin(), boxTypes.end(), myCmp);
        int maxUnits = 0;
        for(int i=0;i<boxTypes.size();i++){
            if(boxTypes[i][0] <= truckSize){
                maxUnits += boxTypes[i][0] * boxTypes[i][1];
                truckSize -= boxTypes[i][0];
            } else {
                maxUnits += truckSize * boxTypes[i][1];
                break;
            }

            if(truckSize == 0)
                break;
        }
        return maxUnits;
    }
};


/*
==================== REVISION BLOCK — Maximum Units on a Truck (Greedy by density) ====================

Problem
-------
You’re given boxTypes[i] = {boxes_i, unitsPerBox_i} and a truck capacity `truckSize`
(number of boxes it can carry). Maximize the **total units** loaded.

Pattern
-------
Greedy by **value density** (units per box):
- Take boxes from the type with the **most units per box** first.
- Fill as many as possible until the truck is full, then move to the next best type.

Algorithm (step-by-step)
------------------------
1) Sort boxTypes by `unitsPerBox` in **descending** order.
2) For each type in that order:
   a) `take = min(boxes_i, truckSize)`
   b) `totalUnits += 1LL * take * unitsPerBox_i`
   c) `truckSize -= take`
   d) If `truckSize == 0` → stop.
3) Return `totalUnits`.

Why it works (correctness)
--------------------------
The objective is linear and we can take any integer number of boxes from each type (up to availability).
A classic greedy exchange argument shows that prioritizing the highest `unitsPerBox` never hurts:
if a lower-density box occupies capacity while a higher-density one is available, swapping them increases gain.

Complexity
---------
- Time: O(k log k) to sort k types + O(k) scan.
- Space: O(1) extra (in-place sort).

Edge Cases / Pitfalls
---------------------
- `truckSize == 0` → answer 0.
- Empty `boxTypes` → answer 0.
- Use 64-bit when accumulating units to avoid overflow in `take * unitsPerBox`.
- Comparator should take **const references**.

Optional Faster Variant (Counting Sort)
---------------------------------------
If `unitsPerBox` has a small bound (e.g., ≤ 1000 as in LC 1710), use counting:
- Count total boxes available for each `u = unitsPerBox`.
- Iterate `u` from high to low and greedily take boxes.
- Time: O(U + k), Space: O(U).

========================================================
*/

class Solution {
public:
    static bool byUnitsDesc(const std::vector<int>& a, const std::vector<int>& b) {
        return a[1] > b[1];
    }

    int maximumUnits(std::vector<std::vector<int>>& boxTypes, int truckSize) {
        std::sort(boxTypes.begin(), boxTypes.end(), byUnitsDesc);

        long long total = 0;
        for (const auto& t : boxTypes) {
            if (truckSize == 0) break;
            int boxes = t[0], units = t[1];
            int take = std::min(boxes, truckSize);
            total += 1LL * take * units;
            truckSize -= take;
        }
        return (int)total;
    }
};

/* ==================== Optional: Counting approach (when unitsPerBox is small) ====================
int maximumUnits_counting(std::vector<std::vector<int>>& boxTypes, int truckSize) {
    if (truckSize <= 0) return 0;
    int maxU = 0;
    for (auto& t : boxTypes) maxU = std::max(maxU, t[1]);
    std::vector<long long> cnt(maxU + 1, 0); // cnt[u] = total boxes with unitsPerBox = u
    for (auto& t : boxTypes) cnt[t[1]] += t[0];

    long long total = 0;
    for (int u = maxU; u >= 0 && truckSize > 0; --u) {
        if (cnt[u] == 0) continue;
        long long take = std::min<long long>(cnt[u], truckSize);
        total += take * u;
        truckSize -= (int)take;
    }
    return (int)total;
}
