#include <stdlib.h>
#include <vector>

struct Node {
    int value;
    int height;
    int size;
    Node* left;
    Node* right;
        
    Node(int xvalue, int xheight, int xsize) : value(xvalue), height(xheight), size(xsize) {}
    ~Node() {
        left = right = nullptr;
        delete left;
        delete right;
    }
};

class Set {
    Node* root;
    
    // main operations
    Node* insert(Node*, int);
    Node* contains(Node*, int);
    Node* remove(Node*, int);
    
    // AVL managing
    int size(Node*);
    int height(Node* x);
    int factor(Node*);
    Node* balance(Node*);
    Node* rotateRight(Node*);
    Node* rotateLeft(Node*);
    
    // min
    void removeMin();
    Node* removeMin(Node*);
    Node* min(Node*);
    
    // output tree
    Node* inorder(Node*);
    
    public:
        // main operations
        bool empty();
        int size();
        int height();
        void insert(int);
        void remove(int);
        bool contains(int);
        void inorder();
        Node* get_root() {return root;};
                
        // constructors
        Set() { root = NULL; };
        ~Set() { delete root; };
};

class MultiSet {
    Node* root;
    
    // main operations
    Node* insert(Node*, int);
    Node* contains(Node*, int);
    Node* remove(Node*, int);
    
    // AVL managing
    int size(Node*);
    int height(Node* x);
    int factor(Node*);
    Node* balance(Node*);
    Node* rotateRight(Node*);
    Node* rotateLeft(Node*);
    
    // min
    void removeMin();
    Node* removeMin(Node*);
    Node* min(Node*);
    
    // iterations
    Node* inorder(Node*);
        
    public:
        // main operations
        bool empty();
        int size();
        int height();
        void insert(int);
        void remove(int);
        bool contains(int);
        void inorder();
        
        std::vector<int> items() const;
        void getItems(Node*, std::vector<int>&) const;
        
        // operators
        void operator=(const MultiSet&);
        MultiSet& operator<<(int);
        MultiSet& operator>>(int);
        MultiSet operator+(const MultiSet&);
        MultiSet operator*(const MultiSet&);
        MultiSet operator-(const MultiSet&);
        MultiSet& operator+=(const MultiSet&);
        MultiSet& operator*=(const MultiSet&);
        MultiSet& operator-=(const MultiSet&);
        operator Set();
        
        // constructors
        MultiSet() { root = NULL; };
        ~MultiSet() { delete root; };
};
