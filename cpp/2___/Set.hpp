#ifndef SET_HPP
#define SET_HPP

#include <iostream>
#include <vector>
#include <utility>

class Set {
    std::vector<int> s;
    
    int search(int lo, int hi, int key) const {
        if (hi < lo) return -1;
        
        int mid = (lo + hi) / 2;
        
        if (key == s[mid]) return mid;
        if (key > s[mid]) return search(mid + 1, hi, key);
        return search(lo, mid - 1, key);
    }
    
public:
    // main functions
    void insert(int key) {
        if (contains(key)) return;
        if (s.size() == 0) {
            s.push_back(key); 
            return;
        }
        int i, n = s.size();
        s.push_back(key);

        for (i = n - 1; i >= 0 && s[i] >= key; i--) s[i + 1] = s[i];
        s[i + 1] = key;
    }

    void remove(int key) {
        int index = search(0, s.size(), key);
        if (index == -1) return;
        s.erase(s.begin() + index);
    }
    
    void show() const { for (int key : s) std::cout << key << " "; }
    
    bool contains(int key) const {
        if (s.size() == 0) return false;
        if (search(0, s.size()-1, key) == -1) return false;
        return true;
    }
    
    // operators
    Set& operator=(Set that) {
        this->s.swap(that.s);
        return *this;
    }
    Set& operator>>(int key) {
        this->remove(key);
        return *this;
    }
    Set& operator<<(int key) {
        this->insert(key);
        return *this;
    }
    Set& operator+=(const Set& set) {
        Set temp = *this + set;
        this->s.swap(temp.s);
        return *this;
    }
    Set& operator*=(const Set& set) {
        Set temp = *this * set;
        this->s.swap(temp.s);
        return *this;
    }
    Set& operator-=(const Set& set) {
        Set temp = *this - set;
        this->s.swap(temp.s);
        return *this;
    }
    
    friend Set operator+(Set a, const Set& b) {
        std::vector<int> it = b.s;
        for (int key : it) a.insert(key);
        return a;
    }
    friend Set operator*(Set a, const Set& b) {
        Set result;
        
        std::vector<int> it = b.s;
        for (int key : it) if (a.contains(key)) result.insert(key);
        return result;
    }
    friend Set operator-(Set a, const Set& b) {
        Set result;
        
        std::vector<int> it = a.s;
        for (int key : it) if (!b.contains(key)) result.insert(key);
        return result;
    }
    friend Set operator%(Set a, const Set& b) {
        Set result = (a + b) - (a * b);
        return result;
    }
};

#endif