// mock-util.h

  #include <iterator>
  #include <iostream>
  #include <sys/types.h>
  #include <array>
  #include <map>
  #include <cmath>
  #include <algorithm>
  #include <assert.h>

  namespace mock::util {

    // default element type (domain)
    typedef uint64_t element_t;

    // represents lower and upper bounds
    template<typename T>
    struct Range
    {
      T lo_;
      T hi_;
      Range(T lo, T hi) 
       : lo_(lo), hi_(hi) {};
    };

    // represents a slice of an array
    template<typename T>
    struct Slice
    {
      T* data_;
      std::size_t n_;
      std::size_t lo_;
      std::size_t hi_;
      std::size_t* begin() { return data_ + lo_; }
      std::size_t* end() { return data_ + hi_; }
      Slice(T *data, std::size_t lo, std::size_t hi) 
       : data_(data), n_(hi-lo), lo_(lo), hi_(hi) {};
      Slice(T *data, const Range<std::size_t> &range)
       : data_(data), n_(range.hi_-range.lo_), lo_(range.lo_), hi_(range.hi_) {};
    };

    // identify a pivot element, partitioning the array into two subarrays
    auto make_pivot = [](element_t lo, element_t hi) -> element_t { return std::ceil(lo+(hi-lo)/2.0); };

    // stdandard input, output and error iterators
    std::ostream_iterator<std::string> os(std::cout,"");
    std::ostream_iterator<std::string> es(std::cerr,"");
    std::istream_iterator<std::string> eos;
  //std::istream_iterator<std::string> is = std::istream_iterator<std::string>(std::cin);

  } // namspace

// *EOF*
