#include <iostream>
#include "ascii_draw.hpp"

int main()
{
  using top::IDraw;
  using top::Dot;
  using top::f_t;
  using top::p_t;
  using top::HSeg;
  using top::VSeg;
  using top::DSeg;
  using top::Square;
  using top::Rectangle;
  int err = 0;
  p_t * pts = nullptr;
  size_t s = 0;
  size_t sc = 10;
  IDraw * shps[sc] = {};
  try {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    shps[3] = new HSeg(p_t{3, 3}, 5);
    shps[4] = new VSeg(p_t{8, 8}, 5);
    shps[5] = new DSeg(p_t{-8, -7}, 4);
    shps[6] = new Square(p_t{16, -16}, 6);
    shps[7] = new Rectangle(p_t{-16, -16}, 8, 5);
    shps[8] = new Dot(-30, -30);
    shps[9] = new Dot(30, -30);
    for (size_t i = 0; i < sc; i++) {
      points(*(shps[i]), &pts, s);
    }
    f_t fr = frame(pts, s);
    char * cnv = canvas(fr, '.');
    for (size_t i = 0; i < s; i++) {
      paint(cnv, fr, pts[i], '#');
    }
    flush(std::cout, cnv, fr);
    delete[] cnv;
  } catch (...) {
    err = 2;
    std::cerr << "Dab drawing\n";
  }
  delete[] pts;
  delete_shapes(shps, sc);
  return err;
}
