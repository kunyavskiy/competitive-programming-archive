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

class DSU {
public:
  vector<int> p, sz;
  explicit DSU(int n) : p(n), sz(n) {
    for (int i = 0; i < n; i++) {
      p[i] = i;
      sz[i] = 1;
    }
  }

  int get(int v) {
    if (p[v] == v) return v;
    return p[v] = get(p[v]);
  }

  bool join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return false;
    if (sz[a] > sz[b]) swap(a, b);
    p[a] = b;
    sz[b] += sz[a];
    return true;
  }
};

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  };
  DSU d(n);
  vector<int> order(n);
  for (int i = 0; i < n; i++) {
    order[i] = i;
  }
  sort(order.begin(), order.end(), [&](int a, int b) { return g[a].size() < g[b].size(); });
  vector<bool> done(n);
  vector<vector<int>> ans(n);
  for (int x : order) {
    done[x] = true;
    int dd = 0;
    for (int y : g[x]) {
      if (done[y]) {
        dd++;
        if (d.join(x, y)) {
          ans[x].push_back(y);
        }
      }
    }
    //eprintf("x = %d, dd = %d, sz = %d\n", x, dd, d.sz[d.get(x)]);
    if (dd + 1 != d.sz[d.get(x)]) {
      printf("No\n");
      return;
    }
  }
  printf("Yes\n");
  for (int x : order) {
    printf("%d %d", x + 1, (int)ans[x].size());
    for (int y : ans[x]) {
      printf(" %d", y +1);
    }
    printf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t;i++) {
    solve();
  }

  return 0;
}
