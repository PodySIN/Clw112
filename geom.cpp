#include "geom.hpp"
#include <stdexcept>
#include <iostream>

bool top::operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool top::operator!=(p_t a, p_t b)
{
  return !(a == b);
}

size_t top::rows(f_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}

size_t top::cols(f_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}

top::f_t top::frame(const p_t* pts, size_t s)
{
  if (!s) {
    throw std::logic_error("bad size");
  }
  int minx = pts[0].x, maxx = minx;
  int miny = pts[0].y, maxy = miny;
  for (size_t i = 1; i < s; i++) {
    minx = std::min(minx, pts[i].x);
    maxx = std::max(maxx, pts[i].x);
    miny = std::min(miny, pts[i].y);
    maxy = std::max(maxy, pts[i].y);
  }
  p_t aa{minx, miny};
  p_t bb{maxx, maxy};
  return {aa, bb};
}
