#include "dot.hpp"

top::Dot::Dot(int x, int y):
  IDraw(),
  p0_{x, y}
{}

top::p_t top::Dot::begin() const
{
  return p0_;
}

top::p_t top::Dot::next(p_t) const
{
  return begin();
}
