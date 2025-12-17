#ifndef DSEG_HPP
#define DSEG_HPP
#include "idraw.hpp"

namespace top {
  struct DSeg: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t p0_;
    int length;
    DSeg(p_t a, int l);
  };
}
#endif
