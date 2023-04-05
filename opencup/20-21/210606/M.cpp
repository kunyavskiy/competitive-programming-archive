#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time : %.3lf s.\n", (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const ld eps = 1e-9;

struct point {
  ld x, y, z;
  point(ld x, ld y, ld z) : x(x), y(y), z(z) {}
  point() { x = y = z = 0; }
  bool operator==(const point &a) const {
    return fabs(x - a.x) < eps && fabs(y - a.y) < eps && fabs(z - a.z) < eps;
  }
  bool load() {
    double _x, _y, _z;
    if (scanf("%lf%lf%lf", &_x, &_y, &_z) != 3) return false;
    x = _x, y = _y, z = _z;
    return true;
  }
  ld dist2() const {
    return x * x + y * y + z * z;
  }
  ld dist() const {
    return sqrt(dist2());
  }
};

point operator+(const point &a, const point &b) {
  return point(a.x + b.x, a.y + b.y, a.z + b.z);
}

point operator-(const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y, a.z - b.z);
}

point operator*(const point &a, ld t) {
  return point(a.x * t, a.y * t, a.z * t);
}

ld det(ld a, ld b, ld c, ld d) {
  return a * d - b * c;
}

int sgn(ld x) {
  return (x > eps) - (x < -eps);
}

ld det(ld a11, ld a12, ld a13, ld a21, ld a22, ld a23, ld a31, ld a32, ld a33) {
  return a11 * det(a22, a23, a32, a33) - a12 * det(a21, a23, a31, a33) + a13 * det(a21, a22, a31, a32);
}

ld det(const point &a, const point &b, const point &c) {
  return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

point vp(const point &a, const point &b) {
  return point(det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), det(a.x, a.y, b.x, b.y));
}

ld sp(const point &a, const point &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}


struct line {
  point p, v;
  line() = default;
  line(const point &p, const point &v) : p(p), v(v) {
    assert(!(v == point()));
  }
  bool on(const point &pt) const {
    return vp(pt - p, v) == point();
  }
};

struct plane {
  point n;
  ld d;
  plane() : d(0) {}
  plane(const point &n, ld d) : n(n), d(d) {}
  plane(const point &p1, const point &p2,
        const point &p3) {
    n = vp(p2 - p1, p3 - p1);
    d = -sp(n, p1);
    assert(side(p1) == 0);
    assert(side(p2) == 0);
    assert(side(p3) == 0);
  }
  int side(const point &p) const {
    return sgn(sp(n, p) + d);
  }
  plane orient(const point& p) {
    if (side(p) < 0) {
      return {n * -1, -d};
    } else {
      return *this;
    }
  }
};

int cross(const line &l, const plane &pl, point &res) {
  ld d = sp(pl.n, l.v);
  if (sgn(d) == 0) {
    return (pl.side(l.p) == 0) ? 2 : 0;
  }
  ld t = (-sp(pl.n, l.p) - pl.d) / d;
  res = l.p + l.v * t;
#ifdef DEBUG
  assert(pl.side(res) == 0);
#endif
  return 1;
}

double solve_inner(point p1, point p2, point p3, point p4) {
  auto fix = [&](ld point::*field) {
    if (p3.*field > p4.*field) swap(p3.*field, p4.*field);
    if (p1.*field < p2.*field) {
      p3.*field = max(p3.*field, p1.*field);
      p4.*field = max(p4.*field, p1.*field);
    } else {
      p3.*field = min(p3.*field, p1.*field);
      p4.*field = min(p4.*field, p1.*field);
    }
    return p3.*field != p4.*field;
  };

  if (!fix(&point::x)) return 0;
  if (!fix(&point::y)) return 0;
  if (!fix(&point::z)) return 0;

  ld ans = 0;


  auto cut = [](vector<point> v, plane P) {
    vector<point> nv;
    for (int i = 0; i < (int) v.size(); i++) {
      point cur = v[i];
      point next = v[(i + 1) % v.size()];
      if (P.side(cur) >= 0) {
        nv.push_back(cur);
      }
      if (P.side(cur) * P.side(next) < 0) {
        line l{cur, next - cur};
        point p;
        int r = cross(l, P, p);
        assert(r == 1);
        nv.push_back(p);
      }
    }
    return nv;
  };

  auto get_volume = [](vector<point> v) {
    ld vol = 0;
    for (int i = 1; i + 1 < (int) v.size(); i++) {
      vol += det(v[0], v[i], v[i + 1]);
    }

    return vol;
  };

  point A{p3.x, p3.y, p3.z};
  point V1{p4.x - p3.x, 0, 0};
  point V2{0, p4.y - p3.y, 0};
  point V3{0, 0, p4.z - p3.z};

  point B = A + V1 + V2 + V3;

  vector<vector<point>> sqs = {
    {A, A + V1, A + V1 + V2, A + V2},
    {A, A + V3, A + V1 + V3, A + V1},
    {A, A + V2, A + V2 + V3, A + V3},
    {B, B - V3, B - V2 - V3, B - V2},
    {B, B - V2, B - V2 - V1, B - V1},
    {B, B - V1, B - V3 - V1, B - V3},
  };

  vector<point> tri { {p1.x, p1.y, p2.z}, {p1.x, p2.y, p1.z}, {p2.x, p1.y, p1.z} };

  plane P(tri[0], tri[1], tri[2]);
  if (P.side({p1.x, p1.y, p1.z}) < 0) {
    swap(tri[0], tri[1]);
    P = plane(tri[0], tri[1], tri[2]);
  }

  for (auto &sq : sqs) {
    ans += get_volume(cut(sq, P));
    tri = cut(tri, plane{sq[0], sq[1], sq[2]}.orient(A).orient(B));
  }

  ans += get_volume(tri);

  return -ans / 6.0;
}

bool solve() {
  point p1, p2, p3, p4;
  if (!p1.load()) return false;
  p2.load();
  p3.load();
  p4.load();

  double ans = solve_inner(p1, p2, p3, p4);
  printf("%.18lf\n", ans);

  return true;
}

int main() {
#ifdef LOCAL
  freopen("m.in", "r", stdin);
  freopen("m.out", "w", stdout);
#endif

  while (solve()) {

  }

  return 0;
}
