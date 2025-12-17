#ifndef VSEG_HPP
#define VSEG_HPP
#include "idraw.hpp"

namespace top {
  struct VSeg: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t p0_;
    int length;
    VSeg(p_t a, int l);
  };
}
#endif
