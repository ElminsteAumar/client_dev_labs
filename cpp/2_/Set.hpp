#ifndef SET_HPP
#define SET_HPP

#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include "Node.hpp"

//template<typename Key>
class Set {
    Node* root;
    // main operations
    Node* insert(Node*, int);
    Node* contains(Node*, int) const;
    Node* remove(Node*, int);
    
    // AVL managing
    int size(Node*) const;
    int height(Node* x) const;
    int factor(Node*);
    Node* balance(Node*);
    Node* rotateRight(Node*);
    Node* rotateLeft(Node*);
    void removeMin();
    Node* removeMin(Node*);
    Node* min(Node*);
    
    public:
        // main operations
        bool empty();
        int size();
        int height();
        void insert(int);
        void remove(int);
        bool contains(int) const;
        void inorder();
        Node* get_root() {return root;};
        void inorder(Node*);
        std::vector<int> items() const;
        void getItems(Node* x, std::vector<int>& items) const;
    
        // constructors/destrucors
        Set();
        ~Set();
        Set(const Set&);
        Set(Set&&);
        
        //operators
        Set& operator=(Set);
        Set& operator>>(int);
        Set& operator<<(int);
        Set& operator+=(const Set&);
        Set& operator*=(const Set&);
        Set& operator-=(const Set&);
        friend Set operator+(const Set&, const Set&);
        friend Set operator*(const Set&, const Set&);
        friend Set operator-(const Set&, const Set&);
        friend void swap(Set&, Set&);
};

#endif