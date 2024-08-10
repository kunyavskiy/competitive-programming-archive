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

void solve(int n) {
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    g[a-1].push_back(b - 1);
    g[b-1].push_back(a - 1);
  }
  vector<int> a(n), b(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }
  vector<int> size(n);
  auto dfs_size = [&](auto self, int v, int p) -> void {
    auto it = find(g[v].begin(), g[v].end(), p);
    if (it != g[v].end()) g[v].erase(it);
    size[v] = 1;
    for (int u : g[v]) {
      self(self, u, v);
      size[v] += size[u];
    }
    sort(g[v].begin(), g[v].end(), [&](int x, int y) { return size[x] > size[y];});
  };
  dfs_size(dfs_size, 0, -1);

  vector<int> ans(n, -1);
#ifdef LOCAL
  constexpr int MAX = 1 << 4;
  constexpr int LIM = 8;
#else
  constexpr int MAX = 1 << 20;
  constexpr int LIM = 512;
#endif

  auto add = [](vector<int> x, int val) {
    vector<int> res(LIM, std::numeric_limits<int>::max() / 2);
    for (int i = 0; i < LIM; i++) {
      res[i] = min(x[i], x[(i - val) & (LIM - 1)] + val);
    }
    return res;
  };

  auto dfs_solve = [&](auto self, int v, int cur, vector<int> mins) -> void {
    while (true) {
      vector<int> cp;
      if (cur >= LIM) {
        a[v] = cur;
        cp = mins;
        ans[v] = (b[v] & (cur - 1)) == 0;
        cur /= 2;
      } else {
        cp = add(mins, a[v]);
        ans[v] = cp[b[v] & (LIM - 1)] <= b[v];
      }
      if (g[v].empty()) break;
      for (int i = 1; i < (int)g[v].size(); i++) {
        self(self, g[v][i], cur, cp);
      }
      v = g[v][0];
      mins = cp;
    }
  };

  vector<int> cur(LIM, numeric_limits<int>::max() / 2);
  cur[0] = 0;
  dfs_solve(dfs_solve, 0, MAX, cur);
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    printf("%d", ans[i]);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }

  return 0;
}
