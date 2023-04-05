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

const int MOD = 998244353;

void add(int & a, int b) {
  if ((a += b) >= MOD) {
    a -= MOD;
  }
}

int prod(int a, int b) {
  return int((ll(a) * b) % MOD);
}

void mult(int & a, int b) {
  a = prod(a, b);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  if (n == 1) {
    printf("1\n");
    return 0;
  }
  vector<vector<int>> ed(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    ed[u].push_back(v);
    ed[v].push_back(u);
  }

  vector<int> cycles(1 << n, 0);
  for (int cnt = n; cnt >= 2; --cnt) {
    vector<vector<int>> dp(1 << n, vector<int>(n, 0));
    dp[1 << (cnt - 1)][cnt - 1] = 1;
    for (int mask = 1; mask < (1 << cnt); ++mask) {
      for (int last = 0; last < cnt; ++last) {
        if (dp[mask][last] == 0) { continue; }
        for (int next : ed[last]) {
          if (next >= cnt || (mask & (1 << next))) { continue; }
          add(dp[mask | (1 << next)][next], dp[mask][last]);
        }
      }
    }
    for (int mask = 0; mask < (1 << n); ++mask) {
      for (int v : ed[cnt - 1]) {
        if (mask == ((1 << v) | (1 << (cnt - 1)))) { continue; }
        cycles[mask] += dp[mask][v];
      }
    }
  }
  for (int & x : cycles) {
    mult(x, (MOD + 1) / 2);
  }
  for (int u = 0; u < n; ++u) {
    for (int v : ed[u]) {
      if (u < v) {
        add(cycles[(1 << u) | (1 << v)], 1);
      }
    }
  }
//  for (int i = 0; i < n; ++i) {
//    cycles[1 << i] = 1;
//  }

//  for (int mask = 0; mask < (1 << n); ++mask) {
//    eprintf("cycles[%d] = %d\n", mask, cycles[mask]);
//  }

  vector<vector<int>> dp(1 << n, vector<int>(n + 1, 0));
  for (int mask = 1; mask < (1 << n); ++mask) {
    dp[mask][n] = cycles[mask];
    for (int k = n - 1; k >= 0; --k) {
      dp[mask][k] = dp[mask][k + 1];
      if (mask & (1 << k)) {
        if (mask == (1 << k)) { continue;}
        int k2 = __builtin_ctz(mask ^ (1 << k));
        int all = (mask ^ (1 << k) ^ (1 << k2));
        for (int msk = all; msk > 0; msk = (msk - 1) & all) {
          int mask1 = ((all ^ msk) | (1 << k) | (1 << k2));
          int mask2 = (msk | (1 << k));
          add(dp[mask][k], prod(dp[mask1][k + 1], dp[mask2][k]));
        }
      }
    }
  }
//  for (int mask = 0; mask < (1 << n); ++mask) {
//    eprintf("dp[%d] =", mask);
//    for (int k = 0; k <= n; ++k) {
//      eprintf(" %d", dp[mask][k]);
//    }
//    eprintf("\n");
//  }
  printf("%d\n", dp[(1 << n) - 1][0]);

  return 0;
}
