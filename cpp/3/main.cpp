#include "NAedrTemplate.hpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
    int side;
    cout << "Insert side : "; cin >> side;
    
    NAedr<double>* tetraedr = new Tetraedr<double>(side);
    cout << "Tetrader area   : " << tetraedr->area() << endl;
    cout << "Tetrader volume : " << tetraedr->volume() << endl;
    
    NAedr<double>* dodekaedr = new Dodekaedr<double>(side);
    cout << "Dodekaedr area  : " << dodekaedr->area() << endl;
    cout << "Dodekaedr volume: " << dodekaedr->volume() << endl;
    
    NAedr<double>* icosaedr = new Icosaedr<double>(side);
    cout << "Icosaedr area   : " << icosaedr->area() << endl;
    cout << "Icosaedr volume : " << icosaedr->volume() << endl;
    
    delete tetraedr;
    delete dodekaedr;
    delete icosaedr;
}