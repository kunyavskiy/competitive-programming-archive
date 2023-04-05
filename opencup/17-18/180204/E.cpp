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

struct pt {
  int x, col;
  pt(int x_, int col_) : x(x_), col(col_) {}
};
bool operator<(const pt &a, const pt &b) {
  if (a.x != b.x) return a.x < b.x;
  return a.col < b.col;
}

class Solver {
public:
  Solver(int len_) : len(len_) {}

  void add(int x) {
    eprintf("add %d\n", x);
    _add(pt(x, 0));
    _add(pt((x + (len / 2)) % len, 1));
  }

  void del(int x) {
    eprintf("del %d\n", x);
    _del(pt(x, 0));
    _del(pt((x + (len / 2)) % len, 1));
  }

  int getMin() {
    assert(!pts.empty());
    assert(!dists.empty());
    int ans1 = *dists.begin();
    assert(ans1 >= 0);
    int ans2 = len;
    {
      pt a = *pts.begin(), b = *--pts.end();
      if (a.col != b.col)
        ans2 = a.x + len - b.x;
    }
    eprintf("getMin = min(%d, %d)\n", ans1, ans2);
    return min(ans1, ans2);
  }

private:
  int len;
  multiset<pt> pts;
  multiset<int> dists;

  void _add(pt p) {
    auto it = pts.insert(p);
    auto ne = it; ne++;
    if (it != pts.begin() && ne != pts.end()) {
      auto pr = it; pr--;
      if (pr->col != ne->col)
        deld(ne->x - pr->x);
    }
    if (it != pts.begin()) {
      auto pr = it; pr--;
      if (pr->col != it->col)
        dists.insert(it->x - pr->x);
    }
    if (ne != pts.end()) {
      if (it->col != ne->col)
        dists.insert(ne->x - it->x);
    }
  }

  void _del(pt p) {
    auto it = pts.find(p);
    assert(it != pts.end());
    auto ne = it; ne++;
    if (it != pts.begin()) {
      auto pr = it; pr--;
      if (pr->col != it->col)
        deld(it->x - pr->x);
    }
    if (ne != pts.end()) {
      if (ne->col != it->col)
        deld(ne->x - it->x);
    }
    if (it != pts.begin() && ne != pts.end()) {
      auto pr = it; pr--;
      if (pr->col != ne->col)
        dists.insert(ne->x - pr->x);
    }
    pts.erase(it);
  }

  void deld(int d) {
    auto it = dists.find(d);
    assert(it != dists.end());
    dists.erase(it);
  }
};

const ld PI = 4 * atan(1.0);

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  double R, r;
  int n;
  while (scanf("%lf%lf%d", &R, &r, &n) == 3) {
    const double ALPHA = acos(r / R);
    const double HYP2 = 2 * sqrt(R * R - r * r);
    auto calc = [R, r, ALPHA, HYP2](int diff) {
      assert(diff <= 180000);
      diff = 180000 - diff;
      double ang = diff * PI / 180000.0;
      if (ang <= 2 * ALPHA) return 2 * R * sin(ang / 2);
      else return r * (ang - 2 * ALPHA) + HYP2;
    };

    Solver s(360000);
    for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      s.add(x);
    }
    printf("%.8lf\n", calc(s.getMin()));

    int q;
    scanf("%d", &q);
    while (q --> 0) {
      int op, x;
      scanf("%d%d", &op, &x);
      if (op == 1) s.add(x);
      else s.del(x);
      printf("%.8lf\n", calc(s.getMin()));
    }
  }
  return 0;
}
