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

void solve(int n, int m) {
  vector<int> v(n);
  vector<int> pos(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    pos[v[i]] = i;
  }
  vector<pair<int, int>> segs(m);
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &segs[i].first, &segs[i].second);
    --segs[i].first;
    --segs[i].second;
  }
  auto left_cmp = [&](int x, int y) { return std::make_tuple(segs[x].first, x) < std::make_tuple(segs[y].first, y); };
  auto right_cmp = [&](int x, int y) { return std::make_tuple(-segs[x].second, x) < std::make_tuple(-segs[y].second, y); };
  set<int, decltype(left_cmp)> lf(left_cmp);
  set<int, decltype(right_cmp)> rg(right_cmp);
  for (int i = 0; i < m; i++) {
    lf.insert(i);
    rg.insert(i);
  }

  bool has_empty = false;
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    vector<int> noi;
    segs.push_back({pos[i], pos[i]});
    while (true) {
      auto it = lf.upper_bound(segs.size() - 1);
      if (it != lf.end()) {
        int val = *it;
        noi.push_back(val);
        lf.erase(val);
        rg.erase(val);
      } else {
        break;
      }
    }

    while (true) {
      auto it = rg.upper_bound(segs.size() - 1);
      if (it != rg.end()) {
        int val = *it;
        noi.push_back(val);
        lf.erase(val);
        rg.erase(val);
      } else {
        break;
      }
    }
    if (noi.empty()) {
      segs.pop_back();
      continue;
    }
    int es = noi.size() - 1 + has_empty;
    ans += es * 1LL * i;
    int maxl = 0;
    int minr = n + 1;
    for (int x : noi) {
      maxl = max(maxl, segs[x].first);
      minr = min(minr, segs[x].second);
    }
    if (maxl <= minr && !has_empty) {
      segs.back() = {maxl, minr};
      lf.insert(segs.size() - 1);
      rg.insert(segs.size() - 1);
    } else {
      has_empty = true;
    }
  }
  ans += n * 1LL * (((int)lf.size()) - 1 + has_empty);
  printf("%lld\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    solve(n, m);
  }
  return 0;
}
