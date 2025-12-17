#ifndef SQUARE_HPP
#define SQUARE_HPP
#include "idraw.hpp"

namespace top {
  struct Square: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t p0_;
    int length;
    Square(p_t a, int length);
  };
}
#endif
