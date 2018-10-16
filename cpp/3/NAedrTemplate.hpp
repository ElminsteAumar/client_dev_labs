#ifndef NAEDR_HPP
#define NAEDR_HPP

#include <stdlib.h>
#include <cmath>
#include <utility>

#define DEFAULT 10

// NAedr accepts only numeric types [int, float, short, double]
template<class T>
class NAedr { 
protected:
    T side;
public:
    virtual T area() = 0;
    virtual T volume() = 0;
    NAedr<T>(T key) : side(std::abs(key)) { }
    //NAedr<T>(const T& key) : side(std::abs(key)) { }
    //NAedr<T>(T&& key) : side(std::move(std::abs(key))) { } // Bullshit for numeric types(Overloaded Longint?)
};

template<class T>
class Tetraedr : public NAedr<T> {
private:
    using NAedr<T>::side;
public:
    Tetraedr() : NAedr<T>(DEFAULT) { }
    Tetraedr(T a) : NAedr<T>(a) { }
    
    T area() override { return std::sqrt(3)*side*side; }
    T volume() override { return std::pow(side, 3)/(6*std::sqrt(2)); }
};

template<class T>
class Dodekaedr : public NAedr<T> {
private:
    using NAedr<T>::side;
public:
    Dodekaedr() : NAedr<T>(DEFAULT) { }
    Dodekaedr(T a) : NAedr<T>(a) { }
    
    T area() override { return 3*std::pow(side, 2)*std::sqrt(25+10*std::sqrt(5)); }
    T volume() override { return 0.25*(15+7*std::sqrt(5))*pow(side, 3); }
};

template<class T>
class Icosaedr : public NAedr<T> {
private:
    using NAedr<T>::side;
public:
    Icosaedr() : NAedr<T>(DEFAULT) { }
    Icosaedr(T a) : NAedr<T>(a) { }
    
    T area() override { return pow(side, 2) * 5 * std::sqrt(3); }
    T volume() override { return 5*(3+std::sqrt(5))*pow(side, 3)/12; }
};

#endif