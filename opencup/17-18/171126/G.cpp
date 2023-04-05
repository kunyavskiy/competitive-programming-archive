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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  vector<int> deg(n);
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<double> dist(n, 1e18);
  dist[n - 1] = 0;
  vector<double> sum(n);

  priority_queue<pair<double, int>> q;
  q.push({0.0, n - 1});

  vector<bool> used(n);

  while (!q.empty()) {
    int v = q.top().second;
    q.pop();
    if (used[v]) continue;
//    eprintf("%d %.5f\n", v, dist[v]);
    used[v] = true;

    for (int u : g[v]) {
      sum[u] += dist[v];
      deg[u]++;
      double cur = (g[u].size() + sum[u]) / deg[u];
      dist[u] = min(dist[u], cur);
      q.push({-dist[u], u});
    }
  }

  printf("%.18f\n", dist[0]);

  return 0;
}
