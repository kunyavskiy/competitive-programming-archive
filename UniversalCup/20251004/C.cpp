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

vector<pair<int, int>> get_cuts(int n) {
  vector<pair<int, int>> ret;
  for (int i = 1; i * i <= n; ++i) {
    ret.emplace_back((n + i - 1) / i, i);
  }
  int last = ret.back().second;
  for (int j = 1; (n + j - 1) / j > last; ++j) {
    ret.emplace_back(j, (n + j - 1) / j);
  }
  ranges::sort(ret);
  return ret;
}

int solve(int h, int w, int s) {
  auto ca = get_cuts(h);
  auto cb = get_cuts(w);
  ranges::reverse(cb);
  int ptr = 0;
  int ans = std::numeric_limits<int>::max();
  for (auto [maxs, cuts] : ca) {
    while (ptr < (int)cb.size() && cb[ptr].first * 1LL * maxs > s) {
      ptr++;
    }
    if (ptr < (int)cb.size()) {
      ans = min(ans, cb[ptr].second + cuts - 2);
    }
  }
#ifdef LOCAL
  int ans2 = std::numeric_limits<int>::max();
  for (int i = 1; i <= h; i++) {
    for (int j = 1; j <= w; j++) {
      if (((h + i - 1) / i) * 1LL * ((w + j - 1) / j) <= s) {
        ans2 = min(ans2, i + j - 2);
      }
    }
  }
  if (ans != ans2) {
    eprintf("%d %d %d, ans1=%d,ans2=%d\n", h, w, s, ans, ans2);
    assert(false);
  }
#endif
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    int h, w, s;
    scanf("%d%d%d", &h, &w, &s);
    printf("%d\n", solve(h, w, s));
  }

  return 0;
}
