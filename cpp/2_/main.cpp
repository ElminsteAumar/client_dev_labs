#include "Set.hpp"
#include "MultiSet.hpp"
#include <iostream>
#include <time.h>
#define N 5
using namespace std;

void show(string, Set&);
//makvoid show(string, MultiSet);

int main(int argc, char* argv[]) {
    Set mset1, mset2, unite, intersection, diff;
    
    for (int i = 0; i < N; i++) {
        mset1 << rand()%10;
        mset2 << rand()%10;
    }
    
    // operations./m
    unite = mset1 + mset2;
    intersection = mset1 * mset2;
    diff = mset1 - mset2;
    
    show("MultiSet 1", mset1);
    show("MultiSet 2", mset2);
    show("Unite", unite);
    show("intersection", intersection);
    show("Diff", diff);
    
    // delete/add op
    mset1 << 0 << 1 << 2;
    mset2 >> 0 >> 1 >> 2;
    
    show("MultiSet 1 | Add", mset1);
    show("MultiSet 2 | Delete", mset2);
    
    // Add repeating numbers
    mset1 << 100 << 100 << 100;
    mset2 << 99 << 99 << 99;
    
    show("MultiSet 1", mset1);
    show("MultiSet 2", mset2);
    
    // Conversion operator
    Set set1 = Set(mset1);
    Set set2 = Set(mset2);
    
    show("Set 1", set1);
    show("Set 2", set2);
}

void show(string mes, Set& s) {
    cout << mes << " { ";
    vector<int> it = s.items();
    for (int i : it) cout << i << ", ";
    cout << "}" <<endl;
}