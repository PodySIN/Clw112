#include "rectangle.hpp"
#include <stdexcept>

top::Rectangle::Rectangle(p_t p0, int lengtha, int lengthb):
  IDraw(),
  p0_(p0),
  lengtha(lengtha),
  lengthb(lengthb)
{
  if (lengtha == 0 && lengthb == 0) {
    throw std::invalid_argument("It`s a dot, not a rectangle...");
  } else if (lengtha == 0 || lengthb == 0) {
    throw std::invalid_argument("It`s a seg, not a rectangle...");
  }
  if (lengtha < 0) {
    lengtha *= -1;
    p0_.x -= lengtha;
  }
  if (lengthb < 0) {
    lengthb *= -1;
    p0_.y -= lengthb;
  }
}

top::p_t top::Rectangle::begin() const
{
  return p0_;
}

top::p_t top::Rectangle::next(p_t p) const
{
  if (p.x < p0_.x + lengtha - 1 && p.y == p0_.y) {
    return {p.x + 1, p.y};
  } else if (p.y < p0_.y + lengthb - 1 && p.x == p0_.x + lengtha - 1) {
    return {p.x, p.y + 1};
  } else if (p.x > p0_.x && p.y == p0_.y + lengthb - 1) {
    return {p.x - 1, p.y};
  } else if (p.y > p0_.y && p.x == p0_.x) {
    return {p.x, p.y - 1};
  }
  return p0_;
}
