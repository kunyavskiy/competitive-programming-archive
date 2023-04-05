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

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }

    const int LOG = 20;

    vector<vector<int>> up(LOG, vector<int>(n));
    vector<int> h(n);

    function<void(int,int)> dfs = [&](int v, int p) {
      up[0][v] = p;
      for (int i : g[v]) {
        if (i != p) {
          h[i] = h[v] + 1;
          dfs(i, v);
        }
      }
    };

    dfs(0, 0);

    for (int i = 1; i < LOG; i++) {
      for (int j = 0; j < n; j++) {
        up[i][j] = up[i-1][up[i-1][j]];
      }
    }

    auto lca = [&](int u, int v) {
      if (h[u] < h[v]) {
        swap(u, v);
      }
      for (int i = LOG - 1; i >= 0; i--) {
        if (h[u] - (1 << i) >= h[v]) {
          u = up[i][u];
        }
      }
      if (u == v) return u;
      for (int i = LOG - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
          u = up[i][u];
          v = up[i][v];
        }
      }
      return up[0][u];
    };

    for (int i = 0; i < q; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      int l = h[a] + h[b] - 2 * h[lca(a, b)] + 1;
      eprintf("l = %d\n", l);
      printf("%lld\n", n - l + l * 1LL * (l + 1) / 2);
    }

  }

  return 0;
}
