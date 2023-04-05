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

#ifndef LOCAL
//#undef assert
//#define assert(x) (x)
#endif

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


namespace dbl_utils {
  typedef double dbl;

  const dbl EPS = 1e-9;

  bool eq(dbl a, dbl b) {
    return fabs(a - b) < EPS;
  }

  bool ne(dbl a, dbl b) {
    return !eq(a, b);
  }

  bool lt(dbl a, dbl b) {
    return a < b && !eq(a, b);
  }

  bool le(dbl a, dbl b) {
    return !lt(b, a);
  }

  bool ge(dbl a, dbl b) {
    return !lt(b, a);
  }

  bool gt(dbl a, dbl b) {
    return lt(b, a);
  }

  int sign(dbl x) {
    if (eq(x, 0)) return 0;
    if (x > 0) return 1;
    return -1;
  }
}
using namespace dbl_utils;
template <typename T>
struct _pt {
  T x, y;

  _pt<T>() {}
  _pt<T>(T _x, T _y) : x(_x), y(_y) {}

  _pt<T> operator+ (const _pt<T> &p) const {
    return _pt<T>(x + p.x, y + p.y);
  }

  _pt<T>& operator+= (const _pt<T> &p) {
    return *this = *this + p;
  }

  _pt<T> operator- (const _pt<T> &p) const {
    return _pt<T>(x - p.x, y - p.y);
  }

  _pt<T>& operator-= (const _pt<T> &p) {
    return *this = *this - p;
  }

  _pt<T> operator* (T d) const {
    return _pt<T>(x * d, y * d);
  }

  _pt<T>& operator*= (T d) {
    return *this = *this * d;
  }

  T operator* (const _pt<T> &p) const {
    return x * p.y - y * p.x;
  }

  T operator% (const _pt<T> &p) const {
    return x * p.x + y * p.y;
  }

  T d2() const {
    return *this % *this;
  }

  dbl d() const {
    return sqrt((dbl)d2());
  }

  dbl ang() const {
    return atan2((dbl)y, (dbl)x);
  }

  _pt<T> rotate90() const {
    return _pt<T>(-y, x);
  }

  _pt<T> rotate(dbl ang) {
    return _pt<T>(x * cos(ang) - y * sin(ang),
                  x * sin(ang) + y * cos(ang));
  }

  int turn(const _pt<T> &p) const {
    return sign((*this) * p);
  }

  bool operator< (const _pt<T> &p) const {
    if (!eq(x, p.x)) return lt(x, p.x);
    return lt(y, p.y);
  }

  bool operator== (const _pt<T> &p) const {
    return eq(x, p.x) && eq(y, p.y);
  }

  void read() {
    cin >> x >> y;
  }

  int up() const {
    if (lt(0, y) || (eq(0, y) && lt(0, x))) return 1;
    if (lt(y, 0) || (eq(0, y) && lt(x, 0))) return -1;
    return 0;
  }
};
typedef _pt<dbl> pt;
const dbl PI = acos(-1.0);
const dbl PHI = (sqrt(5.0) - 1) / 2.0;

struct line {
  pt p;
  pt v;

  bool contains(pt x) {
    return v.turn(x - p) > 0;
  }
};

pt pt_ang(dbl ang) {
  return pt(cos(ang), sin(ang));
}

line get_line(dbl ang, int r, int i) {
  line l;
  switch (i) {
    case 0: {
      l = line({pt_ang(ang) * r, pt_ang(ang - PI / 2)});
      break;
    }
    case 1: {
      l = line({pt_ang(ang) * r, pt_ang(ang + PI / 2)});
      break;
    }
    case 2: {
      l = line({pt_ang(ang + PI) * r, pt_ang(ang + PI / 2)});
      break;
    }
    case 3: {
      l = line({pt_ang(ang + PI) * r, pt_ang(ang - PI / 2)});
      break;
    }
    default: {
      assert(0);
    }
  }
  return l;
}

namespace PASHA {
  const double eps = 1e-9;
#define pb push_back
#define sz(x) ((int)(x).size())

  int sgn(double x) { return x < -eps ? -1 : x > eps; }
  struct pt {
    double x, y;
    pt() : x(0), y(0) {}
    pt(double x, double y) : x(x), y(y) {}
    pt operator+(const pt &p2) const { return pt(x + p2.x, y + p2.y); }
    pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
    pt operator*(const double b) const { return pt(x * b, y * b); }
    int operator*(const pt &p2) const { return sgn(x * p2.y - y * p2.x); }
    int operator^(const pt &p2) const { return sgn(x * p2.x + y * p2.y); }
    double dist2() const { return x * x + y * y; }
    bool operator<(const pt &p2) const { return fabs(x - p2.x) > eps ? x < p2.x : y < p2.y - eps; }
    bool operator==(const pt &p2) const { return fabs(x - p2.x) < eps && fabs(y - p2.y) < eps; }
  };
  struct line {
    double a, b, c;
    line() : a(0), b(0), c(1) {}
    line(const pt &p1, const pt &p2) {
      a = p1.y - p2.y;
      b = p2.x - p1.x;
      c = -a * p1.x - b * p1.y;
    }
    line(double a, double b, double c) : a(a), b(b), c(c) {}
    double distz(const pt &p) const { return a * p.x + b * p.y + c; }
    double norm2() const { return a * a + b * b; }
    double dists(const pt &p) const { return distz(p) / sqrt(norm2()); }
    double dist(const pt &p) const { return fabs(distz(p)) / sqrt(norm2()); }
    int side(const pt &p2) const { return sgn(a * p2.x + b * p2.y + c); }
  };

#define sqr(x) ((x) * (x))

// BEGIN ALGO
// Assumption: line.norm2() > 0
// Assumption: r >= 0

// returns 0-2 _unique_ points, which lie both on circle and line
// res[0] lies on the left side of (l.a, l.b)
// for example (center=0,0, r=2, 0x+1y-1=0): (-sqrt(3), 1), (sqrt(3),1)

  pt operator&(const line &l1, const line &l2) {
    double d = l1.a * l2.b - l1.b * l2.a;
//    assert(fabs(d) > eps);
    pt res(
      (l1.b * l2.c - l1.c * l2.b) / d,
      (l1.a * l2.c - l1.c * l2.a) / -d
    );
//    assert(l1.side(res) == 0);
//    assert(l2.side(res) == 0);
    return res;
  }

  bool is_in(double l, double r, double x) {
    if (l > r) swap(l, r);
    return l <= x + eps && x - eps <= r;
  }
/*BOXNEXT*/
  bool contains(const pt &a, const pt &b, const pt &p) {
    if ((p - a) * (p - b) != 0) return false;
    return is_in(a.x, b.x, p.x) &&
           is_in(a.y, b.y, p.y);
  }

  vector<pt> cross(const pt &center, double r,
                   const line &l) {
    double di = l.distz(center);
    double d2 = l.norm2();
    assert(fabs(d2) > eps);
    pt mid = center + pt(l.a, l.b) * (-di / d2);
#ifdef DEBUG
    assert(l.side(mid) == 0);
#endif

    double s = r * r - di * di / d2;
    if (s < -eps) return vector<pt>();
    if (fabs(di * di - r * r * d2) < eps)
      return vector<pt>(1, mid);

    pt off = pt(-l.b, l.a) * sqrt(s / d2);
    assert(fabs(off.dist2() - s) < eps);
    vector<pt> res;
    res.pb(mid + off);
    res.pb(mid - off);
    return res;
  }




// returns 0-2 _unique_ points.
// res[0] lies on the left side of line (a-->b)
  vector<pt> cross(const pt &a, double r1, pt b,
                   double r2) {
    b = b - a;
    if (fabs(b.dist2()) < eps) {
      if (fabs(r1) < eps && fabs(r2) < eps)
        return vector<pt>(1, a);

      assert(fabs(r1 - r2) > eps);
      return vector<pt>();
    }
    vector<pt> res = cross(b, r2,
                           line(2 * b.x, 2 * b.y,
                                sqr(r2) - sqr(r1) -
                                sqr(b.x) - sqr(b.y)));
    for (int i = 0; i < sz(res); i++)
      res[i] = res[i] + a;
    return res;
  }

// returns tangent line to (cent,r) in point (p)
// p should lie on the circle. !! r > 0 !!
  line get_tangent(const pt &cent, /*BOXNEXT*/
                   const double &r, const pt &p){ /*BOXNEXT*/
    assert(fabs((p - cent).dist2() - r * r) < eps);
    assert(fabs(r) > eps);
    pt vec = p - cent;
    return line(
      vec.x, vec.y, -vec.x * p.x - vec.y * p.y
    );
  }

// returns 0-2 _unique_ points such that (p-->x) is
// tangent to the circle. When r=0, returns no more than 1 point
// res[0] lies on the left side of line (p-->cent)
  vector<pt> tangent(const pt &p,
                     const pt &cent,
                     const double &r) {
    vector<pt> res = cross(
      pt(), r,
      line(cent.x - p.x, cent.y - p.y, r * r)
    );
    for (int i = 0; i < sz(res); i++)
      res[i] = res[i] + cent;
    return res;
  }
}

dbl solve(vector<pt> a, int r) {
  int n = a.size();

  vector<dbl> angles;
  auto add_angle = [&](double ang) {
    while (ang < 0) ang += PI;
    while (ang >= PI) ang -= PI;
    angles.push_back(ang);
  };
  angles.push_back(0);
  angles.push_back(PI);
  for (int i = 0; i < n; i++) {
    dbl ang = a[i].ang();
    add_angle(ang);
    dbl turn = acos(r / a[i].d());
    add_angle(ang - turn);
    add_angle(ang + turn);
    add_angle(ang - turn + PI / 2);
    add_angle(ang + turn + PI / 2);
  }
  sort(angles.begin(), angles.end());

  vector<int> id(4, -1);
  for (int i = 0; i < 4; i++) {
    line l = get_line(angles[0], r, i);
    for (int j = 0; j < n; j++) {
      if (!l.contains(a[j])) {
        id[i] = j;
        break;
      }
    }
    assert(id[i] != -1);
    while (!l.contains(a[id[i]])) {
      id[i] = (id[i] + 1) % n;
    }
  }

  auto f = [&](dbl ang) {
    vector<pt> vct;

    for (int i = 0; i < 4; i++) {
      pt u = a[(id[i] - 1 + n) % n];
      pt v = a[id[i]];

      PASHA::line l1(PASHA::pt(u.x, u.y), PASHA::pt(v.x, v.y));
      line cl = get_line(ang, r, i);
      PASHA::line l2(PASHA::pt(cl.p.x, cl.p.y), PASHA::pt(cl.p.x + cl.v.x, cl.p.y + cl.v.y));
      auto res = l1 & l2;
      vct.push_back(pt(res.x, res.y));
    }
    return (vct[0] - vct[1]).d() + (vct[2] - vct[3]).d();
  };
  dbl ans = 1e20;
  for (int t = 0; t + 1 < (int)angles.size(); t++) {
    for (int i = 0; i < 4; i++) {
      line l = get_line((angles[t] + angles[t + 1]) / 2, r, i);
      int cur = 0;
      while (!l.contains(a[id[i]])) {
        cur++;
        assert(cur <= n);
        id[i] = (id[i] + 1) % n;
      }
    }

    dbl L = angles[t];
    dbl R = angles[t + 1];
    dbl fL = f(R - (R - L) * PHI);
    dbl fR = f(L + (R - L) * PHI);
    for (int it = 0; it < 50; it++) {
//      dbl m1 = (L + L + R) / 3;
//      dbl m2 = (L + R + R) / 3;
//      if (f(m1) < f(m2)) {
//        R = m2;
//      } else {
//        L = m1;
//      }
      if (fL < fR) {
        fR = fL;
        R = L + (R - L) * PHI;
        fL = f(R - (R - L) * PHI);
      } else {
        fL = fR;
        L = R - (R - L) * PHI;
        fR = f(L + (R - L) * PHI);
      }
    }
    ans = min(ans, min(f(L), f(R)));
  }
  return ans;
}

void stress() {
  for (int it = 0;; it++) {
    srand(it);
    db(it);

    int n = rand() % 10 + 3;
    int r = 1;
    vector<pt> a(n);
    const int C = 10;
    pt sum;
    for (int i = 0; i < n; i++) {
      a[i].x = rand() % (2 * C + 1) - 1;
      a[i].y = rand() % (2 * C + 1) - 1;
      a[i].x = a[i].x * 5 + 1;
      a[i].y = a[i].y * 5 + 1;
      sum = sum - a[i];
    }
    a.push_back(sum);
    n = a.size();

    sort(a.begin(), a.end(), [&](pt u, pt v) {
      if (u.up() != v.up()) return u.up() > v.up();
      return u.turn(v) > 0;
    });

    vector<pt> b(n);
    for (int i = 1; i < n; i++) {
      b[i] = b[i - 1] + a[i - 1];
    }

    pt w;
    for (int i = 0; i < n; i++) w = w + b[i];
    w = w * (1.0 / n);
    for (int i = 0; i < n; i++) b[i] = b[i] - w;

    auto ans = solve(b, r);
    db(ans);
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif

//  stress();

  int n, r;
  while (scanf("%d%d", &n, &r) == 2) {
    vector<pt> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &a[i].x, &a[i].y);
    }
    dbl s = 0;
    for (int i = 0; i < n; i++) s += a[i] * a[(i + 1) % n];
    if (s < 0) reverse(a.begin(), a.end());

    printf("%.17f\n", solve(a, r));
  }

  return 0;
}
