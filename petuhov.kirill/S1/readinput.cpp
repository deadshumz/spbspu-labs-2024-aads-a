#include "readinput.hpp"
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <string>
#include "list.hpp"

namespace petuhov
{
  void readInput(List< std::pair< std::string, List< size_t > > > &sequences, const std::string &input)
  {
    size_t start = 0;
    size_t end = input.find('\n');

    while (end != std::string::npos)
    {
      std::string line = input.substr(start, end - start);
      size_t pos = 0;

      while (pos < line.size() && line[pos] != ' ')
      {
        ++pos;
      }
      std::string name = line.substr(0, pos);

      List< size_t > numbers;
      while (pos < line.size())
      {
        while (pos < line.size() && line[pos] == ' ')
        {
          ++pos;
        }

        size_t num_start = pos;
        while (pos < line.size() && line[pos] != ' ')
        {
          ++pos;
        }

        if (num_start < pos)
        {
          size_t num = std::stoull(line.substr(num_start, pos - num_start));
          numbers.push_front(num);
        }
      }

      numbers.reverse();
      sequences.push_front(std::make_pair(name, numbers));

      start = end + 1;
      end = input.find('\n', start);
    }

    sequences.reverse();
  }
}
