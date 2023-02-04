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

struct point {
    int x, y;
    point operator-(const point& other) const {
        return point{other.x - x, other.y - y};
    }
    ll operator*(const point& other) const {
        return x * 1LL * other.y - y * 1LL * other.x;
    }
};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
      vector<vector<int>> ga(n);
      vector<vector<int>> gb(n);
      for (int i = 0; i < m; i++) {
          int u, v, c;
          scanf("%d%d%d", &u, &v, &c);
          if (c == 0) ga[v - 1].push_back(u - 1); else gb[v - 1].push_back(u - 1);
      }

      auto stupid = [&] (int a, int b, int x) {
          vector<ll> dp(n);
          for (int i = 1; i < n; i++) {
              dp[i] = std::numeric_limits<ll>::max() / 2;
              for (int pa: ga[i]) {
                  dp[i] = min(dp[i], dp[pa] + a);
              }
              for (int pa: gb[i]) {
                  dp[i] = min(dp[i], dp[pa] + b);
              }
          }
          return dp[x];
      };

      vector<vector<point>> ans(n);
      ans[0].push_back({0, 0});

      vector<int> best(n, std::numeric_limits<int>::max());
      for (int i = 1; i < n; i++) {
          vector<int> touched;
          auto add = [&](int x, int y) {
              if (best[x] == numeric_limits<int>::max()) {
                  touched.push_back(x);
              }
              best[x] = min(best[x], y);
          };
          for (int p : ga[i]) {
              for (auto [x, y] : ans[p]) {
                  add(x + 1, y);
              }
          }
          for (int p : gb[i]) {
              for (auto [x, y] : ans[p]) {
                  add(x, y + 1);
              }
          }
          sort(touched.begin(), touched.end());
          auto bad = [](point a, point b, point c) {
              return (b - a) * (c - a) <= 0;
          };
          auto &cur = ans[i];
          for (int x: touched) {
              auto next = point{x, best[x]};
              while (cur.size() >= 2 && bad(cur[cur.size() - 2], cur[cur.size() - 1], next)) {
                  cur.pop_back();
              }
              cur.emplace_back(next);
              best[x] = numeric_limits<int>::max();
          }
#ifdef LOCAL
          eprintf("%d: ", i);
          for (auto [x, y] : ans[i]) {
              eprintf("(%d, %d) ", x, y);
          }
          eprintf("\n");
#endif
      }

      int q;
      scanf("%d", &q);
      for (int i = 0; i < q; i++) {
          int a, b, x;
          scanf("%d%d%d", &a, &b, &x);
          const auto &hull = ans[x - 1];

          point dir{-b, a};

          ll result;
          if (hull.empty()) {
              result = std::numeric_limits<ll>::max() / 2;
          } else {
              int l = 0;
              int r = hull.size() - 1;
              while (r - l > 1) {
                  int mid = (l + r) / 2;
                  if (((hull[mid + 1] - hull[mid]) * dir) <= 0) {
                      r = mid;
                  } else {
                      l = mid;
                  }
              }
              eprintf("l = %d, r = %d, (%d, %d) or (%d, %d)\n", l, r, hull[l].x, hull[l].y, hull[r].x, hull[r].y);
              result = min(hull[l].x * 1LL * a + hull[l].y * 1LL * b, hull[r].x * 1LL * a + hull[r].y * 1LL * b);
          }
#ifdef LOCAL
          if (result != stupid(a, b, x - 1)) {
              eprintf("FAIL on %d %d %d: %lld vs %lld\n", a, b, x, result, stupid(a, b, x - 1));
              assert(false);
          }
#endif
          printf("%lld\n", result);
      }
  }

  return 0;
}
