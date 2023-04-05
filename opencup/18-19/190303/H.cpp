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

struct pt {
  ld x, y;
};

pt operator-(const pt& a, const pt& b) {
  return {a.x - b.x, a.y - b.y};
}

ld vp(const pt& a, const pt& b) {
  return a.x * b.y - a.y * b.x;
}

ld sp(const pt& a, const pt& b) {
  return a.x * b.x + a.y * b.y;
}

ld dist(pt a, pt b) {
  pt c = a - b;
  return sqrt(c.x * c.x + c.y * c.y);
}

ld solve1(pt p, ld v, ld w) {
  ld r = v / w;

  const int BUBEN = 1e6;
  ld ans = 1e100;

  for (int step = 0; step < BUBEN; step++) {
    ld wait = M_PI * step / BUBEN;

    pt c{-sin(wait) * r, cos(wait) * r};

    ld d = dist(c, p);
    if (d < r) continue;

    ld ang = atan2(vp(pt() - c, p - c), sp(pt() - c, p - c));
    if (ang < 0) ang += 2 * M_PI;
    ld ang2 = acos(r / d);

    if (ang2 > ang) continue;

    ld t = sqrt(d * d - r * r);

    ld res = wait / w + ((ang - ang2) * r + t) / v;
    ans = min(ans, res);
  }
  return ans;
}

ld solve2(pt , ld , ld ) {
  return 1e100;
}


int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  ld x, y;
  ld v, w;


//  x = y = v = w = 10;
  while (cin >> x >> y >> v >> w) {
    y = abs(y);
    double ans = min(solve1({x, y}, v, w), solve2({x, y}, v, w));
    printf("%.18f\n", ans);
  }

  return 0;
}
