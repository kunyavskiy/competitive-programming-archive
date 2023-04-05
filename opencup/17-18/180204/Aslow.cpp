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
  int x, y, s;
};

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, l, r;
  while (scanf("%d%d%d", &n, &l, &r) == 3) {
    vector<pt> pts(n);
    for (pt &p : pts)
      scanf("%d%d%d", &p.x, &p.y, &p.s);

    int minx = pts[0].x, maxx = pts[0].x;
    int miny = pts[0].y, maxy = pts[0].y;
    for (const pt &p : pts) {
      minx = min(minx, p.x);
      maxx = max(maxx, p.x);
      miny = min(miny, p.y);
      maxy = max(maxy, p.y);
    }
    minx -= r;
    miny -= r;
    maxx += r;
    maxy += r;

    int ans = 0;
    for (int y = miny; y <= maxy; y++)
      for (int x = minx; x <= maxx; x++) {
        int cans = 0;
        for (const pt &p : pts) {
          int d = max(abs(p.x - x), abs(p.y - y));
          if (l <= d && d <= r)
            cans += p.s;
        }
        ans = max(ans, cans);
      }
    printf("%d\n", ans);
  }

  return 0;
}
