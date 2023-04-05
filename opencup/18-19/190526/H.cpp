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
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a, --b;
      g[a].push_back({b, c});
      g[b].push_back({a, c});
    }

    auto dijkstra = [&](int v) {
      set<pair<ll, int>> s;
      vector<ll> d(n, 1LL << 60);
      d[v] = 0;
      s.insert({0, v});
      while (!s.empty()) {
        v = s.begin()->second;
        s.erase(s.begin());
        for (auto to : g[v]) {
          int u = to.first;
          ll nd = d[v] + to.second;
          if (d[u] > nd) {
            s.erase({d[u], u});
            d[u] = nd;
            s.insert({d[u], u});
          }
        }
      }
      return vector<ll>(d.begin(), d.begin() + 13);
    };

    vector<vector<ll>> d(13);
    for (int i = 0; i < 13; i++) {
      d[i] = dijkstra(i);
    }

    vector<vector<ll>> dp(13, vector<ll>(1 << 13, 1LL << 60));
    dp[0][1] = 0;
    for (int mask = 0; mask < (1 << 13); mask++) {
      for (int u = 0; u < 13; u++) {
        if (mask & (1 << u)) {
          for (int v = 0; v < 13; v++) {
            if (!(mask & (1 << v))) {
              ll &to = dp[v][mask | (1 << v)];
              to = min(to, dp[u][mask] + d[v][u]);
            }
          }
        }
      }
    }
    ll ans = 1LL << 60;
    for (int i = 0; i < 13; i++) {
      ans = min(ans, dp[i][(1 << 13) - 1] + d[i][0]);
    }
    printf("%lld\n", ans);
  }

  return 0;
}
