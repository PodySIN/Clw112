#ifndef HSEG_HPP
#define HSEG_HPP
#include "idraw.hpp"

namespace top {
  struct HSeg: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t p0_;
    int length;
    HSeg(p_t a, int l);
  };
}
#endif
