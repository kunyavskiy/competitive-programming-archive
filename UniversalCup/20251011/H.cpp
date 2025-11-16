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

void solve() {
  int n, d;
  scanf("%d%d", &n, &d);
  vector<int> a(n);
  for (int& x: a) scanf("%d", &x);
  int ptr = 0;
  int ans = 0;
  int k = accumulate(a.begin(), a.end(), 0LL) / n;
  for (int i = 0; i < n; i++) {
    int cur = k;
    while (cur > 0) {
      int to_use = min(cur, a[ptr]);
      cur -= to_use;
      a[ptr] -= to_use;
      if (to_use > 0) {
        ans = max(ans, abs(ptr - i));
      }
      if (a[ptr] == 0) {
        ptr++;
      }
    }
  }
  printf("%d\n", (ans + d - 1) / d);
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
