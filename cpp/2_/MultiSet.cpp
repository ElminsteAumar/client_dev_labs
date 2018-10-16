#include "MultiSet.hpp"
#include <iostream>
#include <vector>

// Multiset

MultiSet::MultiSet() : root(nullptr) { }
MultiSet::~MultiSet() {
    Node* temp = root;
    root = nullptr;
    delete temp;
}

MultiSet::MultiSet(const MultiSet& that) { *this += that; }
MultiSet::MultiSet(MultiSet&& that) : root(std::exchange(that.root, nullptr)) { }
        
bool MultiSet::empty() {
    return root == nullptr;
}

int MultiSet::size() const {
    return size(root);
}

int MultiSet::size(Node* x) const {
    if (x == nullptr) return 0;
    return x->size;
}

int MultiSet::height() {
    return height(root);
}

int MultiSet::height(Node* x) {
    if (x == nullptr) return -1;
    return x->height;
}

Node* MultiSet::contains(Node* x, int value) const {
    if (x == nullptr) return NULL;
    if (value < x->value) return contains(x->left, value);
    else if (value > x->value) return contains(x->right, value);
    else return x;
}

bool MultiSet::contains(int value) const {
    return contains(root, value) != NULL;
}

void MultiSet::insert(int value) {
    root = insert(root, value);
}

Node* MultiSet::insert(Node* x, int value) {
    if (x == nullptr) return new Node(value, 0, 1);
    if (value < x->value) {
        x->left = insert(x->left, value);
    } else {
        x->right = insert(x->right, value);
    }
    
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    return balance(x);
}

Node* MultiSet::balance(Node* x) {
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

int MultiSet::factor(Node* x) {
    return height(x->left) - height(x->right);
}

Node* MultiSet::rotateRight(Node* x) {
    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    y->size = x->size;
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    return y;
}

Node* MultiSet::rotateLeft(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    y->size = x->size;
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    y->height = 1 + std::max(height(y->left), height(y->right));
    return y;
}

void MultiSet::remove(int value) {
    if (!contains(value)) return;
    root = remove(root, value);
}

Node* MultiSet::remove(Node* x, int value) {
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

void MultiSet::removeMin() {
    if (empty()) return;
    root = removeMin(root);
}

Node* MultiSet::removeMin(Node* x) {
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

Node* MultiSet::min(Node* x) {
    if (x->left == nullptr) return x;
    return min(x->left);
}

void MultiSet::inorder() {
    inorder(root);
}

void MultiSet::inorder(Node* x) {
    if (x != nullptr) {
        inorder(x->left);
        std::cout << x->value << ", ";
        inorder(x->right);
    }
}

std::vector<int> MultiSet::items() const {
    std::vector<int> items;
    getItems(root, items);
    return items;
}

void MultiSet::getItems(Node* x, std::vector<int>& items) const {
    if (x != NULL) {
        getItems(x->left, items);
        items.push_back(x->value);
        getItems(x->right, items);
    }
}

// operators
MultiSet& MultiSet::operator=(MultiSet that) {
    swap(*this, that);
    return *this;
}

MultiSet& MultiSet::operator>>(int i) {
    this->remove(i);
    return *this;
}
        
MultiSet& MultiSet::operator<<(int i) {
    this->insert(i);
    return *this;
}
    
MultiSet& MultiSet::operator+=(const MultiSet& that) {
    std::vector<int> it = that.items();
    for (int i : it) insert(i);
    return *this;
}

MultiSet operator+(MultiSet a, const MultiSet& b) {
    return a += b;
}

MultiSet& MultiSet::operator*=(const MultiSet& that) {
    MultiSet temp = *this * that;
    swap(*this, temp);
    return *this;
}

MultiSet operator*(const MultiSet& a, const MultiSet& b) {
    MultiSet result;

    std::vector<int> it = a.items();
    for (int i : it) if (b.contains(i)) result.insert(i);
    return result;
}
        
void swap(MultiSet& a, MultiSet& b) {
    std::swap(a.root, b.root);
}

MultiSet& MultiSet::operator-=(const MultiSet& that) {
    MultiSet temp = *this - that;
    swap(*this, temp);
    return *this;
}

MultiSet::operator Set() {
    std::vector<int> it = this->items();
    Set temp;
    for (int i : it) temp.insert(i);
    return temp;
}

MultiSet operator-(const MultiSet& lhs, const MultiSet& rhs) {
    MultiSet result;
    
    std::vector<int> it = lhs.items();
    for (int i : it) if (!rhs.contains(i)) result.insert(i);
    return result;
}
