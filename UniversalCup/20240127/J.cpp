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
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
  #endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    set<ll> s;
    int n, m;
    scanf("%d%d", &n, &m);
    s.insert(0);
    s.insert((1LL << n) - 1);
    for (int r = 0; r <= n; r++) {
      for (int l = 0; l < r; l++) {
        if ((int)s.size() < m) {
          s.insert((1LL << r) - (1LL << l));
        }
      }
    }
    for (ll x : s) {
      printf("%lld ", x);
    }
    printf("\n");
  }

  return 0;
}
