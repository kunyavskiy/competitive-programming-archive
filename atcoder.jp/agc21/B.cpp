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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

struct point {
  ll x, y;
};

ll sp(const point& a, const point& b) {
  return a.x * b.x + a.y * b.y;
}

ll vp(const point& a, const point& b) {
  return a.x * b.y - a.y * b.x;
}


int sign(ll x) {
  return (x > 0) - (x < 0);
}

struct line {
  ll a, b, c;
  line(const point &p1, const point& p2) {
    a = p2.y - p1.y;
    b = p1.x - p2.x;
    c = -a * p1.x - b * p1.y;
    assert(side(p1) == 0);
    assert(side(p2) == 0);
  }

  int side(const point &p1) {
    return sign(a * p1.x + b * p1.y + c);
  }
};

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<point> v(n);
    for (point& p : v) {
      scanf("%lld%lld", &p.x, &p.y);
      p.x *= 2;
      p.y *= 2;
    }

    vector<point> lf(n);
    vector<point> rg(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i == j) continue;
        line l(v[i], v[j]);
        bool bad = false;
        for (int k = 0; k < n; k++) {
          if (k == i || k == j) continue;
          if (l.side(v[k]) < 0) {
            bad = true;
            break;
          }
          if (l.side(v[k]) == 0) {
            bool ok = false;
            if (min(v[i].x, v[j].x) <= v[k].x && v[k].x <= max(v[i].x, v[j].x)) {
              if (min(v[i].y, v[j].y) <= v[k].y && v[k].y <= max(v[i].y, v[j].y)) {
                ok = true;
              }
            }
            if (!ok) {
              bad = true;
            }
          }
        }
        if (bad) continue;
        lf[i] = rg[j] = {l.a, l.b};
      }
    }

    for (int i = 0; i < n; i++) {
      printf("%.18lf\n", atan2(vp(lf[i], rg[i]), sp(lf[i], rg[i])) / (2 * M_PI));
    }
  }

  return 0;
}
