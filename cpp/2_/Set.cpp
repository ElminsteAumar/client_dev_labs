#include "Set.hpp"
#include <iostream>
#include <vector>

Set::Set():root(nullptr) { }
Set::~Set() {
    Node* temp = root;
    root = nullptr;
    delete temp;
}
Set::Set(const Set& that) { 
    std::vector<int> it = that.items();
    for (int i : it) insert(i);
}
Set::Set(Set&& that) : root(std::exchange(that.root, nullptr)) {}
        
bool Set::empty() {
    return root == nullptr;
// }

int Set::size() {
    return size(root);
}

int Set::size(Node* x) const {
    if (x == nullptr) return 0;
    return x->size;
}

int Set::height() {
    return height(root);
}

int Set::height(Node* x) const {
    if (x == nullptr) return -1;
    return x->height;
}

Node* Set::contains(Node* x, int value) const {
    if (x == nullptr) return NULL;
    if (value < x->value) return contains(x->left, value);
    else if (value > x->value) return contains(x->right, value);
    else return x;
}

bool Set::contains(int value) const {
    return contains(root, value) != NULL;
}

void Set::insert(int value) {
    root = insert(root, value);
}

Node* Set::insert(Node* x, int value) {
    if (x == nullptr) return new Node(value, 0, 1);
    if (value < x->value) {
        x->left = insert(x->left, value);
    } else if (value > x->value) {
        x->right = insert(x->right, value);
    } else {
        return x; // set contains only unique entries
    }
    
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    return balance(x);
}

Node* Set::balance(Node* x) {
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

int Set::factor(Node* x) {
    return height(x->left) - height(x->right);
}

Node* Set::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    y->size = x->size;
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    return y;
}

Node* Set::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    y->size = x->size;
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    return y;
}

void Set::remove(int value) {
    if (!contains(value)) return;
    root = remove(root, value);
}

Node* Set::remove(Node* x, int value) {
    if (x == nullptr) return nullptr;
    
    if (value < x->value) {
        x->left = remove(x->left, value);
    } else if(value > x->value) {
        x->right = remove(x->right, value);
    } else {
        Node* temp;
        
        if      (x->left  == nullptr) temp = x->right;
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
        x->size = 1 + size(x->left) + size(x->right);
        x->height = 1 + std::max(height(x->left), height(x->right));
    }
    return balance(x);
}

void Set::removeMin() {
    if (empty()) return;
    root = removeMin(root);
}

Node* Set::removeMin(Node* x) {
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
      x->height = std::max(height(x->left), height(x->right)) + 1;
      x->size = size(x->left) + size(x->right) + 1;
    }
    return balance(x);
}

Node* Set::min(Node* x) {
    if (x->left == nullptr) return x;
    return min(x->left);
}

// output functions
void Set::inorder() {
    inorder(root);
}

void Set::inorder(Node* x) {
    if (x != nullptr) {
        inorder(x->left);
        std::cout << x->value << ", ";
        inorder(x->right);
    }
}

std::vector<int> Set::items() const {
    std::vector<int> items;
    getItems(root, items);
    return items;
}

void Set::getItems(Node* x, std::vector<int>& items) const {
    if (x != NULL) {
        getItems(x->left, items);
        items.push_back(x->value);
        getItems(x->right, items);
    }
}
// operators
Set& Set::operator=(Set that) {
    swap(*this, that);
    return *this;
}

Set& Set::operator>>(int i) {
    this->remove(i);
    return *this;
}
        
Set& Set::operator<<(int i) {
    this->insert(i);
    return *this;
}
        
Set& Set::operator+=(const Set& that) {
    Set res = *this + that;
    swap(*this, res);
    return *this;
}

Set operator+(const Set& a, const Set& b) {
    Set result;
    std::vector<int> itb = b.items(), ita = a.items();
    for (int i : ita) result.insert(i);
    for (int i : itb) result.insert(i);
    return result;
}

Set& Set::operator*=(const Set& that) {
    Set temp = *this * that;
    swap(*this, temp);
    return *this;
}

Set operator*(const Set& a, const Set& b) {
    Set result;

    std::vector<int> it = a.items();
    for (int i : it) if (b.contains(i)) result.insert(i);
    return result;
}
        
Set operator-(const Set& a, const Set& b) {
    Set result;

    std::vector<int> it = a.items();
    for (int i : it) if (!b.contains(i)) result.insert(i);
    return result;
}
        
Set& Set::operator-=(const Set& that) {
    Set temp = *this - that;
    swap(*this, temp);
    return *this;
}
        
void swap(Set& a, Set& b) {
    std::swap(a.root, b.root);
}