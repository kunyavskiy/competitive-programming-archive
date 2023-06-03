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
#include <numeric>
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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

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

struct edge {
  int u, v, w, id;
};

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<edge> es(m);
  vector<vector<pair<int, int>>> g(n);
  vector<bool> ing(m);
  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &es[i].u, &es[i].v, &es[i].w);
    es[i].id = i;
    --es[i].u, --es[i].v;
    g[es[i].u].emplace_back(es[i].v, i);
    g[es[i].v].emplace_back(es[i].u, i);
    ing[i] = i < n - 1;
  }
  vector<int> ids(m);
  std::iota(ids.begin(), ids.end(), 0);
  stable_sort(ids.begin(), ids.end(),
              [&](int a, int b) { return es[a].w < es[b].w; });

  vector<pair<int, int>> ops;
  auto dfs = [&](auto dfs, int from, int p, int to) -> int {
    if (from == to) return -2;
    for (auto [v, id]  : g[from]) {
      if (!ing[id] || v == p)
        continue;
      auto r = dfs(dfs, v, from, to);
      if (r == -1) { continue; }
      if (r == -2 || es[r].w < es[id].w) return id;
      return r;
    }
    return -1;
  };
  for (auto eid : ids) {
    if (ing[eid]) {
      continue;
    }
    int mx = dfs(dfs, es[eid].u, -1, es[eid].v);
    if (es[mx].w > es[eid].w) {
      ops.emplace_back(mx + 1, eid + 1);
      ing[mx] = false;
      ing[eid] = true;
    }
  }

  printf("%d\n", (int)ops.size());
  for (auto [x, y] : ops) {
    printf("%d %d\n", x, y);
  }


  return 0;
}
