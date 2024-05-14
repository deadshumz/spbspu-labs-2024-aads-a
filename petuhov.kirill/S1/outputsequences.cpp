#include "outputsequences.hpp"
#include <iostream>
#include <string>
#include "list.hpp"

namespace petuhov
{
  void outputSequences(std::ostream& out, const List< std::pair< std::string, List< int > > >& sequences, List< int >& sums)
  {
    int max_length = 0;
    for (auto seq_it = sequences.cbegin(); seq_it != sequences.cend(); ++seq_it)
    {
      int length = 0;
      for (auto num_it = seq_it->second.cbegin(); num_it != seq_it->second.cend(); ++num_it)
      {
        ++length;
      }
      if (length > max_length)
      {
        max_length = length;
      }
    }

    List< List< int > > columns;
    for (int i = 0; i < max_length; ++i)
    {
      List< int > column;
      for (auto seq_it = sequences.cbegin(); seq_it != sequences.cend(); ++seq_it)
      {
        auto num_it = seq_it->second.cbegin();
        for (int j = 0; j < i; ++j)
        {
          if (num_it != seq_it->second.cend())
          {
            ++num_it;
          }
        }
        if (num_it != seq_it->second.cend())
        {
          column.push_front(*num_it);
        }
        else
        {
          column.push_front(-1); // заменим -1 на какой-то другой маркер, если -1 может быть в данных
        }
      }
      column.reverse();
      columns.push_front(column);
    }

    columns.reverse();

    for (auto col_it = columns.cbegin(); col_it != columns.cend(); ++col_it)
    {
      int sum = 0;
      bool first = true;
      bool has_numbers = false;
      for (auto num_it = col_it->cbegin(); num_it != col_it->cend(); ++num_it)
      {
        if (*num_it != -1) // проверяем на маркер
        {
          if (!first)
          {
            out << " ";
          }
          out << *num_it;
          sum += *num_it;
          has_numbers = true;
          first = false;
        }
      }
      if (has_numbers)
      {
        sums.push_front(sum);
        out << "\n";
      }
    }
    sums.reverse();
  }
}
