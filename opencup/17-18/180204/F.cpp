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

const int MAXN = 15;
const ll INF = 1LL << 60;

int g[MAXN][MAXN];
ll dp[1 << MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      scanf("%d", &g[i][j]);
      g[j][i] = g[i][j];
    }
  }

  for (int mask = 0; mask < (1 << n); mask++) {
    for (int v = 0; v < n; v++) {
      dp[mask][v] = INF;
      if ((mask & (1 << v)) == 0) {
        continue;
      }

      if (__builtin_popcount(mask) == 1) {
        dp[mask][v] = 0;
        continue;
      }

      for (int j = mask & (mask - 1); j; j = (j - 1) & mask) {
        if (j & (1 << v)) continue;
        dp[mask][v] = min(dp[mask][v], dp[mask ^ j][v] + dp[j | (1 << v)][v]);
      }

      for (int nv = 0; nv < n; nv++) {
        if ((mask & (1 << nv)) && nv != v) {
          int cnt = __builtin_popcount(mask) - 1;
          ll coef = cnt * (n - cnt);
          dp[mask][v] = min(dp[mask][v], dp[mask ^ (1 << v)][nv] + g[v][nv] * coef);
        }
      }
    }
  }

  printf("%lld\n", dp[(1 << n) - 1][0]);
  return 0;
}
