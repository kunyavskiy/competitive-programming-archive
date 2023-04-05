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

const double eps = 1e-9;

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
  double ang() const {
    double r = atan2(y, x);
    if (r < 0) r += 2 * M_PI;
    return r;
  }
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

#ifdef LOCAL1
#define my_assert assert
#else
#define my_assert (void)
#endif

// BEGIN ALGO
// Assumption: line.norm2() > 0
// Assumption: r >= 0

// returns 0-2 _unique_ points, which lie both on circle and line
// res[0] lies on the left side of (l.a, l.b)
// for example (center=0,0, r=2, 0x+1y-1=0): (-sqrt(3), 1), (sqrt(3),1)

pt operator&(const line &l1, const line &l2) {
  double d = l1.a * l2.b - l1.b * l2.a;
  my_assert(fabs(d) > eps);
  pt res(
    (l1.b * l2.c - l1.c * l2.b) / d,
    (l1.a * l2.c - l1.c * l2.a) / -d);
  my_assert(l1.side(res) == 0);
  my_assert(l2.side(res) == 0);
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

void cross(const pt &center, double r,
           const line &l, vector<pt> &res) {
  double di = l.distz(center);
  double d2 = l.norm2();
  my_assert(fabs(d2) > eps);
  pt mid = center + pt(l.a, l.b) * (-di / d2);
  my_assert(l.side(mid) == 0);

  double s = r * r - di * di / d2;
  if (s < -eps) {
    return;
  }
  s = max(s, 0.0);
  if (fabs(di * di - r * r * d2) < eps) {
    res.push_back(mid);
  }

  pt off = pt(-l.b, l.a) * sqrt(s / d2);
  my_assert(fabs(off.dist2() - s) < eps);
  res.push_back(mid + off);
  res.push_back(mid - off);
}


// returns 0-2 _unique_ points.
// res[0] lies on the left side of line (a-->b)
void cross(const pt &a, double r1, pt b, double r2, vector<pt> &res) {
  if (r1 < 0 || r2 < 0) return;
  b = b - a;
  if (fabs(b.dist2()) < eps) {
    if (fabs(r1) < eps && fabs(r2) < eps) {
      res.push_back(a);
    }

    my_assert(fabs(r1 - r2) > eps);
    return;
  }
  int old_size = res.size();
  cross(b, r2,
        line(2 * b.x, 2 * b.y,
             sqr(r2) - sqr(r1) -
               sqr(b.x) - sqr(b.y)),
        res);
  for (int i = old_size; i < (int) res.size(); i++)
    res[i] = res[i] + a;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("5.out", "w", stdout);
#endif

  int n;
  double r;
  while (scanf("%d%lf", &n, &r) == 2) {
    vector<pt> p(n);
    vector<double> h(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf%lf", &p[i].x, &p[i].y, &h[i]);
    }

    vector<pt> cands;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        cross(p[i], h[i] + r, p[j], h[j] + r, cands);
        cross(p[i], h[i] + r, p[j], h[j] - r, cands);
        cross(p[i], h[i] - r, p[j], h[j] + r, cands);
        cross(p[i], h[i] - r, p[j], h[j] - r, cands);
      }
      cands.push_back({p[i].x + h[i] + r, p[i].y});
    }

    int best = 0;
    pt bestpt;

    for (pt x : cands) {
      int cnt = 0;
      for (int i = 0; i < n; i++) {
        double dist = (x - p[i]).dist2();
        if (is_in(sqr(max(0.0, h[i] - r)), sqr(h[i] + r), dist)) {
          cnt++;
        }
      }
      if (cnt > best) {
        best = cnt;
        bestpt = x;
      }
    }

    printf("%d\n", best);
    printf("%.15f %.15f\n", bestpt.x, bestpt.y);

    for (int i = 0; i < n; i++) {
      pt cand{p[i].x + h[i], p[i].y};
      if ((cand - bestpt).dist2() <= sqr(r) + eps) {
        printf("%d %.15f\n", i + 1, (cand - p[i]).ang() / M_PI * 180);
      } else {
        vector<pt> rs;
        cross(p[i], h[i], bestpt, r, rs);
        if (rs.size() > 0) {
          printf("%d %.15f\n", i + 1, (rs[0] - p[i]).ang() / M_PI * 180);
        }
      }
    }
  }

  return 0;
}
