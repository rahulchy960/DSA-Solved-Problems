class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) { 
        vector<int>stack;
        stack.push_back(asteroids[0]);
        for(int i=1; i<asteroids.size();i++){
            int curr = asteroids[i];
            while(!stack.empty() && stack.back()>0 && curr < 0){ // only time when collision happen
                int diff  = stack.back() + curr;
                if(diff < 0)
                    stack.pop_back();  // top of the stack destroyed
                else if(diff > 0)
                    curr = 0;   // current element destroyed
                else {  // both destryed
                    stack.pop_back();
                    curr = 0;
                }
            }
            if(curr) // if current element not destroyed
                stack.push_back(curr);
        }
        return stack;
    }
};


/*
==================== REVISION BLOCK — Asteroid Collision (Stack, one pass) ====================

Problem
-------
Given an array `asteroids`, each value is an asteroid: sign = direction (right if >0, left if <0),
abs(value) = size. When two asteroids moving toward each other collide, the smaller explodes;
if equal, both explode. Output the state after all collisions.

Core Idea
---------
Use a stack of **settled** asteroids. A collision is only possible when the top of the stack
moves right (>0) and the incoming asteroid moves left (<0). Resolve that clash before pushing.

Algorithm (amortized O(n))
--------------------------
1) Initialize an empty stack.
2) For each `curr` in `asteroids`:
   - While stack not empty **and** stack.back() > 0 **and** curr < 0 (they face each other):
       * diff = stack.back() + curr
       * if diff < 0  → top is smaller: pop it, continue checking with new top
       * if diff > 0  → curr is smaller: set curr = 0 (destroyed), stop loop
       * else (diff == 0) → equal: pop top, set curr = 0, stop loop
   - If curr != 0 after the loop (survived), push it.
3) The stack contains the final configuration.

Why it works
------------
Only (right, left) pairs can collide. The while-loop resolves all collisions the current asteroid
might have with prior right-movers, possibly popping multiple smaller ones (chain reaction).

Complexity
----------
- Time: O(n) amortized — each asteroid is pushed at most once and popped at most once.
- Space: O(n) for the stack in the worst case (no collisions).

Edge Notes
----------
- If the input can be empty, guard before `stack.push_back(asteroids[0])`.
- Variable name `stack` shadows the concept; it’s a `vector<int>` (fine in C++).
========================================================
*/

class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        vector<int> stack;
        // If inputs can be empty, uncomment:
        // if (asteroids.empty()) return stack;

        stack.push_back(asteroids[0]);            // seed with first asteroid

        for (int i = 1; i < (int)asteroids.size(); i++) {
            int curr = asteroids[i];

            // Collide while top is moving right and current moves left
            while (!stack.empty() && stack.back() > 0 && curr < 0) {
                int diff = stack.back() + curr;   // effectively compares sizes: top vs |curr|
                if (diff < 0) {
                    // top is smaller → it explodes; keep testing curr against previous
                    stack.pop_back();
                } else if (diff > 0) {
                    // curr is smaller → it explodes
                    curr = 0;
                } else {
                    // equal sizes → both explode
                    stack.pop_back();
                    curr = 0;
                }
                if (curr == 0) break;             // no further collisions if curr destroyed
            }

            if (curr) stack.push_back(curr);      // survived (or no collision possible)
        }
        return stack;
    }
};
