#include <iostream>
#include <fstream>

#include <list>

#include "list.hpp"
#include "getSeqFromStream.hpp"
#include "outputSeqs.hpp"

#include "outputList.hpp"

int main()
{
  getSeqFromStream(sequences, std::cin);
  if (sequences.empty())
  {
    std::cout << "0\n";
    return 0;
  }
  sequences.back().second.assign(4, 52);
  try
  {
    outputSeqs(sequences, std::cout);
    std::cout << "\n";
  }
  catch (const std::overflow_error &e)
  {
    std::cerr << "Error has occured: " << e.what();
    return 1;
  }
}
