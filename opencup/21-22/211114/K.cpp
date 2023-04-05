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

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m)== 2) {
    vector<int> c(m);
    for (int i = 0; i < m; i++) {
      scanf("%d", &c[i]);
    }
    vector<vector<int>> gf(n, vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) {
      gf[i][i] = 0;
    }
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
      int a, b, w;
      scanf("%d%d%d", &a, &b, &w);
      --a, --b, --w;
      gf[a][b] = gf[b][a] = 1;
      g[a].emplace_back(b, w);
      g[b].emplace_back(a, w);
    }
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          gf[i][j] = min(gf[i][j], gf[i][k] + gf[k][j]);
        }
      }
    }
    for (int i = 0; i < n; i++) {
      g[i].erase(
        remove_if(g[i].begin(), g[i].end(), [&](const pair<int, int>& x) { return gf[0][x.first] != gf[0][i] + 1; }),
        g[i].end());
    }
    vector<int> now(m);
    vector<int> ans(n, 1e9);
    auto dfs = [&](int v, int cost, auto dfs) -> void {
      ans[v] = min(ans[v], cost);
      for (auto [u, w] : g[v]) {
        now[w]++;
        dfs(u, cost + c[w] * now[w], dfs);
        now[w]--;
      }
    };
    dfs(0, 0, dfs);
    for (int i = 1; i < n; i++) {
      printf("%d\n", ans[i]);
      assert(ans[i] > 0);
      assert(ans[i] < 1e9);
    }
  }

  return 0;
}
