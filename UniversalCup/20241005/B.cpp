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
#include <numeric>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }

const int MAXN = 3100;
int cnk[MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i)
        add(cnk[i][j], cnk[i - 1][j]);
      if (i && j)
        add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> dp(m + 1);
    dp[0] = 1;
    vector<int> a(n);
    for (int& x : a) scanf("%d", &x);
    sort(a.rbegin(), a.rend());
    vector<int> ans(n + 1);
    for (int i = 0; i < n; i++) {
      vector<int> ndp(m + 1);
      for (int j = 0; j <= m; j++) {
        add(ndp[min(m, j + a[i])], dp[j]);
      }
      for (int k = 0; k <= n; k++) {
        add(ans[k], mul(ndp[m], cnk[n - i - 1][k]));
      }
      for (int j = 0; j <= m; j++) {
        add(ndp[j], dp[j]);
      }
      dp = std::move(ndp);
    }
    for (int i = 0; i <= n; i++) {
      printf("%d\n", ans[i]);
    }
    printf("\n");
  }

  return 0;
}
