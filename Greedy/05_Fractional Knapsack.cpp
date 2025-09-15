class Solution {
  public:
    static bool myCmp(const pair<int, int> &p1, const pair<int, int> &p2){
        double res1 = (double)p1.first / p1.second;
        double res2 = (double)p2.first / p2.second;
        return res1 > res2;
    }
    double fractionalKnapsack(vector<int>& val, vector<int>& wt, int capacity) {
        // code here
        int n = wt.size();
        vector<pair<int, int>> ratio;
        for(int i=0;i<n;i++)
            ratio.push_back({val[i], wt[i]});
        
        sort(ratio.begin(), ratio.end(), myCmp);
        double profit = 0.0;
        for(int i=0; i<n; i++){
            if(ratio[i].second <= capacity){
                profit += ratio[i].first;
                capacity -= ratio[i].second;
            }
                
            else{
                profit += capacity * ratio[i].first / (double)ratio[i].second;
                break;
            }
            
            if(capacity == 0)
                break;
            
            
        }
        
        return profit;
    }
};

/*
==================== REVISION BLOCK — Fractional Knapsack (greedy by value/weight) ====================

Problem
-------
Given items with value `val[i]` and weight `wt[i]`, and a knapsack capacity `C`,
maximize total **value** when you may take **fractions** of items.

Pattern
-------
Greedy by **density** (value per weight):
- Sort items in **descending** order of `val/weight`.
- Take as much as possible from each item in that order until capacity is full.

Algorithm (step-by-step, precise)
---------------------------------
1) Build items (value, weight). If `C == 0` or `n == 0` → return 0.
2) Sort items by **ratio** descending. Prefer a **division-free comparator**:
   `a.value/a.weight > b.value/b.weight`  ⇔  `a.value * b.weight > b.value * a.weight`
3) Iterate items:
   - If `wt <= C`: take whole item → `profit += val`, `C -= wt`.
   - Else: take fraction `C / wt` → `profit += (C * val / wt)` and **stop**.
4) Return `profit`.

Correctness (sketch)
--------------------
For fractional knapsack, the greedy choice of taking the available item with the current
highest value density is optimal (matroid/convexity argument). Inductively, after taking all
of the best density item (or filling the remaining capacity with its fraction), no alternative
can yield more value.

Complexity
----------
- Time: `O(n log n)` (sort) + `O(n)` scan
- Space: `O(1)` extra (if sorting in-place)

Edge Cases / Pitfalls
---------------------
- `capacity == 0` or `n == 0` → answer 0.
- Weights must be **positive**; guard against `wt == 0` (undefined density).
- Avoid floating-point comparator: use cross-multiplication to sort reliably.
- Accumulate profit in `long double` (or `double`) to preserve precision on fractions.
- Ensure fractional step computes in floating-point: cast before multiply/divide.

========================================================
*/

class Solution {
public:
    struct Item { int v, w; };

    static bool byRatio(const Item& a, const Item& b) {
        // Compare a.v/a.w vs b.v/b.w without division to avoid precision issues
        // a.v/a.w > b.v/b.w  <=>  a.v * b.w > b.v * a.w
        return 1LL * a.v * b.w > 1LL * b.v * a.w;
    }

    double fractionalKnapsack(std::vector<int>& val, std::vector<int>& wt, int capacity) {
        const int n = (int)wt.size();
        if (n == 0 || capacity <= 0) return 0.0;

        std::vector<Item> items; items.reserve(n);
        for (int i = 0; i < n; ++i) {
            if (wt[i] <= 0) continue;            // skip invalid/zero-weight items
            items.push_back({val[i], wt[i]});
        }
        if (items.empty()) return 0.0;

        std::sort(items.begin(), items.end(), byRatio);

        long double profit = 0.0L;
        int C = capacity;

        for (const auto& it : items) {
            if (C == 0) break;
            if (it.w <= C) {                     // take whole item
                profit += (long double)it.v;
                C -= it.w;
            } else {                              // take fraction
                profit += (long double)C * (long double)it.v / (long double)it.w;
                break;
            }
        }
        return (double)profit;
    }
};

/* Notes on your code
- Correct greedy structure. Two small upgrades:
  1) Use a division-free comparator (see byRatio) to avoid FP comparison issues.
  2) Accumulate in long double and cast; also guard against wt == 0.
*/
