#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "idraw.hpp"

namespace top {
  struct Rectangle: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t p0_;
    int lengtha;
    int lengthb;
    Rectangle(p_t a, int lengtha, int lengthb);
  };
}
#endif
