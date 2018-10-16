#ifndef SET_HPP
#define SET_HPP

#include <stdlib.h>
#include <vector>
#include <list>
#include <utility>
#include <iostream>

template<typename T>
class Set {
    struct Node {
        T value;
        Node* left = nullptr;
        Node* right = nullptr;
        int height = 0;
        std::size_t size = 1;

        Node() = delete;

        Node(const T& key) : value(key)
        { }

        Node(T&& key) : value(std::move(key))
        { }

        Node& operator=(Node node) = delete;

        ~Node() {
            auto l = left, r = right;
            left = right = nullptr;
            delete l;
            delete r;
        }
    };

    Node* root;
    
    static void inorder(const Node* node, std::list<T>& items) {
        if (node == nullptr) return;
        inorder(node->left, items);
        items.push_back(node->value);
        inorder(node->right, items);
    }
    
    static std::size_t size(const Node* node) noexcept {
        return node == nullptr ? 0 : node->size;
    }

    static int height(const Node* node) noexcept {
        return node == nullptr ? -1 : node->height;
    }

    static Node* min(Node* node) noexcept {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) node = node->left;
        return node;
    }
    
    static Node* removeMin(Node* node) {
        if (node == nullptr) return nullptr;

        if (node->left != nullptr)
            node->left = removeMin(node->left);
        else {
            Node* temp = node->right;
            node->right = nullptr;
            delete node;
            node = temp;
        }

        if (node != nullptr) {
            node->height = std::max(height(node->left), height(node->right)) + 1;
            node->size = size(node->left) + size(node->right) + 1;
        }

        return balance(node);
    }
    
    static int factor(const Node* node) noexcept {
        return height(node->left) - height(node->right);
    }
    
    static Node* rotateLeft(Node* node) noexcept {
        Node* temp = node->right;
        node->right = temp->left;
        temp->left = node;
        temp->size = node->size;
        node->size = size(node->left) + size(node->right) + 1;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        temp->height = std::max(height(temp->left), height(temp->right)) + 1;
        return temp;
    }

    static Node* rotateRight(Node* node) noexcept {
        Node* temp = node->left;
        node->left = temp->right;
        temp->right = node;
        temp->size = node->size;
        node->size = size(node->left) + size(node->right) + 1;
        node->height = std::max(height(node->left), height(node->right)) + 1;
        temp->height = std::max(height(temp->left), height(temp->right)) + 1;
        return temp;
    }
    
    static Node* balance(Node* node) noexcept {
        if (node == nullptr) return nullptr;

        if (factor(node) > 1) {
        if (factor(node->left) < 0)
            node->left = rotateLeft(node->left);
        node = rotateRight(node);
        } else if (factor(node) < -1) {
        if (factor(node->right) > 0)
            node->right = rotateRight(node->right);
        node = rotateLeft(node);
        }

        return node;
    }
    
    Node* insert(Node* node, T value) {
        if (node == nullptr) return new Node(value);

        if (value < node->value)
            node->left = insert(node->left, value);
        else if (value > node->value)
            node->right = insert(node->right, value);
        else return node;

        node->height = std::max(height(node->left), height(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
        return balance(node);
    }
    
    Node* remove(Node* node, const T& value) {
        if (node == nullptr) return nullptr;

        if (value < node->value)
            node->left = remove(node->left, value);
        else if (value > node->value)
            node->right = remove(node->right, value);
        else {
            Node* temp;

            if      (node->left  == nullptr) temp = node->right;
            else if (node->right == nullptr) temp = node->left;
            else {
                node->value = min(node->right)->value;
                node->right = removeMin(node->right);
                temp = node;
                node = nullptr;
            }

            if (node != nullptr) node->left = node->right = nullptr;
            delete node;
            node = temp;
        }

        if (node != nullptr) {
            node->height = std::max(height(node->left), height(node->right)) + 1;
            node->size = size(node->left) + size(node->right) + 1;
        }

        return balance(node);
    }
public:
    explicit Set() : root(nullptr) {}
    
    Set(const Set& that) { *this += that; }
    Set(Set&& that) : root(std::exchange(that.root, nullptr)) { }
    Set& operator=(Set that) {
        swap(*this, that);
        return *this;
    }
    ~Set() {
        Node* temp = root;
        root = nullptr;
        delete temp;
    }
    
    friend void swap(Set& a, Set& b) noexcept {
        std::swap(a.root, b.root);
    }
    
    void insert(const T& value) {
        root = insert(root, value);
    }
    
    bool contains(const T& value) const noexcept {
        Node* node = root;

        while (node != nullptr) {
            if (value < node->value)
                node = node->left;
            else if (value > node->value)
                node = node->right;
            else return true;
        }

        return false;
    }

    std::size_t size() const noexcept {
        return size(root);
    }

    bool empty() const noexcept {
        return size() == 0;
    }
    
    Set& operator+=(const Set& that) {
        std::list<T> items;
        inorder(that.root, items);
        for (T item : items) insert(item);
        return *this;
    }
    
    void remove(const T& value) {
        root = remove(root, value);
    }
    
    void inorder(Node* node) const noexcept {
        if (node != nullptr) {
            inorder(node->left);
            std::cout << node->value << " ";
            inorder(node->right);
        }
    }
    void inorder() const noexcept {
        inorder(root);
    }
};


#endif