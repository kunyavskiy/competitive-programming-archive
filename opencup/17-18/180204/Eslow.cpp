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

class Solver {
public:
  Solver(int len_) : len(len_) {}

  void add(int x) {
    pts.insert(x);
  }

  void del(int x) {
    auto it = pts.find(x);
    assert(it != pts.end());
    pts.erase(it);
  }

  int getMax() {
    int ans = 0;
    for (auto a : pts)
      for (auto b : pts) {
        int d = abs(b - a);
        d = min(d, len - d);
        ans = max(ans, d);
      }
    return ans;
  }

private:
  int len;
  multiset<int> pts;
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
    printf("%.8lf\n", calc(s.getMax()));

    int q;
    scanf("%d", &q);
    while (q --> 0) {
      int op, x;
      scanf("%d%d", &op, &x);
      if (op == 1) s.add(x);
      else s.del(x);
      printf("%.8lf\n", calc(s.getMax()));
    }
  }
  return 0;
}
