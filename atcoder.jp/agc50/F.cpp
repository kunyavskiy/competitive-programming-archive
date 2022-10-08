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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

int nand(int a, int b) {
  return !a || !b;
}

int solve(vector<pair<int, int>> es, vector<int> vals, int root, int a, int b) {
  auto cont = [&](int &root, int a) {
    auto it = find(es.begin(), es.end(), pair<int, int>{min(root, a), max(root, a)});
    assert(it != es.end());
    es.erase(it);
    vals[root] = nand(vals[root], vals[a]);
    for (auto &[x, y] : es) {
      if (x == a) x = root;
      if (y == a) y = root;
    }
  };
  vector<vector<int>> g(es.size() + 1);
  cont(root, a);
  cont(root, b);
  for (auto & e : es) {
    g[e.first].push_back(e.second);
    g[e.second].push_back(e.first);
  }
  int res = vals[root];
  int ans = 1;
  vector<int> size(g.size());
  auto dfs = [&](int v, int p, auto dfs) -> int {
    if (vals[v] == 0 && v != root) ans = 0;
    if (v != root) res = nand(res, 1);
    size[v] = 1;
    int already = 0;
    for (int u : g[v]) {
      if (u != p) {
        size[v] += dfs(u, v, dfs);
        if (size[u] & already) ans = 0;
        already |= size[u];
      }
    }
    return size[v];
  };
  dfs(root, -1, dfs);
  return ans && res;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> vals(n);
    vector<pair<int, int>> g;
    for (int i = 0; i < n - 1; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g.emplace_back(a, b);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &vals[i]);
    }
    if (n == 2) {
      printf("%d\n", nand(vals[0], vals[1]));
      continue;
    }
    int ans = 0;
    for (auto [a, b] : g) {
      for (auto [c, d] : g) {
        if (a == c && b != d) ans += solve(g, vals, a, b, d);
        if (a == d && b != c) ans += solve(g, vals, a, b, c);
        if (b == c && a != d) ans += solve(g, vals, b, a, d);
        if (b == d && a != c) ans += solve(g, vals, b, a, c);
      }
    }
    printf("%d\n", ans % 2);
  }


  return 0;
}
