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

void solve() {
  double v;
  scanf("%lf", &v);
  int n;
  scanf("%d", &n);
  double L = 0;
  double R = 1e100;
  for (int i = 0; i < n; i++) {
    double x, y;
    scanf("%lf%lf", &x, &y);
    double A, B, C;
    A = - 5 * x * x / v / v;
    B = x;
    C = A - y;
    double D = B * B - 4 * A * C;
    L = max(L, (-B + sqrt(D)) / (2 * A));
    R = min(R, (-B - sqrt(D)) / (2 * A));
  }
  printf("%.3lf\n", (L + R) / 2);
  eprintf("%.18lf %.18lf\n", L, R);
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int z;
  scanf("%d", &z);
  while (z-->0) {
    solve();
  }
  return 0;
}
