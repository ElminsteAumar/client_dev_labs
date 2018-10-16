#ifndef NODE_HPP
#define NODE_HPP

struct Node {
    int value;
    int height;
    int size;
    Node* left = nullptr;
    Node* right = nullptr;
        
    Node(int xvalue, int xheight, int xsize) : value(xvalue), height(xheight), size(xsize) {}
    
    ~Node() {
        auto l = left, r = right;
        left = right = nullptr;
        delete l;
        delete r;
    }
};

#endif