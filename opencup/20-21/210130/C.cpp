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

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> g(n);
  for (int i = 0; i < n; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  vector<int> used(n);
  vector<int> cycle;

  auto dfs = [&](int v, int p, auto dfs) {
    used[v] = 1;
    cycle.push_back(v);
    for (int u : g[v]) {
      if (u == p) continue;
      if (used[u] == 1) {
        cycle.erase(cycle.begin(), find(cycle.begin(), cycle.end(), u));
        return true;
      }
      if (used[u] == 0) {
        if (dfs(u, v, dfs)) {
          return true;
        }
      }
    }
    cycle.pop_back();
    used[v] = 2;
    return false;
  };
  assert(dfs(0, -1, dfs));
  assert(cycle.size() >= 3);

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (g[i].size() == 1) {
      ans++;
    }
  }

  int ans2 = 0;

  cycle.push_back(cycle[0]);
  for (int i = 1; i < (int)cycle.size(); i++) {
    int u = cycle[i];
    int v = cycle[i - 1];
    if (g[u].size() == 2 && g[v].size() == 2) {
      ans2 = max(ans2, 2);
    } else if (g[u].size() == 2) {
      ans2 = max(ans2, 1);
    }
  }

  printf("%d\n", max(ans + ans2, 3));
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int z;
  scanf("%d", &z);
  while (z-->0) {
    solve();
  }

  return 0;
}
