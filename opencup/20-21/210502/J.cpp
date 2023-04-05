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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

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

const ld eps = 1e-9;

struct point {
  ld x, y;
  ld dist() const { return sqrt(dist2()); }
  ld dist2() const { return x * x + y * y; }
  ld ang() const { return atan2(y, x); };
  friend point operator+(const point &a, const point &b) { return {a.x + b.x, a.y + b.y}; }
  friend point operator-(const point &a, const point &b) { return {a.x - b.x, a.y - b.y}; }
  friend point operator*(const point &a, ld b) { return {a.x * b, a.y * b}; }
  point rot90() const {
    return {-y, x};
  }
  point norm(ld newd) const {
    return *this * (newd / dist());
  }
  void read() {
    int x_, y_;
    scanf("%d%d", &x_, &y_);
    x = x_;
    y = y_;
  }
};

ld sp(const point& a, const point& b) {
  return a.x * b.x + a.y * b.y;
}

ld vp(const point& a, const point& b) {
  return a.x * b.y - a.y * b.x;
}


ld solve() {
  int n;
  ld R;
  double R_;
  scanf("%d%lf", &n, &R_); R = R_;
  vector<point> ps(n);
  for (point &p : ps) p.read();

  vector<point> is;

  {
    set<int> s;
    queue<int> q;
    for (int i = 0; i < n; i++) {
      s.insert(i);
      q.push(i);
    }
    while (!q.empty() && s.size() >= 2) {
      int v = q.front(); q.pop();
      auto it = s.find(v);
      if (it == s.end()) continue;
      auto last = prev(s.end());
      auto pit = (it == s.begin()) ? last : prev(it);
      auto nit = (it == last) ? s.begin() : next(it);
      auto check = [&](const point& a, const point& b, const point& c) {
        if (sp(b - a, c - a) >= 0) return true;
        ld s = abs(vp(b - a, c - a) / 2);
        ld A = (b - c).dist();
        ld B = (a - c).dist();
        ld C = (a - b).dist();
        ld r = A * B * C / (4 * s);
        return R > r;
      };
      if (!check(ps[*it], ps[*pit], ps[*nit])) {
        q.push(*pit);
        q.push(*nit);
        s.erase(it);
      }
    }
    vector<point> nps;
    for (auto x : s) {
      nps.push_back(ps[x]);
    }
    ps = nps;
    n = nps.size();
  }

  if (n == 1) {
    return M_PI * R * R;
  }

  ps.push_back(ps[0]);

  for (int i = 0; i < n; i++) {
    ld d2 = R * R - (ps[i] - ps[i + 1]).dist2() / 4;
    if (d2 <= eps) {
      eprintf("not intersecting\n");
      return 0;
    }
    ld d = sqrt(d2);
    point c = (ps[i + 1] + ps[i]) * 0.5;
    point v = (ps[i + 1] - ps[i]).rot90().norm(d);
    is.push_back(c + v);
  }

  auto area = [&](point c, point p1, point p2) {
    ld l = (p1 - c).ang();
    ld r = (p2 - c).ang();
    //eprintf("%lf..%lf, r -l = %lf\n", (double) l, (double) r, (double) (r - l));
    while (r < l - eps) r += 2 * M_PI;

    // 1/2 int f(t) x f'(t)
    // 1/2 int (p + v1 * cos + v2 * sin) x (-v1 * sin + v2 * cos)
    // 1/2 int -(p x v1) * sin + (p x v2) * cos + (v1 x v2) * cos^2 - (v2 x v1) * sin^2
    // 1/2 int -(p x v1) * sin + (p x v2) * cos + (v1 x v2)
    // 1/2 ((p x v1) * cos + (p x v2) * sin + (v1 x v2) * t)
    ld ans = (-R * c.y * (cos(r) - cos(l)) + R * c.x * (sin(r) - sin(l)) + R * R * (r - l)) / 2;
    //eprintf("%lf\n", (double) ans);
    return ans;
  };

  ld ans = 0;
  for (int i = 0; i < n; i++) {
    ans += area(ps[i], is[(i + n - 1) % n], is[i]);
  }

  for (int i = 0; i < n; i++) {
    if ((ps[i] - is[0]).dist2() > R * R * (1 + eps)) return 0;
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    printf("%.18lf\n", (double)solve());
  }
  return 0;
}
