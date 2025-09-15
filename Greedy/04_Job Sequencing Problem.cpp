class Solution {
  public:
    static bool myCmp(const pair<int,int>&p1, const pair<int, int>&p2){
        return p1.first > p2.first;
    }
    vector<int> jobSequencing(vector<int> &deadline, vector<int> &profit) {
        // code here
        int n = profit.size();
        vector<pair<int, int>>jobs;
        int maxTime = 0;
        for(int i=0;i<n;i++){
            jobs.push_back({profit[i], deadline[i]});
            maxTime = max(maxTime, deadline[i]);
        }
        sort(jobs.begin(), jobs.end(), myCmp);
        vector<bool>slots(maxTime+1, false);
        int jobCount = 0;
        int totalProfit = 0;
        for(int i=0; i<n; i++){
            int time = jobs[i].second;
            for(int j = time; j>0; j--){
                if(slots[j] == false){
                    slots[j] = true;
                    jobCount++;
                    totalProfit += jobs[i].first;
                    break;
                }
            }
        }
        vector<int>res;
        res.push_back(jobCount);
        res.push_back(totalProfit);
        return res;
    }
};


/*
==================== REVISION BLOCK — Job Sequencing with Deadlines (maximize profit) ====================

Problem
-------
You have n jobs; job i takes 1 unit of time, yields profit[i], and must finish by deadline[i] (integer).
You can do at most **one** job per time slot. Choose a subset to **maximize total profit**.
Return {number_of_jobs_done, total_profit}.

Pattern
-------
Greedy + **latest-feasible-slot**:
- Sort jobs by **profit descending**.
- For each job, try to place it at the **latest free** slot ≤ its deadline.
- This keeps high-profit jobs while leaving earlier slots free for others.

Algorithm (step-by-step; slot-filling)
--------------------------------------
1) Build pairs (profit, deadline) and find `maxTime = max(deadline)`.
2) Sort jobs by profit ↓.
3) Create a boolean array `slots[1..maxTime]` = false (free).
4) For each job (p, d) in sorted order:
   a) For t = min(d, maxTime) down to 1:
        if slots[t] == false:
            slots[t] = true; take this job;
            jobCount++, totalProfit += p; break
5) Return {jobCount, totalProfit}.

Why it works (correctness)
--------------------------
Among all schedules that do a given set of jobs, there exists one that places each job
as **late as possible**. Greedily trying jobs by **highest profit first** and placing them
into the latest free slot never hurts future choices and is optimal.

Complexity
---------
- Sorting: O(n log n)
- Slot search: worst-case O(Σ min(deadline_i, maxTime)) ⩽ O(n · maxTime)
  ⇒ Overall worst-case O(n log n + n · maxTime)
- Space: O(maxTime)

Edge Cases / Pitfalls
---------------------
- If a deadline ≤ 0, the job is unschedulable (ignore it).
- Use `long long` for profit sum to avoid overflow.
- `slots` are **1-indexed**; iterate t from `min(d,maxTime)` down to 1.
- Comparator must take **const references** for `std::sort`.

Greedy Alternatives (same optimal goal)
---------------------------------------
A) **DSU (Union-Find) for O(α(maxTime)) slot search**  
   - Maintain parent[t] = the latest free slot ≤ t.  
   - When you occupy slot s, union(s, s-1).  
   - Each job placement becomes amortized O(α(maxTime)).

B) **Deadline-ordered + Min-Heap of profits**  
   - Sort by deadline ↑; scan jobs, push profit into a min-heap.  
   - If heap size > current job’s deadline, pop the smallest profit.  
   - At the end, heap holds the chosen jobs; sum = total profit; size = job count.  
   - Time O(n log n); space O(n). (Doesn’t recover exact time slots, but not needed here.)

========================================================
*/

// Your approach (tidied + 64-bit profit)
class Solution {
public:
    static bool byProfitDesc(const std::pair<int,int>& a, const std::pair<int,int>& b) {
        return a.first > b.first;
    }

    std::vector<int> jobSequencing(std::vector<int> &deadline, std::vector<int> &profit) {
        int n = (int)profit.size();
        if (n == 0) return {0, 0};

        std::vector<std::pair<int,int>> jobs; // {profit, deadline}
        jobs.reserve(n);
        int maxTime = 0;
        for (int i = 0; i < n; ++i) {
            if (deadline[i] > 0) {                // ignore non-positive deadlines
                jobs.emplace_back(profit[i], deadline[i]);
                maxTime = std::max(maxTime, deadline[i]);
            }
        }
        if (jobs.empty()) return {0, 0};

        std::sort(jobs.begin(), jobs.end(), byProfitDesc);

        std::vector<char> slots(maxTime + 1, 0);  // 1..maxTime
        int jobCount = 0;
        long long totalProfit = 0;

        for (auto &job : jobs) {
            int d = std::min(job.second, maxTime);
            for (int t = d; t >= 1; --t) {
                if (!slots[t]) {
                    slots[t] = 1;
                    ++jobCount;
                    totalProfit += job.first;
                    break;
                }
            }
        }
        return {jobCount, (int)totalProfit};
    }
};

/* ==================== Faster slot search: DSU / Union-Find ====================
- parent[t] = latest free slot ≤ t (0 means no slot).
- find(t) gives where to place; after using s, set parent[s] = find(s-1).

Time: O(n log n + n α(maxTime)), Space: O(maxTime)
*/
class Solution_DSU {
    std::vector<int> parent;
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
public:
    static bool byProfitDesc(const std::pair<int,int>& a, const std::pair<int,int>& b) {
        return a.first > b.first;
    }
    std::vector<int> jobSequencing(std::vector<int> &deadline, std::vector<int> &profit) {
        int n = (int)profit.size();
        if (n == 0) return {0, 0};

        std::vector<std::pair<int,int>> jobs;
        jobs.reserve(n);
        int maxTime = 0;
        for (int i = 0; i < n; ++i) {
            if (deadline[i] > 0) {
                jobs.emplace_back(profit[i], deadline[i]);
                maxTime = std::max(maxTime, deadline[i]);
            }
        }
        if (jobs.empty()) return {0, 0};

        std::sort(jobs.begin(), jobs.end(), byProfitDesc);

        parent.resize(maxTime + 1);
        for (int t = 0; t <= maxTime; ++t) parent[t] = t;

        int jobCount = 0;
        long long totalProfit = 0;
        for (auto &job : jobs) {
            int d = std::min(job.second, maxTime);
            int s = find(d);                 // best free slot ≤ d
            if (s > 0) {                     // slot 0 means none available
                // occupy s and union with s-1
                totalProfit += job.first;
                ++jobCount;
                parent[s] = find(s - 1);
            }
        }
        return {jobCount, (int)totalProfit};
    }
};

/* ==================== Alternative: Deadline ↑ + Min-Heap of profits ====================
- Keeps the best set without tracking exact time slots.
- Easy and fast: O(n log n)

std::vector<int> jobSequencing_heap(std::vector<int>& deadline, std::vector<int>& profit) {
    int n = (int)profit.size();
    std::vector<std::pair<int,int>> jobs;
    jobs.reserve(n);
    for (int i = 0; i < n; ++i) if (deadline[i] > 0) jobs.emplace_back(deadline[i], profit[i]);
    if (jobs.empty()) return {0, 0};

    std::sort(jobs.begin(), jobs.end()); // by deadline ↑
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    long long total = 0;
    for (auto& [d, p] : jobs) {
        minHeap.push(p);
        total += p;
        if ((int)minHeap.size() > d) { total -= minHeap.top(); minHeap.pop(); }
    }
    return {(int)minHeap.size(), (int)total};
}
*/
