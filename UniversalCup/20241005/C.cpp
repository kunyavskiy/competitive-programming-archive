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
#include <numeric>
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

int main() {
  #ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
  #endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n), c(n), d(n);
    for (int &x : a)
      scanf("%d", &x);
    for (int &x : b)
      scanf("%d", &x);
    for (int &x : c)
      scanf("%d", &x);
    for (int &x : d)
      scanf("%d", &x);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      ans += a[i];
      b[i] -= a[i];
    }
    sort(b.begin(), b.end());
    vector<ll> cs(n + 1), ds(n + 1);
    for (int i = 0; i< n; i++) {
      cs[i + 1] = cs[i] + c[i];
      ds[i + 1] = ds[i] + d[i];
    }
    ll res = std::numeric_limits<ll>::max();
    for (int i = 0; i <= n; i++) {
      res = min(res, ans + cs[n - i] + ds[i]);
      if (i != n) ans += b[i];
    }
    printf("%lld\n", res);
  }

  return 0;
}
