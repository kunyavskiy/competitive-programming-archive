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

const int INF = numeric_limits<int>::max() / 4;

void solve() {
  int n, m, s, t;
  scanf("%d %d %d %d", &n, &m, &s, &t);
  --s, --t;
  vector<vector<int>> g(n,vector<int>(n, INF));
  for (int i = 0; i < n; i++) {
    g[i][i] = 0;
  }
  vector<int> p(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &p[i]);
  }
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a][b] = p[b];
  }

  auto floyd = [&]() {
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
          g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
      }
    }
  };
  floyd();
  vector<vector<int>> ng(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == j) {
        ng[i][j] = 0;
      } else {
        ng[i][j] = g[i][j] + g[j][i] - p[i];
      }
    }
  }
  g = std::move(ng);
  floyd();
  int ans = g[s][t] + p[s];
  if (ans >= INF) ans = -1;
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
