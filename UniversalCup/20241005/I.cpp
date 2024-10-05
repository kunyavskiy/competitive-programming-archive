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

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  vector<int> fs(200, 1);
  for (int i = 2; i < (int)fs.size(); i++) {
    fs[i] = mul(fs[i - 1], i);
  }

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    int sum = 0;
    for (int& x : a) {
      scanf("%d", &x);
      sum += x;
    }

    int need = sum / 2;
    vector<vector<int>> dp(n + 1, vector<int>(need + 1, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
      vector<vector<int>> ndp(n + 1, vector<int>(need + 1, 0));
      for (int c = 0; c <= i; c++) {
        for (int j = 0; j <= need; j++) {
          add(ndp[c][j], dp[c][j]);
          if (j + a[i] <= need) {
            add(ndp[c + 1][j + a[i]], dp[c][j]);
          }
        }
      }
      dp = std::move(ndp);
    }

    int ans = 0;
    if (sum % 2 == 0) {
      for (int i = 0; i <= n; i++) {
        add(ans, mul(dp[i][need], mul(fs[i], fs[n - i])));
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
