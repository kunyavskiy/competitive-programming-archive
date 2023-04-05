#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

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

  bool operator<(const point &a) const {
    if (fabs(x - a.x) > eps) return x < a.x;
    if (fabs(y - a.y) > eps) return y < a.y;
    if (fabs(z - a.z) > eps) return z < a.z;
    return false;
  }

  bool load() {
    double _x, _y, _z;
    if (scanf("%lf%lf%lf", &_x, &_y, &_z) != 3) return 0;
    x = _x, y = _y, z = _z;
    return 1;
  }

  void print() const {
    printf("%lf %lf %lf\n", (double) x, (double) y, (double) z);
  }

  void eprint() {
    eprintf("%lf %lf %lf\n", (double) x, (double) y, (double) z);
  }

  ld dist2() const {
    return x * x + y * y + z * z;
  }

  ld dist() const {
    return sqrt(dist2());
  }
};

inline point operator+(const point &a, const point &b) {
  return point(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline point operator-(const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline point operator*(const point &a, ld t) {
  return point(a.x * t, a.y * t, a.z * t);
}

inline point operator/(const point &a, ld t) {
  return point(a.x / t, a.y / t, a.z / t);
}


inline ld det(ld a, ld b, ld c, ld d) {
  return a * d - b * c;
}

inline ld det(ld a11, ld a12, ld a13, ld a21, ld a22, ld a23, ld a31, ld a32, ld a33) {
  return a11 * det(a22, a23, a32, a33) - a12 * det(a21, a23, a31, a33) + a13 * det(a21, a22, a31, a32);
}

int sgn(ld x) {
  return (x > eps) - (x < -eps);
}

inline ld det(const point &a, const point &b, const point &c) {
  return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

point vp(const point &a, const point &b) {
  return point(det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), det(a.x, a.y, b.x, b.y));
}

ld sp(const point &a, const point &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

struct segment {
  point p1, p2;

  segment(const point &_p1, const point &_p2) : p1(_p1), p2(_p2) {
    if (p2 < p1) swap(p1, p2);
  }

  bool operator<(const segment &s) const {
    if (!(p1 == s.p1)) return p1 < s.p1;
    return p2 < s.p2;
  }

  bool operator==(const segment &s) const {
    return p1 == s.p1 && p2 == s.p2;
  }
};

struct triangle {
  point p1, p2, p3;

  int side(const point& p) const {
    return sgn(sp(p - p1, vp(p2 - p1, p3 - p1)));
  }

  void norm(const point &p) {
    if (side(p) < 0) {
      swap(p2, p3);
    }
  }
};

point intersect(const point &p1, const point &p2, double z) {
  return p1 + (p2 - p1) / (p2.z - p1.z) * (z - p1.z);
}

ld get_volume(const vector<triangle> &ts, double z) {
  ld ans = 0;
  for (const auto &t : ts) {
    vector<point> p;
    p.push_back(t.p1);
    p.push_back(t.p2);
    p.push_back(t.p3);
    sort(p.begin(), p.end(), [](const point& a, const point& b) { return a.z < b.z;});

    if (z > p[2].z) {
      ans += abs(det(t.p1, t.p2, t.p3));
    } else if (z > p[1].z) {
      ans += abs(det(t.p1, t.p2, t.p3));
      ans -= abs(det(
          intersect(point(), p[2], z) - p[2],
          intersect(p[1], p[2], z) - p[2],
          intersect(p[0], p[2], z) - p[2]
          ));
    } else if (z > p[0].z) {
      point p2 = intersect(point(), p[2], z);
      point p1 = intersect(point(), p[1], z);
      point p02 = intersect(p[0], p[2], z);
      point p01 = intersect(p[0], p[1], z);

      ans += abs(det(p1, p02, p2));
      ans += abs(det(p1, p01, p02));
      ans += abs(det(p[0], p01, p02));
    } else {
      ans += abs(det(
          (p[2] / p[2].z * z),
          (p[1] / p[1].z * z),
          (p[0] / p[0].z * z)
      ));
    }
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<point> v(n);

  point inside;

  for (int i = 0; i < n; i++) {
    v[i].load();
  }

  {
    point f = v[0];
    for (int i = 0; i < n; i++) {
      if (v[i].z < f.z) f = v[i];
    }
    for (int i = 0; i < n; i++) {
      v[i] = v[i] - f;
    }
  }


  inside = (v[0] + v[1] + v[2] + v[3]) * 0.25;

  vector<triangle> ts;
/*  ts.push_back({v[0], v[1], v[2]});
  ts.push_back({v[0], v[2], v[3]});
  ts.push_back({v[0], v[1], v[3]});
  ts.push_back({v[1], v[2], v[3]});

  for (triangle& t : ts) {
    t.norm(inside);
  }

  for (int i = 4; i < n; i++) {
    vector<triangle> nts;
    vector<segment> ss;

    for (const auto& t : ts) {
      if (t.side(v[i]) < 0) {
        ss.push_back({t.p1, t.p2});
        ss.push_back({t.p2, t.p3});
        ss.push_back({t.p1, t.p3});
      } else {
        nts.push_back(t);
      }
    }
    sort(ss.begin(), ss.end());

    for (int j = 0; j < (int)ss.size(); j++) {
      if (j < (int) ss.size() && ss[j] == ss[j + 1]) {
        j++;
      } else {
        triangle t{ss[j].p1, ss[j].p2, v[i]};
        t.norm(inside);
        nts.push_back(t);
      }
    }
    ts = nts;
  }
*/

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        triangle t{v[i], v[j], v[k]};
        t.norm(inside);
        ts.push_back(t);
        for (int q = 0; q < n; q++) {
          if (q != i && q != j && q != k) {
            if (t.side(v[q]) <= 0) {
              ts.pop_back();
              break;
            }
          }
        }
      }
    }
  }

  eprintf("ts = %d\n", (int)ts.size());
//  for (const triangle& t : ts) {
//    t.p1.print();
//    t.p2.print();
//    t.p3.print();
//    printf("\n");
//  }

  get_volume(ts, 5);

//  for (int i = 1; i < 1000; i++) {
//    printf("%.18lf %.18lf\n", i / 100.0, (double)get_volume(ts, i / 100.0));
//  }

  ld l = 0;
  ld r = 500;

  ld need_volume = get_volume(ts, r) * 0.9;

  for (int i = 0; i < 100; i++) {
    ld m = (l + r) / 2;
    ld v = get_volume(ts, m);

    if (v >= need_volume) {
      r = m;
    } else {
      l = m;
    }
  }

  printf("%.18lf\n", (double)(l + r) / 2.0);
  return 0;
}
