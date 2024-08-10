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

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    auto mul = [&](int& x, int y) {
      x = (x * 1LL * y) % m;
    };
    int hi = n / 2;
    int lo = n - hi;

    vector<vector<int>> ans(n + 1, vector<int>(1 << n, 1));
    vector<int> pop(1 << lo);
    for (int i = 0; i < (int)pop.size(); i++) {
      pop[i] = __builtin_popcount(i);
    }
    for (int i = 0; i < k; i++) {
      int c, d, x;
      scanf("%d%d%d", &c, &d, &x);
      for (int j = 0; j < (1 << hi); j++) {
        if (pop[j] > d) {
          continue;
        }
        mul(ans[d - pop[j]][c ^ (j << lo)], x);
      }
    }
    vector<int> res(1 << n);
    for (int i = 0; i < (1 << n); i++) {
      int& x = res[i];
      x = 1;
      for (int j = 0; j < (1 << lo); j++) {
        mul(x, ans[pop[j]][i ^ j]);
      }
    }

    for (int i = 0; i < (1 << n); i++) {
      printf("%d ", res[i]);
    }
    printf("\n");
  }

  return 0;
}
