#include "S.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    Set<int> s;
    
    for (int i = 0; i < 10; i++) s.insert(i);
    s.inorder();
    
    for (int i = 4; i < 8; i++) s.remove(i);
    s.inorder();
    
    Set<int> set = s;
    set.inorder();
    s.inorder();
}