#include "dseg.hpp"
#include <stdexcept>

top::DSeg::DSeg(p_t p0, int l):
  IDraw(),
  p0_(p0),
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("It`s a dot, not a segment...");
  }
  if (length < 0) {
    length *= -1;
    p0_.y -= length;
    p0_.x -= length;
  }
}

top::p_t top::DSeg::begin() const
{
  return p0_;
}

top::p_t top::DSeg::next(p_t p) const
{
  if ((p.y == p0_.y + length - 1) && (p.x == p0_.x + length - 1)) {
    return p0_;
  }
  return {p.x + 1, p.y + 1};
}
