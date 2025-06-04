#include <iostream>
#include <vector>
#include "AVL_Tree.hpp"
using namespace std;

// Test suite for insert-only AVL test cases
vector<vector<int>> insertion_test_suite = {
    // Basic Insertion Test -> 0
    {50, 25, 75, 10, 30, 60, 80, 5, 15, 27, 55, 1},  

    // LL Rotation Test -> 1
    {30, 20, 10},

    // RR Rotation Test -> 2
    {10, 20, 30},

    // LR Rotation Test -> 3
    {30, 10, 20},

    // RL Rotation Test -> 4
    {10, 30, 20}
};

// Test suite for insert + delete test cases  // pair.first = insert cases , pair.second = delete cases
vector<pair<vector<int>, vector<int>>> test_suites = {
    // Basic Deletion Test -> 0
    {
        {50, 25, 75, 10, 30, 60, 80}, 
        {25, 75}                           
    },

    // Deletion with LL Rotation -> 1
    {
        {50, 30, 70, 20, 40, 60, 80, 10, 25},
        {60, 80, 70}
    },

    // Deletion with RR Rotation -> 2
    {
        {50, 30, 70, 20, 40, 60, 80, 65, 90},
        {20, 30, 40}
    },

    // Deletion with LR Rotation -> 3
    {
        {50, 30, 70, 20, 40, 60, 80, 35},
        {20, 70}
    },

    // Deletion with RL Rotation -> 4
    {
        {50, 30, 70, 20, 40, 60, 80, 65},
        {30, 80}
    },

    // Chain Deletion with Multiple Rebalancing -> 5
    {
        {50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 40, 55, 70, 80, 100},
        {5, 15, 10, 27, 30, 25, 40}
    },

    // Extreme Deletion Test  -> 6
    {
        {50, 25, 75, 10, 30, 60, 90, 5, 15, 27, 40, 55, 70, 80, 100},
        {5, 15, 10, 27, 40, 30, 25, 55, 70, 60, 80, 100, 90, 75, 50}
    },

    // Insert-Delete-Insert Cycles -> 7
    {
        {10, 20, 30, 40, 50},
        {20, 40}
    },

    // More Insert After Deletion -> 8
    {
        {10, 20, 30, 40, 50},
        {20, 40, 30, 50, 10}
    },

    // Zigzag Tree with Chain Deletions from Left -> 9
    {
        {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93, 3, 9, 15, 21, 28, 34, 40, 46},
        {3, 6, 9, 12, 15, 18, 21, 25}
    },

    // Zigzag Tree with Chain Deletions from Right -> 10
    {
        {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93, 3, 9, 15, 21, 28, 34, 40, 46},
        {93, 87, 81, 75, 68, 62, 56, 50}
    },

    // Almost Complete Tree with Alternating Deletions -> 11
    {
        {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93},
        {25, 75, 12, 87, 37, 62, 6, 93, 18, 56, 31, 68, 43, 81, 50}
    },

    // Cascading Rotations  -> 12
    {
        {64, 32, 96, 16, 48, 80, 112, 8, 24, 40, 56, 72, 88, 104, 120, 4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 92, 100, 108, 116, 124},
        {4, 8, 12, 16, 20, 24, 28, 32}
    },

    // Successor Chain Deletion -> 13
    {
        {50, 25, 75, 12, 37, 62, 87, 6, 18, 31, 43, 56, 68, 81, 93},
        {25, 31, 37, 43, 50, 56}
    },

    // Skewed Tree Deletion -> 14
    {
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        {10, 30, 50, 70, 90}
    },

    // Random Insertions with Systematic Deletions  -> 15
    {
        {42, 15, 88, 6, 27, 65, 93, 3, 11, 20, 35, 58, 73, 90, 97},
        {42, 15, 88, 6, 27, 65, 93, 3, 11, 20, 35, 58, 73, 90, 97}
    }
};


int main(){
    int select = 0 ; 
    cout << "Choices : 1) Insertion test suite  2) Full test suite " << endl ; 
    cout << "Enter Choice Number : " ;
    cin >> select ; 

    AVL a ; 
    if(select == 1){
        cout << "Enter the Test Case Index : " ;
        cin >> select ; 
        if(select >= insertion_test_suite.size()) { cout << "Invalid Index" ; return 0 ; }
        a.InsertKeys(insertion_test_suite[select]) ; 
    }
    else if(select == 2){
        cout << "Enter the Test Case Index : " ;
        cin >> select ; 
        if(select >= test_suites.size()) { cout << "Invalid Index" ; return 0 ; }
        a.InsertKeys(test_suites[select].first) ; 
        a.DeleteKeys(test_suites[select].second) ;
    }
    else cout << "Invalid Choice" << endl ;;
}