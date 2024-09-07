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

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

static const double EPS = 1e-6;
int solve() {
  int x1, y1, z1, p1, q1;
  int x2, y2, z2, p2, q2;
  scanf("%d%d%d%d%d", &x1, &y1, &z1, &p1, &q1);
  scanf("%d%d%d%d%d", &x2, &y2, &z2, &p2, &q2);

  if ((x1 - x2) * p1 + (y1 - y2) * q1 == 0 && (x1 - x2) * p2 + (y1 - y2) * q2 == 0) {
    return 2;
  }

  int a1 = p1;
  int b1 = q1;
  int c1 = -x1 * a1 - y1 * b1;

  int a2 = p2;
  int b2 = q2;
  int c2 = -x2 * a2 - y2 * b2;

  if (a1 * b2 - a2 * b1 == 0) return 4;
  double xi = (b1 * c2 - c1 * b2) * 1.0 / (a1 * b2 - a2 * b1);
  double yi = - (a1 * c2 - a2 * c1) * 1.0 / (a1 * b2 - a2 * b1);
#ifdef LOCAL
  assert(fabs(a1 * x1 + b1 * y1 + c1) < EPS);
  assert(fabs(a1 * xi + b1 * yi + c1) < EPS);
  assert(fabs(a2 * xi + b2 * yi + c2) < EPS);
#endif
  
  if (z1 == z2) {
    if (fabs(xi - x1) < EPS && fabs(yi - y1) < EPS) return 4;
    if (fabs(xi - x2) < EPS && fabs(yi - y2) < EPS) return 4;
  }

  double s = z2 - z1;
  double p = - (xi - x1) * (x2 - xi) - (yi - y1) * (y2 - yi);
  double d = s * s - 4 * p;
  eprintf("d = %lf, s = %lf, p = %lf\n", d, s, p);
  if (d < -EPS) return 4;
  return 3;
}

int main() {
  #ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
  #endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    printf("%d\n", solve());
  }

  return 0;
}
