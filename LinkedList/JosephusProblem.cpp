#include<bits/stdc++.h>
using namespace std;
int getSurvival(int n, int k){
    list<int>dll;
    for(int i=0;i<n;i++)
        dll.push_back(i);
    auto itr = dll.begin();
    while(dll.size()>1){
        for(int count = 1; count < k; count++ ){
            itr++;
            if(itr==dll.end())
                itr = dll.begin();
        }
        itr = dll.erase(itr);
        if(itr == dll.end())
            itr = dll.begin();
    }
    return *dll.begin();
}



// Algorithm for Josephus Problem (getSurvival function):
//
// Problem Statement:
//   - n people (numbered from 0 to n-1) are standing in a circle.
//   - Starting from person 0, every k-th person is eliminated in the circle.
//   - This process continues until only one person remains.
//   - The goal is to return the position (number) of the survivor.
//
// Approach:
// 1. Use a doubly linked list to simulate the circle of people.
//    - list<int> dll stores people from 0 to n-1
//    - We can erase elements efficiently using iterators
//
// 2. Initialize an iterator to the beginning of the list.
//
// 3. Loop until only one person remains:
//    a. Move the iterator (k-1) steps forward, wrapping around to the start if needed.
//    b. Erase the k-th person (the one currently pointed by iterator).
//    c. Update iterator to point to the next person after erase, wrapping again if needed.
//
// 4. When only one person is left, return the value at the front of the list (survivor's position).

int getSurvival(int n, int k) {
    // Step 1: Create a circular list of people numbered 0 to n-1
    list<int> dll;
    for (int i = 0; i < n; i++)
        dll.push_back(i);

    // Step 2: Start from the beginning
    auto itr = dll.begin();

    // Step 3: Loop until one person remains
    while (dll.size() > 1) {
        // Move (k-1) steps forward in the list
        for (int count = 1; count < k; count++) {
            itr++;
            if (itr == dll.end())
                itr = dll.begin(); // Wrap around
        }

        // Erase the k-th person
        itr = dll.erase(itr); // erase returns next iterator

        // If erase reached end, wrap around
        if (itr == dll.end())
            itr = dll.begin();
    }

    // Step 4: Return the last remaining person's position
    return *dll.begin();
}
