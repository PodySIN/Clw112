#include "square.hpp"
#include <stdexcept>

top::Square::Square(p_t p0, int l):
  IDraw(),
  p0_(p0),
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("It`s a dot, not a square...");
  }
  if (length < 0) {
    length *= -1;
    p0_.x -= length;
  }
}

top::p_t top::Square::begin() const
{
  return p0_;
}

top::p_t top::Square::next(p_t p) const
{
  if (p.x < p0_.x + length - 1 && p.y == p0_.y) {
    return {p.x + 1, p.y};
  } else if (p.y < p0_.y + length - 1 && p.x == p0_.x + length - 1) {
    return {p.x, p.y + 1};
  } else if (p.x > p0_.x && p.y == p0_.y + length - 1) {
    return {p.x - 1, p.y};
  } else if (p.y > p0_.y && p.x == p0_.x) {
    return {p.x, p.y - 1};
  }
  return p0_;
}
