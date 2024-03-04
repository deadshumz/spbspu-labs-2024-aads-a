#ifndef LIST_HPP
#define LIST_HPP
#include <utility>
#include <cstddef>
#include <string>
#include "iterator.hpp"
#include "functions.hpp"
#include "node.hpp"

namespace zakozhurnikova
{
  template <typename T>
  using predicateFunction = bool (*)(T);

  template <typename T>
  class List
  {
  public:
    List() :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {}

    List(const List& rhs) :
      head_(nullptr),
      tail_(nullptr),
      size_(0)
    {
      Node< T >* temp = rhs.head_;
      while (temp)
      {
        push(temp->data);
        temp = temp->next;
      }
    }

    List(List&& rhs) noexcept :
      head_(rhs.head_),
      tail_(rhs.tail_),
      size_(size_)
    {
      rhs.head_ = nullptr;
      rhs.tail_ = nullptr;
    }

    List& operator=(const List& rhs)
    {
      if (this != &rhs)
      {
        List temp(rhs);
        clear();
        head_ = temp.head_;
        tail_ = temp.tail_;
      }
      return *this;
    }

    List operator=(List&& rhs) noexcept
    {
      if (this != &rhs)
      {
        swap(rhs);
      }
      return this;
    }

    ~List()
    {
      clear();
    }

    void push(T data)
    {
      Node< T >* temp = new Node< T >{ data };

      if (!tail_)
      {
        tail_ = temp;
        head_ = temp;
      }
      else
      {
        tail_->next = temp;
        temp->prev = tail_;
        tail_ = temp;
      }
      ++size_;
    }

    void pop() noexcept
    {
      Node< T >* toDelete = tail_;
      tail_ = tail_->prev;
      if (!tail_)
      {
        head_ = nullptr;
        tail_ = nullptr;
      }
      else
      {
        tail_->next = nullptr;
      }
      delete toDelete;
      --size_;
    }

    size_t size() const
    {
      return size_;
    }

    void clear() noexcept
    {
      while (tail_)
      {
        pop();
      }
      head_ = nullptr;
    }

    bool empty() noexcept
    {
      return size_ == 0;
    }

    void swap(List& rhs) noexcept
    {
      std::swap(head_, rhs.head_);
      std::swap(tail_, rhs.tail_);
      std::swap(size_, rhs.size_);
    }

    void remove(const T& value)
    {
      Iterator<T> first = begin();
      Iterator<T> last = end();
      for (Iterator<T> it = first; it != last; ++it)
      {
        if (*it != value)
        {
          *first++ = std::move(*it);
        }
      }
    }

    void remove_if(predicateFunction<T> p)
    {
      auto first = begin();
      auto last = end();
      for (auto it = first; it != last; ++it)
      {
        if (!p(*(it)))
        {
          *first++ = std::move(*it);
        }
      }
    }

    void assign(Iterator<T> first, Iterator<T> last, const T& value)
    {
      fill(first, last, value);
    }

  private:
    Node< T >* head_;
    Node< T >* tail_;
    size_t size_;
  };
}
