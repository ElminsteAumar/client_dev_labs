#ifndef SET_HPP
#define SET_HPP

#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>
#include "Node.hpp"

class Set {
    Node* root;
public:
    // AVL managing
    bool empty() { return size() == 0; }
    int size() { return size(root);}
    int size(Node* x) const {
        if (x == nullptr) return 0;
        return x->size;
    }
    int height() { return height(root); }
    int height(Node* x) const {
        if (x == nullptr) return -1;
        return x->height;
    }
    
    Node* min(Node* x) {
        if (x->left == nullptr) return x;
        return min(x->left);
    }
    void removeMin() {
        if(empty()) return;
        root = removeMin(root);
    }
    Node* removeMin(Node* x) {
        if (x == nullptr) return nullptr;
        
        if (x->left != nullptr) {
            x->left = removeMin(x->left);
        } else {
            Node* temp = x->right;
            x->right = nullptr;
            delete x;
            x = temp;
        }
        
        if (x != nullptr) {
        x->height = 1 + std::max(height(x->left), height(x->right));
        x->size = 1 + size(x->left) + size(x->right);
        }
        return balance(x);
    }
    int factor(Node* x) {
        return height(x->left) - height(x->right);
    }
    
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        y->size = x->size;
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));
        return y;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        y->size = x->size;
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
        y->height = 1 + std::max(height(y->left), height(y->right));
        return y;
    }

    Node* balance(Node* x) {
        if (x == nullptr) return nullptr;
        
        if (factor(x) > 1) {
            if (factor(x->left) < 0)
                x->left = rotateLeft(x->left);
            x = rotateRight(x);
        } else if (factor(x) < -1) {
            if (factor(x->right) > 0)
                x->right = rotateRight(x->right);
            x = rotateLeft(x);
        }
        return x;
    }
    
    void insert(int value) {
        if (contains(value)) return;
        root = insert(root, value);
    }
    Node* insert(Node* x, int value) {
        if (x == nullptr) return new Node(value, 0, 1);
        if (value < x->value) {
            x->left = insert(x->left, value);
        } else if (value > x->value) {
            x->right = insert(x->right, value);
        } else {
            return x; // set contains only unique entries
        }
        
        x->height = 1 + std::max(height(x->left), height(x->right));
        x->size = 1 + size(x->left) + size(x->right);
        return balance(x);
    }
    
    void remove(int value) {
        if (!contains(value)) return;
        root = remove(root, value);
    }
    
    Node* remove(Node* x, int value) {
        if (x == nullptr) return nullptr;
        
        if (value < x->value) {
            x->left = remove(x->left, value);
        } else if(value > x->value) {
            x->right = remove(x->right, value);
        } else {
            Node* temp;
            
            if (x->left  == nullptr) temp = x->right;
            else if (x->right == nullptr) temp = x->left;
            else {
                x->value = min(x->right)->value;
                x->right = removeMin(x->right);
                temp = x;
                x = nullptr;
            }
            
            if (x != nullptr) x->left = x->right = nullptr;
            delete x;
            x = temp;
        }
        if (x != nullptr) {
            x->height = 1 + std::max(height(x->left), height(x->right));
            x->size = 1 + size(x->left) + size(x->right);
        }
        return balance(x);
    }
    
    bool contains(int value) {
        Node* x = root;
        
        while (x != nullptr) {
            if (value < x->value) {
                x = x->left;
            } else if (value > x->value) {
                x = x->right;
            } else return true;
        }
        return false;
    }
    
    void inorder() { inorder(root); std::cout << std::endl;}
    void inorder(Node* x) {
        if (x != nullptr) {
            inorder(x->left);
            std::cout << x->value << " ";
            inorder(x->right);
        }
    }
    
    void getItems(const Node* x, std::vector<int>& items) const {
        if (x != nullptr) {
            getItems(x->left, items);
            items.push_back(x->value);
            getItems(x->right, items);
        }
    }
    //constructors
    Set() : root(nullptr) {}
    Set(Set&& that) : root(std::exchange(that.root, nullptr)) {}
    Set(const Set& that) {
        *this += that;
    }
    ~Set() {
        delete root;
    }
    
    void swap(Set& a, Set& b) {
        std::swap(a.root, b.root);
    }
    // operators
    Set& operator=(Set that) {
        swap(*this, that);
        return *this;
    }
    Set& operator+=(const Set& that) {
        std::vector<int> it;
        getItems(that.root, it);
        for (int i : it) insert(i);
        return *this;
    }
};


#endif