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

const int MOD = 1000000009;

void add(int& a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int& a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int)((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

const int W = 115381398;

int fact[1010];
int ifact[1010];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  assert(mpow(W, 3) == 1);

  fact[0] = ifact[0] = 1;
  for (int i = 1; i <= 1000; i++) {
    fact[i] = mul(fact[i - 1], i);
    ifact[i] = mul(ifact[i - 1], minv(i));
  }

  auto cnk = [](int n, int k) { return mul(fact[n], mul(ifact[k], ifact[n-k])); };
  auto multic = [](int n, int a1, int a2) { return mul(fact[n], mul(ifact[a1], mul(ifact[a2], ifact[n-a1-a2]))); };

  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    int ans = 0;
    ans = mul(ans, minv(3));
    ans = mpow(ans, n * m);

    vector<int> dp[3] = {vector<int>(n * m + 1), vector<int>(n * m + 1), vector<int>(n * m + 1)};
    int c0 = (k + 2) / 3, c1 = (k + 1) / 3, c2 = k / 3;
    dp[0][0] = 0;
    for (int i = 1; i <= n * m; i++) {
      add(dp[0][i], mul(dp[0][i-1], c0)); add(dp[0][i], mul(dp[2][i-1], c1)); add(dp[0][i], mul(dp[1][i-1], c2));
      add(dp[1][i], mul(dp[1][i-1], c0)); add(dp[1][i], mul(dp[0][i-1], c1)); add(dp[1][i], mul(dp[2][i-1], c2));
      add(dp[2][i], mul(dp[2][i-1], c0)); add(dp[2][i], mul(dp[1][i-1], c1)); add(dp[2][i], mul(dp[0][i-1], c2));
    }


    for (int a0 = 0; a0 <= n; a0++) {
      for (int a1 = 0; a0+a1 <= n; a1++) {
        int a2 = n - a0 - a1;
        for (int b0=0; b0 <= m; b0++) {
          for (int b1= 0; b0+b1 <= m; b1++) {
            int b2 = m - b0 - b1;

            int ways = mul(multic(n, a0, a1), multic(m, b0, b1));

            int t0 = a0 * b0 + a1 * b2 + a2 * b1;
            int t1 = a0 * b1 + a1 * b0 + a2 * b2;
            int t2 = a0 * b2 + a1 * b1 + a2 * b0;



          }
        }
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}
