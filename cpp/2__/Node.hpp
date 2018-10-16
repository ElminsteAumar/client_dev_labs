#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    int value;
    int height;
    int size;
    Node* left = nullptr;
    Node* right = nullptr;
        
    Node(int v, int h, int s) : value(v), height(h), size(s), left(nullptr), right(nullptr) {}
    
    ~Node() {
        auto l = left, r = right;
        left = right = nullptr;
        delete l;
        delete r;
    }
};

#endif