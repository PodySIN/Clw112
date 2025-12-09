#include <iostream>

namespace top {
  struct p_t {
    int x, y;
  };
  struct f_t {
    p_t aa;
    p_t bb;
  };
  struct IDraw {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
    virtual ~IDraw() = default;
  };
  struct Dot: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    Dot(int x, int y);
  };
  struct HSeg: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    int length;
    HSeg(p_t a, int l);
  };
  struct VSeg: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    int length;
    VSeg(p_t a, int l);
  };

  struct DSeg: IDraw {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t a;
    int length;
    DSeg(p_t a, int l);
  };

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  bool operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }
  
  void delete_shapes(IDraw ** shps, size_t s);
  size_t rows(f_t fr);
  size_t cols(f_t fr);
  void extend(p_t** pts, size_t s, p_t p);
  void points(const IDraw& d, p_t ** pts, size_t & s);
  f_t frame(const p_t * ps, size_t s);
  char * canvas(f_t f, char fill);
  void paint(char * cnv, f_t fr, p_t p, char fill);
  void flush(std::ostream& os, const char* cnv, f_t fr);
}

int main()
{
  using top::IDraw;
  using top::Dot;
  using top::f_t;
  using top::p_t;
  using top::HSeg;
  using top::VSeg;
  using top::DSeg;
  int err = 0;
  p_t * pts = nullptr;
  size_t s = 0;
  size_t sc = 6;
  IDraw * shps[6] = {};
  try {
    shps[0] = new Dot(0, 0);
    shps[1] = new Dot(5, 7);
    shps[2] = new Dot(-5, -2);
    shps[3] = new HSeg(p_t{3, 3}, 5);
    shps[4] = new VSeg(p_t{8, 2}, 5);
    shps[5] = new DSeg(p_t{-8, -7}, 4);
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

void top::delete_shapes(IDraw ** shps, size_t s)
{
  for (size_t i = 0; i < s; i++) {
    delete shps[i];
  }
}

size_t top::rows(f_t fr)
{
  return (fr.bb.y - fr.aa.y + 1);
}

size_t top::cols(f_t fr)
{
  return (fr.bb.x - fr.aa.x + 1);
}

top::Dot::Dot(int x, int y):
  IDraw(),
  o{x, y}
{}

top::p_t top::Dot::begin() const
{
  return o;
}

top::p_t top::Dot::next(p_t) const
{
  return begin();
}

top::HSeg::HSeg(p_t aa, int l):
  IDraw(),
  a(aa),
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("It`s a dot, not a segment...");
  }
  if (length < 0) {
    length *= -1;
    a.x -= length;
  }
}

top::p_t top::HSeg::begin() const
{
  return a;
}

top::p_t top::HSeg::next(p_t p) const
{
  if (p.x == a.x + length - 1) {
    return a;
  }
  return {p.x + 1, p.y};
}

top::VSeg::VSeg(p_t aa, int l):
  IDraw(),
  a(aa),
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("It`s a dot, not a segment...");
  }
  if (length < 0) {
    length *= -1;
    a.y -= length;
  }
}

top::p_t top::VSeg::begin() const
{
  return a;
}

top::p_t top::VSeg::next(p_t p) const
{
  if (p.y == a.y + length - 1) {
    return a;
  }
  return {p.x, p.y + 1};
}

top::DSeg::DSeg(p_t aa, int l):
  IDraw(),
  a(aa),
  length(l)
{
  if (length == 0) {
    throw std::invalid_argument("It`s a dot, not a segment...");
  }
  if (length < 0) {
    length *= -1;
    a.y -= length;
    a.x -= length;
  }
}

top::p_t top::DSeg::begin() const
{
  return a;
}

top::p_t top::DSeg::next(p_t p) const
{
  if ((p.y == a.y + length - 1) && (p.x == a.x + length - 1)) {
    return a;
  }
  return {p.x + 1, p.y + 1};
}

void top::extend(p_t** pts, size_t s, p_t p) 
{
  p_t *res = new p_t[s+1];
  for(size_t i = 0; i < s; i++) {
    res[i] = (*pts)[i];
  }
  res[s] = p;
  delete[] *pts;
  *pts = res;
}

void top::points(const IDraw& d, p_t ** pts, size_t & s)
{
  p_t p = d.begin();
  extend(pts, s, p);
  size_t delta = 1;
  while (d.next(p) != d.begin()) {
    p = d.next(p);
    extend(pts, s + delta, p);
    delta++;
  }
  s += delta;
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

char * top::canvas(f_t fr, char fill) 
{
  char * cnv = new char[rows(fr) * cols(fr)];
  for (size_t i = 0; i < rows(fr) * cols(fr); i++) {
    cnv[i] = fill;
  }
  return cnv;
}

void top::paint(char* cnv, f_t fr, p_t p, char fill)
{
  int dx = p.x - fr.aa.x;
  int dy = fr.bb.y - p.y;
  cnv[dy * cols(fr) + dx] = fill;
}

void top::flush(std::ostream& os, const char* cnv, f_t fr)
{
  for (size_t i = 0; i < rows(fr); i++) {
    for (size_t j = 0; j < cols(fr); j++) {
      os << cnv[i * cols(fr) + j];
    }
    os << "\n";
  }
}
