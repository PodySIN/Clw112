#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>

namespace top {
  struct p_t {
    int x, y;
  };
  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);
  struct f_t {
    p_t aa;
    p_t bb;
  };
  size_t rows(f_t fr);
  size_t cols(f_t fr);
  f_t frame(const p_t * ps, size_t s);
}
#endif
