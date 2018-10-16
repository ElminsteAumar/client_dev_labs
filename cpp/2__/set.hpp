#ifndef _SET_HPP_
#define _SET_HPP_

#include <utility>
#include <list>
#include <functional>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <cassert>

template <typename Key, typename Comparator = std::less<Key>>
class Set {
  struct Node {
    Key val;
    Node* left = nullptr;
    Node* right = nullptr;
    int height = 0;
    std::size_t size = 1;

    Node() = delete;

    Node(const Key& key) : val(key)
    { }

    Node(Key&& key) : val(std::move(key))
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
  Comparator comp;

  static void inorder(const Node* node, std::list<std::reference_wrapper<const Key>>& list) {
    if (node == nullptr) return;
    inorder(node->left, list);
    list.push_back(node->val);
    inorder(node->right, list);
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

  static Node* max(Node* node) noexcept {
    if (node == nullptr) return nullptr;
    while (node->right != nullptr) node = node->right;
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

  static Node* removeMax(Node* node) {
    if (node == nullptr) return nullptr;

    if (node->right != nullptr)
      node->right = removeMax(node->right);
    else {
      Node* temp = node->left;
      node->left = nullptr;
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

  bool check(const Node* node, const Node* min = nullptr, const Node* max = nullptr) const noexcept {
    if (node == nullptr) return true;

    int h = std::max(height(node->left), height(node->right)) + 1;
    if (node->height != h) return false;

    std::size_t s = size(node->left) + size(node->right) + 1;
    if (node->size != s) return false;

    if (min != nullptr && !comp(min->val, node->val)) return false;
    if (max != nullptr && !comp(node->val, max->val)) return false;

    return check(node->left, min, node) && check(node->right, node, max);
  }

  template <typename T>
  Node* insert(Node* node, T&& key) {
    if (node == nullptr) return new Node(std::forward<T>(key));

    if (comp(key, node->val))
      node->left = insert(node->left, std::forward<T>(key));
    else if (comp(node->val, key))
      node->right = insert(node->right, std::forward<T>(key));
    else return node;

    node->height = std::max(height(node->left), height(node->right)) + 1;
    node->size = size(node->left) + size(node->right) + 1;
    return balance(node);
  }

  Node* remove(Node* node, const Key& key) {
    if (node == nullptr) return nullptr;

    if (comp(key, node->val))
      node->left = remove(node->left, key);
    else if (comp(node->val, key))
      node->right = remove(node->right, key);
    else {
      Node* temp;

      if      (node->left  == nullptr) temp = node->right;
      else if (node->right == nullptr) temp = node->left;
      else {
        node->val = std::move(min(node->right)->val);
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
  explicit Set(const Comparator& cmp = Comparator())
    : root(nullptr), comp(cmp)
  { }

  Set(const Set& that) : Set(that.comp) {
    *this += that;
  }

  Set(Set&& that) :
    root(std::exchange(that.root, nullptr)),
    comp(std::move(that.comp))
  { }

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
    using std::swap;
    swap(a.root, b.root);
    swap(a.comp, b.comp);
  }

  void insert(const Key& key) {
    root = insert(root, key);
    assert(check(root));
  }

  void insert(Key&& key) {
    root = insert(root, std::move(key));
    assert(check(root));
  }

  bool contains(const Key& key) const noexcept {
    Node* node = root;

    while (node != nullptr) {
      if (comp(key, node->val))
        node = node->left;
      else if (comp(node->val, key))
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
    std::list<std::reference_wrapper<const Key>> list;
    inorder(that.root, list);
    for (const Key& key : list) insert(key);
    assert(check(root));
    return *this;
  }

  friend Set operator+(Set a, const Set& b) {
    return a += b;
  }

  Set& operator*=(const Set& that) {
    Set temp = *this * that;
    swap(*this, temp);
    return *this;
  }

  friend Set operator*(const Set& lhs, const Set& rhs) {
    Set result;
    bool min = lhs.size() < rhs.size();

    const Set& a = min ? lhs : rhs;
    const Set& b = min ? rhs : lhs;

    std::list<std::reference_wrapper<const Key>> list;
    inorder(a.root, list);
    for (const Key& key : list)
      if (b.contains(key)) result.insert(key);

    assert(result.check(result.root));
    return result;
  }

  Set& operator-=(const Set& that) {
    Set temp = *this - that;
    swap(*this, temp);
    return *this;
  }

  friend Set operator-(const Set& lhs, const Set& rhs) {
    Set result;
    std::list<std::reference_wrapper<const Key>> list;
    inorder(lhs.root, list);
    for (const Key& key : list)
      if (!rhs.contains(key)) result.insert(key);

    assert(result.check(result.root));
    return result;
  }

  friend std::ostream& operator<<(std::ostream& out, const Set& set) {
    std::list<std::reference_wrapper<const Key>> list;
    inorder(set.root, list);
    out << "{ ";
    std::copy(list.begin(), list.end(), std::ostream_iterator<Key>(out, " "));
    out << "}";
    return out;
  }

  void remove(const Key& key) {
    root = remove(root, key);
    assert(check(root));
  }
};

#endif