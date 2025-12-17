#ifndef DOT_HPP
#define DOT_HPP
#include "idraw.hpp"

namespace top {
  struct Dot: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t p0_;
    Dot(int x, int y);
  };
}
#endif
