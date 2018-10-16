#ifndef MULTISET_HPP
#define MULTISET_HPP

#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include "Node.hpp"
#include "Set.hpp"


class MultiSet {
    Node* root;
    
    // main operations
    Node* insert(Node*, int);
    Node* contains(Node*, int) const;
    Node* remove(Node*, int);
    
    // AVL managing
    int size(Node*) const;
    int height(Node* x);
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
        int size() const;
        int height();
        void insert(int);
        void remove(int);
        bool contains(int) const;
        void inorder();
        Node* get_root() {return root;};
        void inorder(Node*);
        std::vector<int> items() const;
        void getItems(Node* x, std::vector<int>& items) const;
                
        // constructors
        MultiSet();
        ~MultiSet();
        MultiSet(const MultiSet&);
        MultiSet(MultiSet&&);
        
        // operators
        MultiSet& operator=(MultiSet);
        MultiSet& operator>>(int);
        MultiSet& operator<<(int);
        MultiSet& operator+=(const MultiSet&);
        MultiSet& operator*=(const MultiSet&);
        MultiSet& operator-=(const MultiSet&);
        friend MultiSet operator+(MultiSet, const MultiSet&);
        friend MultiSet operator*(const MultiSet&, const MultiSet&);
        friend MultiSet operator-(const MultiSet&, const MultiSet&);
        friend void swap(MultiSet&, MultiSet&);
        operator Set();
};

#endif