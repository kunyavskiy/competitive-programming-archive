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

void solve() {
  int n;
  scanf("%d", &n);
  vector<ll> v(n);
  for (auto& x : v) scanf("%lld", &x);
  set<pair<ll, int>, greater<>> a;
  for (int i = 0; i < n; i++) {
    if (v[i]) {
      a.emplace(v[i], i);
    }
  }
  vector<pair<int, ll>> ans;
  while (!a.empty()) {
    auto [a1, id1] = *a.begin();
    a.erase(a.begin());
    auto [a2, id2] = *a.begin();
    a.erase(a.begin());
    if (!a.empty()) {
      auto [a3, id3] = *a.begin();
      if (__builtin_clzll(a3) == __builtin_clzll(a1)) {
        printf("-1\n");
        return;
      }
    }
    ans.emplace_back(id1, a1);
    if (a1 != a2) {
      a.emplace(a1 ^ a2, id2);
    }
  }
  printf("%d\n", (int)ans.size());
  for (auto [x, y]: ans) {
    printf("%d %lld\n", x + 1, y);
  }
}

int main() {
  #ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
  #endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
