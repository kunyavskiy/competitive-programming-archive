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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
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

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> lf(n + 2, -1);
    lf[0] = 0;
    lf[n + 1] = n + 1;
    n += 2;
    for (int i = 0; i < m; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      lf[r] = max(lf[r], l);
    }
    for (int i = 1; i < n; i++) {
      lf[i] = max(lf[i], lf[i - 1]);
    }
    vector<int> d6(n + 1);
    d6[0] = 1;
    for (int i = 1; i < n; i++) {
      d6[i] = mul(d6[i - 1], 6);
    }
    vector<vector<int>> dp(n, vector<int>(n, 0));
    vector<vector<int>> dps(n, vector<int>(n+1, 0));
    dp[0][0] = 1;
    dps[0][1] = 1;
    for (int i = 1; i < n; i++) {
      for (int j = 0; j < i; j++) {
        int coef = mul(2, d6[i - j - 1]);
//        int sum = 0;
        int sum2 = 0;
        if (lf[i - 1] <= j) {
//          for (int k = lf[i - 1]; k <= j; k++) {
//            add(sum, dp[j][k]);
//          }
          sum2 = dps[j][j + 1];
          sub(sum2, dps[j][lf[i - 1]]);
//          assert(sum2 == sum);
        }
        add(dp[i][j], mul(sum2, coef));
        add(dp[i][i], mul(sum2, coef));
      }
      for (int j = 0; j <= i; j++) {
        dps[i][j + 1] = dps[i][j];
        add(dps[i][j + 1], dp[i][j]);
      }
    }

    int ans = dp[n - 1][n - 1];
    ans = mul(ans, minv(2));
    printf("%d\n", ans);
  }

  return 0;
}
