#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <stdexcept>
#include "iterator.hpp"
#include "const_iterator.hpp"

namespace petuhov
{
  template <typename Key, typename Value, typename Compare = std::less<Key>>
  class AVLTree
  {
  private:
    struct Node
    {
      Key key;
      Value value;
      Node *left;
      Node *right;
      int height;

      Node(Key k, Value v);
    };

    Node *root;
    Compare compare;
    int node_count;

    int height(Node *node) const;
    int getBalance(Node *node) const;

    Node *rotateRight(Node *y);
    Node *rotateLeft(Node *x);

    Node *insert(Node *node, Key key, Value value);
    Node *find(Node *node, Key key) const;
    Node *erase(Node *node, Key key);
    Node *findMin(Node *node) const;
    void clear(Node *node);
    void swap(Node *&a, Node *&b);

    Node *copyTree(Node *node) const;

  public:
    AVLTree();
    ~AVLTree() = default;

    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&other) noexcept;

    Iterator begin();
    Iterator end();
    ConstIterator begin() const;
    ConstIterator end() const;

    int size() const;
    bool empty() const;

    Value get(Key key) const;

    void clear();
    void swap(AVLTree &other);

    void push(Key key, Value value);
    void drop(Key key);
    bool find(Key key) const;

    void insert(Key key, Value value);
    void erase(Key key);
    void erase(Iterator position);

    std::pair<Iterator, Iterator> equal_range(Key key);
    int count(Key key) const;
  };
}

#endif
