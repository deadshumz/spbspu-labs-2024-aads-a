#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <stack>

namespace petuhov
{
  template <typename Key, typename Value>
  class AVLTree; // Forward declaration of AVLTree

  template <typename Key, typename Value>
  class Iterator
  {
  public:
    using Node = typename AVLTree<Key, Value>::Node;

    Iterator(Node *root = nullptr) { traverseToLeftmost(root); }

    bool operator!=(const Iterator &other) const
    {
      return !(*this == other);
    }

    bool operator==(const Iterator &other) const
    {
      return !nodeStack.empty() && other.nodeStack.empty() ? false : nodeStack.empty() && other.nodeStack.empty();
    }

    std::pair<Key, Value> &operator*()
    {
      Node *node = nodeStack.top();
      return std::make_pair(node->key, node->value);
    }

    Iterator &operator++()
    {
      Node *node = nodeStack.top();
      nodeStack.pop();
      traverseToLeftmost(node->right);
      return *this;
    }

  private:
    std::stack<Node *> nodeStack;

    void traverseToLeftmost(Node *node)
    {
      while (node != nullptr)
      {
        nodeStack.push(node);
        node = node->left;
      }
    }
  };
}

#endif
