#include <iostream>
#include "Set.hpp"
#define N 10
using namespace std;

int main(int argc, char* argv[]) {
    Set s;
    MultiSet s1;
    for (int i = 0; i < N; i++) {
        s.insert(i);
        s1.insert(i);
    }
    s1.insert(0);
    s.insert(0);
    
    
    s.inorder();
    s1.inorder();
    Set s2;
    vector<int> items = s1.items();
    //Set set;
    for (int i = 0; i < items.size(); i++) s2.insert(items[i]);
}