#ifndef MULTISET_HPP
#define MULTISET_HPP

#include "Set.hpp"
#include <iostream>
#include <vector>
#include <utility>

class MultiSet {
    std::vector<int> s;
    
    int search(int low, int high, int key) const {
        if (high < low) return -1;
        
        int mid = (low + high) / 2;
        
        if (key == s[mid]) return mid;
        if (key > s[mid]) return search(mid + 1, high, key);
        return search(low, mid - 1, key);
    }
public:
    // main functions
    void insert(int key) {
        if (s.size() == 0) {
            s.push_back(key); 
            return;
        }
        
        int i, n = s.size();
        s.push_back(key);
        for (i = n - 1; i >= 0 && s[i] >= key; i--) {
            s[i + 1] = s[i];
        }
        s[i + 1] = key;
    }
//     
    void remove(int key) {
        int index = search(0, s.size(), key);
        if (index == -1) return;
        s.erase(s.begin() + index);
    }
    
    void show() const { for (int key : s) std::cout << key << " "; }
    
    bool contains(int key) const {
        if (s.size() == 0) return false;
        if (search(0, s.size(), key) == -1) return false;
        return true;
    }
    
    // operators
    MultiSet& operator=(MultiSet that) {
        this->s.swap(that.s);
        return *this;
    }
    MultiSet& operator>>(int key) {
        this->remove(key);
        return *this;
    }
    MultiSet& operator<<(int key) {
        this->insert(key);
        return *this;
    }
    MultiSet& operator+=(const MultiSet& set) {
        MultiSet temp = *this + set;
        this->s.swap(temp.s);
        return *this;
    }
    MultiSet& operator*=(const MultiSet& set) {
        MultiSet temp = *this * set;
        this->s.swap(temp.s);
        return *this;
    }
    MultiSet& operator-=(const MultiSet& set) {
        MultiSet temp = *this - set;
        this->s.swap(temp.s);
        return *this;
    }
    
    friend MultiSet operator+(MultiSet a, const MultiSet& b) {
        std::vector<int> it = b.s;
        for (int key : it) a.insert(key);
        return a;
    }
    friend MultiSet operator*(MultiSet a, const MultiSet& b) {
        MultiSet result;
        
        std::vector<int> it = b.s;
        for (int key : it) if (a.contains(key)) result.insert(key);
        return result;
    }
    friend MultiSet operator-(MultiSet a, const MultiSet& b) {
        MultiSet result;
        
        std::vector<int> it = a.s;
        for (int key : it) if (!b.contains(key)) result.insert(key);
        return result;
    }
    operator Set() {
        Set result;
        for (int key : this->s) result.insert(key);
        return result;
    }
};

#endif