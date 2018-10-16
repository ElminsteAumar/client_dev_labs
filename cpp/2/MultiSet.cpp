#include "MultiSet.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

bool MultiSet::empty() {
    return root == NULL;
}

int MultiSet::size() {
    return size(root);
}

int MultiSet::size(Node* x) {
    if (x == NULL) return 0;
    //std::cout << x << std::endl;
    return x->size;
}

int MultiSet::height() {
    return height(root);
}

int MultiSet::height(Node* x) {
    if (x == NULL) return -1;
    return x->height;
}

Node* MultiSet::contains(Node* x, int value) {
    if (x == NULL) return NULL;
    if (value < x->value) return contains(x->left, value);
    else if (value > x->value) return contains(x->right, value);
    else return x;
}

bool MultiSet::contains(int value) {
    return contains(root, value) != NULL;
}

void MultiSet::insert(int value) {
    root = insert(root, value);
}

Node* MultiSet::insert(Node* x, int value) {
    if (x == NULL) return new Node(value, 0, 1);
    if (value < x->value) {
        x->left = insert(x->left, value);
    } else if (value >= x->value) {
        x->right = insert(x->right, value);
    }
    
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    return balance(x);
}

Node* MultiSet::balance(Node* x) {
    if (factor(x) < -1) {
        if (factor(x->right) > 0) {
            x->right = rotateRight(x->right);
        }
        x = rotateLeft(x);
    } else if (factor(x) > 1) {
        if (factor(x->left) < 0) {
            x->left = rotateLeft(x->left);
        }
        x = rotateRight(x);
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
    if (value < x->value) {
        x->left = remove(x->left, value);
    } else if(value > x->value) {
        x->right = remove(x->right, value);
    } else {
        if (x->left == NULL) {
            return x->right;
        } else if (x->right == NULL) {
            return x->left;
        } else {
            Node* y = x;
            x = min(y->right);
            x->right = removeMin(y->right);
            x->left = y->left;
        }
    }
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    return balance(x);
}

void MultiSet::removeMin() {
    if (empty()) return;
    root = removeMin(root);
}

Node* MultiSet::removeMin(Node* x) {
    if (x->left == NULL) return x->right;
    x->left = removeMin(x->left);
    x->size = 1 + size(x->left) + size(x->right);
    x->height = 1 + std::max(height(x->left), height(x->right));
    return balance(x);
}

Node* MultiSet::min(Node* x) {
    if (x->left == NULL) return x;
    return min(x->left);
}

void MultiSet::inorder() {
    inorder(root);
    std::cout << std::endl;
}

Node* MultiSet::inorder(Node* x) {
    if (x != NULL) {
        inorder(x->left);
        std::cout << x->value << " ";
        inorder(x->right);
    }
}

std::vector<int> MultiSet::items() const {
    std::vector<int> items;
    Node* cur = root;
    getItems(cur, items);
    
    delete cur;
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
MultiSet& MultiSet::operator<<(int value) {
    this->insert(value);
    return (*this);
}

MultiSet& MultiSet::operator>>(int value) {
    this->remove(value);
    return (*this);
}

MultiSet MultiSet::operator+(const MultiSet& ms) {
    std::vector<int> items1 = this->items(), items2 = ms.items();
    std::vector<int> united;
    
    // create united vectors
    united.reserve(items1.size() + items2.size());
    united.insert(united.end(), items1.begin(), items1.end());
    united.insert(united.end(), items2.begin(), items2.end());
    
    MultiSet sum;
    
    for (int i = 0; i < united.size(); i++) {
        sum.insert(united[i]);
    }
    sum;
    return sum;
}

MultiSet MultiSet::operator*(const MultiSet& ms) {
    std::vector<int> items1 = this->items(), items2 = ms.items();
    std::vector<int> united;
    
    // create united vectors
    united.reserve(items1.size() + items2.size());
    united.insert(united.end(), items1.begin(), items1.end());
    united.insert(united.end(), items2.begin(), items2.end());
    
    MultiSet diverse;
    
    for (int i = 0; i < united.size(); i++) {
        int x = united[i];
        if (std::find(items1.begin(), items1.end(), x) != items1.end() && std::find(items2.begin(), items2.end(), x) != items2.end()) {
            diverse.insert(x);
        }
    }
    diverse;
    return diverse;
}

MultiSet MultiSet::operator-(const MultiSet& ms) {
    std::vector<int> items1 = this->items(), items2 = ms.items();
    std::vector<int> united;
    
    // create united vectors
    united.reserve(items1.size() + items2.size());
    united.insert(united.end(), items1.begin(), items1.end());
    united.insert(united.end(), items2.begin(), items2.end());
    
    MultiSet diff;
    
    for (int i = 0; i < united.size(); i++) {
        int x = united[i];
        if (std::find(items1.begin(), items1.end(), x) != items1.end() &&
            std::find(items2.begin(), items2.end(), x) == items2.end()) {
            diff.insert(x);
        }
    }
    return diff;
}

MultiSet& MultiSet::operator+=(const MultiSet& ms) {
    std::vector<int> items1 = this->items(), items2 = ms.items();
    std::vector<int> united;
    
    // create united vectors
    united.reserve(items1.size() + items2.size());
    united.insert(united.end(), items1.begin(), items1.end());
    united.insert(united.end(), items2.begin(), items2.end());
    
    MultiSet sum;
    
    for (int i = 0; i < united.size(); i++) {
        sum.insert(united[i]);
    }
    *this = sum;
    return (*this);
}

MultiSet& MultiSet::operator*=(const MultiSet& ms) {
    std::vector<int> items1 = this->items(), items2 = ms.items();
    std::vector<int> united, diverse;
    
    // create united vectors
    united.reserve(items1.size() + items2.size());
    united.insert(united.end(), items1.begin(), items1.end());
    united.insert(united.end(), items2.begin(), items2.end());
    
    for (int i = 0; i < united.size(); i++) {
        int x = united[i];
        if (std::find(items1.begin(), items1.end(), x) != items1.end() && std::find(items2.begin(), items2.end(), x) != items2.end()) {
            diverse.push_back(x);
        }
    }
    for (int i = 0; i < items1.size(); i++) this->remove(items1[i]);
    for (int i = 0; i < diverse.size(); i++) this->insert(diverse[i]);
    return (*this);
}

MultiSet& MultiSet::operator-=(const MultiSet& ms) {
    std::vector<int> items1 = this->items(), items2 = ms.items();
    std::vector<int> united, diff;
    
    // create united vectors
    united.reserve(items1.size() + items2.size());
    united.insert(united.end(), items1.begin(), items1.end());
    united.insert(united.end(), items2.begin(), items2.end());

    for (int i = 0; i < united.size(); i++) {
        int x = united[i];
        if (std::find(items1.begin(), items1.end(), x) != items1.end() &&
            std::find(items2.begin(), items2.end(), x) == items2.end()) {
            diff.push_back(x);
        }
    }
    
    for (int i = 0; i < items1.size(); i++) this->remove(items1[i]);
    for (int i = 0; i < diff.size(); i++) this->insert(diff[i]);
    return (*this);
}

MultiSet::operator Set() {
    std::vector<int> items = this->items();
    std::cout << items.size() <<" SIZE " << std::endl;
    Set set;
    for (int i = 0; i < items.size(); i++) set.insert(items[i]);
    return set;
}