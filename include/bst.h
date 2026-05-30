// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <utility>
#include <vector>

template<typename T>

class BST {
 private:
  struct Node {
    T info;
    int count;
    Node* left;
    Node* right;
  };
  Node* top;

Node* createNode(const T& val) {
    Node* newNode = new Node;
    newNode->info = val;
    newNode->count = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
  }

Node* connect(Node* curr, const T& val) {
    if (curr == nullptr) {
      return createNode(val);
    }
    if (val < curr->info) {
      curr->left = connect(curr->left, val);
    } else if (val > curr->info) {
      curr->right = connect(curr->right, val);
    } else {
      curr->count++;
    }
    return curr;
  }

void collectData(Node* curr,
                   std::vector<std::pair<T, int>>& buf) {
    if (curr == nullptr) {
      return;
    }
    collectData(curr->left, buf);
    buf.push_back({curr->info, curr->count});
    collectData(curr->right, buf);
  }

void deleteAll(Node* curr) {
    if (curr == nullptr) {
      return;
    }
    deleteAll(curr->left);
    deleteAll(curr->right);
    delete curr;
  }

int findCount(Node* curr, const T& val) const {
    if (curr == nullptr) {
      return 0;
    }
    if (curr->info == val) {
      return curr->count;
    }
    if (val < curr->info) {
      return findCount(curr->left, val);
    } else {
      return findCount(curr->right, val);
    }
  }

int computeHeight(Node* curr) const {
    if (curr == nullptr) {
      return -1;
    }
    int leftH = computeHeight(curr->left);
    int rightH = computeHeight(curr->right);
    return 1 + (leftH > rightH ? leftH : rightH);
  }

 public:
  BST() : top(nullptr) {}
  ~BST() {
    deleteAll(top);
  }

void insert(const T& val) {
    top = connect(top, val);
  }

int depth() const {
    return computeHeight(top);
  }

int search(const T& val) const {
    return findCount(top, val);
  }

void collectInfo(std::vector<std::pair<T, int>>& out) {
    collectData(top, out);
  }
};

#endif  // INCLUDE_BST_H_
