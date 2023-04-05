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

void bfs(const vector<vector<int>>& g, const vector<int> &start, vector<int>& color, vector<int> &d) {
  color = vector<int>(g.size(), -1);
  d = vector<int>(g.size(), -1);
  queue<int> q;
  for (int i = 0; i < (int)start.size(); i++) {
    d[start[i]] = 0;
    color[start[i]] = i;
    q.push(start[i]);
  }
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    for (int u : g[v]) {
      if (color[u] == -1) {
        color[u] = color[v];
        d[u] = d[v] + 1;
        q.push(u);
      }
    }
  }
}

vector<vector<int>> solve(const vector<vector<int>>& g, int u, int v) {
  vector<int> c, d;
  bfs(g, {u, v}, c, d);
  vector<int> layer;
  for (int i = 0; i < (int)g.size(); i++) {
    if (c[i] == 0) {
      layer.push_back(i);
    }
  }
  if (g.size() % layer.size() != 0) {
    return {};
  }
  int layers = g.size() / layer.size();
  bfs(g, layer, c, d);
  vector<vector<int>> ans(layers, vector<int>(layer.size(), -1));
  for (int i = 0; i < (int)g.size(); i++) {
    assert(d[i] >= 0);
    assert(0 <= c[i] && c[i] < (int) layer.size());
    if (d[i] >= layers || ans[d[i]][c[i]] != -1) {
      return {};
    }
    ans[d[i]][c[i]] = i;
  }
  int zfes = 0;
  int es = 0;
  for (int a = 0; a < (int)g.size(); a++) {
    for (int b : g[a]) {
      es++;
      if (c[a] == c[b]) {
        if (abs(d[a] - d[b]) != 1) {
          return {};
        }
      } else {
        if (d[a] != d[b]) {
          return {};
        }
        if (d[a] == 0) {
          zfes++;
        } else {
          int za = ans[0][c[a]];
          int zb = ans[0][c[b]];
          if (!binary_search(g[za].begin(), g[za].end(), zb)) {
            return {};
          }
        }
      }
    }
  }
  if (es != 2 * (ll)layer.size() * (layers - 1) + zfes * 1LL * layers) {
    return {};
  }
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
      sort(g[i].begin(), g[i].end());
    }
    int mind = 0;
    for (int i = 0; i < n; i++) {
      if (g[i].size() < g[mind].size()) {
        mind = i;
      }
    }
    vector<vector<int>> ans;
    ans.resize(1);
    ans[0].resize(n);
    std::iota(ans[0].begin(), ans[0].end(), 0);
    for (int other : g[mind]) {
      auto ans2 = solve(g, mind, other);
      if (ans2.size() > ans.size()) {
        ans = ans2;
      }
    }
    printf("%zd %zd\n", ans.size(), ans[0].size());
    for (const auto &x : ans) {
      for (int y : x) {
        printf("%d ", y + 1);
      }
      printf("\n");
    }
  }

  return 0;
}
