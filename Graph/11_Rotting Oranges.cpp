class Solution {
public:

    vector<vector<int>>dir = {{-1,0}, {0, -1},{1,0}, {0,1}};
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        queue<pair<int, int>>q;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==2){
                    q.push({i,j});
                    grid[i][j] = 0;
                }
            }
        }

        int count = 0;

        while(!q.empty()){
            int num = q.size();
            bool flag = false;
            for(int i=0; i<num;i++){
                pair<int, int>rot = q.front();
                q.pop();
                for(int d=0;d<4;d++){
                    int dx = rot.first + dir[d][0];
                    int dy = rot.second + dir[d][1];
                    if(dx>=0 && dx<m && dy>=0 && dy<n && grid[dx][dy]==1){
                        q.push({dx, dy});
                        grid[dx][dy] = 0;
                        flag = true;
                    }
                }
            } 
            if(flag) count++;
        }

        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]==1){
                    return -1;
                }
            }
        }
        return count;
    }
};


/*
==================== REVISION BLOCK — Rotting Oranges (Multi-Source BFS, level by level) ====================

Problem
-------
Grid of size m×n with cells:
- 0 = empty, 1 = fresh orange, 2 = rotten orange.
Each minute, any fresh orange that is 4-adjacent to a rotten one becomes rotten.
Return the minimum minutes to rot all oranges, or -1 if impossible.

Pattern
-------
- **Multi-source BFS**: all initially rotten oranges are simultaneous sources.
- Process the grid **level by level** (each BFS layer = 1 minute).
- When a layer rots at least one fresh orange, increment the minute counter.

Algorithm
---------
1) Push coordinates of all initially rotten cells (value 2) into the queue.
   (This code also marks them as 0 to denote “processed”; that’s okay as we only care if any 1’s remain at the end.)
2) While the queue isn’t empty:
   - Let `num` be the current queue size (this layer).
   - For each of these `num` cells, try the 4 directions; whenever you find a fresh (1):
       * change it to 0 (mark as processed/rotted),
       * enqueue it (it becomes a source for the next minute),
       * set a flag indicating at least one fresh got rotted in this layer.
   - After the layer finishes, if the flag is true, increment `count` (minutes).
3) After BFS, scan the grid; if any 1 remains, return -1; else return `count`.

Why it works
------------
- Multi-source BFS spreads “rot” in waves; each wave corresponds to one minute.
- By enqueuing all newly rotted oranges for the next wave, we simulate the parallel rotting.

Complexity
----------
- Time: O(m·n) — each cell is enqueued/processed at most once; 4 neighbors checked each time.
- Space: O(m·n) in the worst case for the queue.

Edge cases / Notes
------------------
- If there are fresh oranges but no initial rotten ones, BFS does nothing and the final scan yields -1.
- If there are no fresh oranges at all, the answer is 0.
- Marking visited by writing 0 is fine here because only the presence of any 1 matters at the end.
  (Alternative: keep a fresh counter and decrement it when rotting; early exit when it reaches 0.)

========================================================
*/

class Solution {
public:
    // 4-directional neighbors: up, left, down, right
    std::vector<std::vector<int>> dir = {{-1,0}, {0,-1}, {1,0}, {0,1}};

    int orangesRotting(std::vector<std::vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        std::queue<std::pair<int,int>> q;

        // 1) Initialize queue with all initially rotten oranges (multi-source BFS)
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 2) {
                    q.push({i, j});
                    grid[i][j] = 0; // mark as processed to avoid revisits (optional)
                }
            }
        }

        int count = 0; // minutes elapsed

        // 2) BFS layer by layer; each layer represents one minute
        while (!q.empty()) {
            int num = q.size();
            bool flag = false; // whether this minute rotted at least one fresh orange

            for (int t = 0; t < num; t++) {
                auto rot = q.front(); q.pop();

                // Try the 4 directions
                for (int d = 0; d < 4; d++) {
                    int dx = rot.first  + dir[d][0];
                    int dy = rot.second + dir[d][1];

                    // If neighbor is inside grid and is a fresh orange, rot it
                    if (dx >= 0 && dx < m && dy >= 0 && dy < n && grid[dx][dy] == 1) {
                        q.push({dx, dy});   // will act as rotten in the next minute
                        grid[dx][dy] = 0;   // mark processed/rotted
                        flag = true;        // at least one fresh got rotted this minute
                    }
                }
            }
            if (flag) count++; // only advance minute if anything changed this layer
        }

        // 3) If any fresh orange remains, it's impossible
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) return -1;
            }
        }
        return count;
    }
};
