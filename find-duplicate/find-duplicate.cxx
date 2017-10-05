// find-duplicates.cxx 

  #include "mock-util.h"

  using namespace mock::util;

  int main(void) 
  {
    // an unsorted array known to contain at least one duplicate
    std::array<element_t, 13> xs = { 1, 2, 3, 4, 5, 6, 7, 7, 9, 10, 11, 12, 13 };

    // histogram
    std::map<element_t, std::size_t> hist;
    const element_t lo = 0;
    const element_t hi = 1;

    // initialize search range
    const Range<std::size_t> range(0, xs.size());

    for(auto &x : Slice<element_t>(xs.data(), range))
    {
      hist.count(x) ?  ++hist[x] : hist[x] = 1;
    } // each element in subrange

    for(auto &x : hist) 
    {
      if(x.second > 1) std::cerr << x.first << std::endl;
    } // each bin

  } // main

// *EOF
