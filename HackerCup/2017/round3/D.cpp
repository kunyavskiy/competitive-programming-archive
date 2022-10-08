//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "D"

typedef long long ll;
typedef long double ld;

const int MAXN = 65;

const ll INF = 1LL << 61;

ll dp[MAXN][MAXN];
int a[MAXN];

ll max3(ll a, ll b, ll c) {
  return max(a, max(b, c));
}

void solve() {
  memset(dp, 0, sizeof(dp));
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
    k -= a[i];
  }

  memset(dp, -1, sizeof(dp));

  for (int i = 0; i < n; i++) {
    dp[i][0] = 0;
    for (int j = 1; j <= i + 1; j++) {
      if (a[i] == 1) {
        if (i == 0) {
          dp[i][j] = -1;
        } else if (dp[i - 1][j] <= 0) {
          dp[i][j] = dp[i - 1][j];
        } else {
          dp[i][j] = min(INF, 2 * dp[i - 1][j] + 1);
        }
      } else {
        int zs = 0;
        while (zs <= i && a[i - zs] == 0) zs++;
        if (zs == i + 1) {
          if (j == 0 || j == zs) {
            dp[i][j] = 0;
          } else if (zs > j) {
            dp[i][j] = -1;
          } else {
            dp[i][j] = INF;
          }
          continue;
        }

        dp[i][j] = -1;
        for (int t = 0; t <= zs && t <= j; t++) {
          ll cur = dp[i - zs][j - t];
          if (cur == -1) continue;
          if (dp[i][j] != -1) {
            cur = (cur << zs) + (1LL << zs) - ((1LL << t) - 1);
          } else {
            cur = (1 << zs) - (1LL << (t + 1)) + (t == 0 ? 1 : 2);
          }
          cur = min(cur, INF);
          dp[i][j] = max(dp[i][j], cur);
        }
      }
    }
    for (int j = 0; j <= i + 1; j++) {
      eprintf("%lld ", dp[i][j]);
    }
    eprintf("\n");
  }

  if (dp[n - 1][k] == INF) {
    printf("-1\n");
  } else {
    assert(dp[n - 1][k] < INF);
    printf("%lld\n", dp[n - 1][k]);
  }

}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}
