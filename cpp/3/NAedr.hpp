#ifndef NAEDR_HPP
#define NAEDR_HPP

#include <stdlib.h>
#include <cmath>
#define DEFAULT 10

class NAedr {
protected:
    double side;
public:
    virtual double area() = 0;
    virtual double volume() = 0;
};

class Tetraedr : NAedr {
public:
    Tetraedr() { side = DEFAULT; }
    Tetraedr(double a) { side = std::abs(a); }
    
    double area() override { return std::sqrt(3)*side*side; }
    double volume() override { return std::pow(side, 3)/(6*std::sqrt(2)); }
};

class Dodekaedr : NAedr {
public:
    Dodekaedr() { side = DEFAULT; }
    Dodekaedr(double a) { side = std::abs(a); }
    
    double area() override { return 3*std::pow(side, 2)*std::sqrt(25+10*std::sqrt(5)); }
    double volume() override { return 0.25*(15+7*std::sqrt(5))*pow(side, 3); }
};

class Icosaedr : NAedr {
public:
    Icosaedr() { side = DEFAULT; }
    Icosaedr(double a) { side = std::abs(a); }
    
    double area() override { return pow(side, 2) * 5 * std::sqrt(3); }
    double volume() override { return 5*(3+std::sqrt(5))*pow(side, 3)/12; }
};

#endif