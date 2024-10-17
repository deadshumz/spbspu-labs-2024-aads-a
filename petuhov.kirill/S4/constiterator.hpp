#ifndef CONST_ITERATOR_HPP
#define CONST_ITERATOR_HPP

#include <stack>

namespace petuhov
{
  template <typename Key, typename Value>
  class AVLTree;

  template <typename Key, typename Value>
  class ConstIterator
  {
  public:
    using Node = typename AVLTree<Key, Value>::Node;

    ConstIterator(const Node *root = nullptr) { traverseToLeftmost(root); }

    bool operator!=(const ConstIterator &other) const
    {
      return !(*this == other);
    }

    bool operator==(const ConstIterator &other) const
    {
      return nodeStack.empty() && other.nodeStack.empty();
    }

    const std::pair<Key, Value> &operator*() const
    {
      const Node *node = nodeStack.top();
      return std::make_pair(node->key, node->value);
    }

    ConstIterator &operator++()
    {
      const Node *node = nodeStack.top();
      nodeStack.pop();
      traverseToLeftmost(node->right);
      return *this;
    }

  private:
    std::stack<const Node *> nodeStack;

    void traverseToLeftmost(const Node *node)
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
