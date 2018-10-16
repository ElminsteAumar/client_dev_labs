#include "Set.hpp"
#include "MultiSet.hpp"
#include <iostream>
#include <string>
#include <time.h>
#define N 5
using namespace std;

void show(string, Set&, bool);
void show(string, MultiSet&, bool);

int main(int argc, char* argv[]) {
    MultiSet mset1, mset2, unite, intersection, diff;
    
    for (int i = 0; i < N; i++) {
        mset1 << rand()%N;
        mset2 << rand()%N;
    }
    
    // operations
    unite = mset1 + mset2;
    intersection = mset1 * mset2;
    diff = mset1 - mset2;
    
    cout << "Creating MultiSets" << endl;
    show("MultiSet 1", mset1, true);
    show("MultiSet 2", mset2, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Unite" << endl << "Operands : ";
    show("", mset1, false);
    show("", mset2, false);
    cout << endl;
    show("Unite", unite, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Intersection" << endl << "Operands : ";
    show("", mset1, false);
    show("", mset2, false);
    cout << endl;
    show("Intersection", intersection, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Diff" << endl << "Operands : ";
    show("", mset1, false);
    show("", mset2, false);
    cout << endl;
    show("Diff", diff, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Add assignement" << endl << "Operands : ";
    show("", mset1, false);
    show("", mset2, false);
    mset1 += mset2;
    cout << endl;
    show("MultiSet 1", mset1, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Intersection assignement" << endl << "Operands : ";
    show("", mset1, false);
    show("", mset2, false);
    mset1 *= mset2;
    cout << endl;
    show("MultiSet 1", mset1, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Diff assignement" << endl << "Operands : ";
    show("", mset1, false);
    show("", mset2, false);
    mset1 -= mset2;
    cout << endl;
    show("MultiSet 1", mset1, true);
    
    // delete/add op
    cout << " ------- " << endl;
    cout << "Operation : Add" << endl << "Operands : ";
    show("", mset1, false);
    cout << " { 0 1 2 } " << endl;
    mset1 << 0 << 1 << 2;
    show("MultiSet 1", mset1, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Delete" << endl << "Operands : ";
    show("", mset2, false);
    cout << " { 0 1 2 } " << endl;
    mset2 >> 0 >> 1 >> 2;
    show("MultiSet 2", mset2, true);
    
    // Add repeating numbers
    cout << " ------- " << endl;
    cout << "Operation : Add repeating " << endl << "Operands : ";
    show("", mset1, false);
    cout << " { 100 100 100 } " << endl;
    mset1 << 100 << 100 << 100;
    show("MultiSet 1", mset1, true);
    
    cout << " ------- " << endl;
    cout << "Operation : Add repeating " << endl << "Operands : ";
    show("", mset2, false);
    cout << " { 99 99 99 } " << endl;
    mset2 << 99 << 99 << 99;
    show("MultiSet 2", mset2, true);
    
    // Conversion operatorx
    cout << " ------- " << endl;
    cout << "Operation : Set conversion " << endl << "Operands : " << endl;
    show("MultiSet 1", mset1, true);
    show("MultiSet 2", mset2, true);
    
    Set set1 = Set(mset1);
    Set set2 = Set(mset2);
    
    cout << "Result : " << endl;
    show("Set 1", set1, true);
    show("Set 2", set2, true);
    
    Set set3 = set1 % set2;
    show("Set 3", set3, true);
}

void show(string message, Set& set, bool flag = false) {
    cout << message << " { ";
    set.show();
    cout << "} ";
    if (flag) cout << endl;
}

void show(string message, MultiSet& set, bool flag = false) {
    cout << message << " { ";
    set.show();
    cout << "} ";
    if (flag) cout << endl;
}