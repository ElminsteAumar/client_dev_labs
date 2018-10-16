#include <iostream>
#include "Queen.hpp"
using namespace std;

int main() {
    cout << "Start" << endl;
    Queen queen;
    queen.show();
    
    if (queen.solve(250)) { // try 100/250/500/1000/2000
        cout << "Solved." << endl;
        queen.show();
    } else {
        cout << "Failed. Try more iterations." << endl;
    }
    return 0;
}