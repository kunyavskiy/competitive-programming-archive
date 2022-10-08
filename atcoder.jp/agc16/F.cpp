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

int g[20];
int dp[(1 << 15)];
int n;

const int MOD = 1000000007;

int add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

int mult(int a, int b) {
  return (a * 1LL * b) % MOD;
}


void solve(int mask) {
  int& ans = dp[mask];
  ans = 0;
  for (int submask = mask; submask != 0; submask = (submask - 1) & mask) {
    if ((submask & 1) != ((submask >> 1) & 1)) continue;
    int coef = 1;
    for (int j = 0; j < n; j++) {
      if (!(mask & (1 << j))) {
        int c = __builtin_popcount(g[j] & submask);
        coef = mult(coef, (1 << c) - 1);
      }
      if (submask & (1 << j)) {
        int c = __builtin_popcount(g[j] & ~mask);
        coef = mult(coef, (1 << c));
      }
    }
    add(ans, mult(coef, dp[mask ^ submask]));
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int m;
  while (scanf("%d%d", &n, &m) == 2) {
    memset(g, 0, sizeof(g));
    memset(dp, -1, sizeof(dp));

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a] |= (1 << b);
    }

    dp[0] = 1;

    for (int mask = 1; mask < (1 << n); mask++) {
      solve(mask);
    }

    int ans = 1;
    for (int i = 0; i < m; i++) {
      ans = mult(ans, 2);
    }
    add(ans, MOD - dp[(1 << n) - 1]);

    printf("%d\n", ans);
  }

  return 0;
}
