#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")

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

constexpr int MOD = 998244353;
constexpr long long MOD2 = MOD * 1LL * MOD;

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

const int MAXN = 3100;


int pow2m1[MAXN];
int ipow2m1[MAXN];

int cnk[MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  for (int i = 0; i < MAXN; i++) {
    pow2m1[i] = mpow(2, i);
    sub(pow2m1[i], 1);
    ipow2m1[i] = minv(pow2m1[i]);
  }

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }


  int n, c;
  while (scanf("%d%d", &n, &c) == 2) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
      --v[i];
    }

    vector<vector<int>> dp1(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
      int cur = 1;
      int cnt0 = c;
      vector<int> cnts(c);
      for (int j = i; j < n; j++) {
        if (cnts[v[j]] == 0) {
          cnt0--;
        } else {
          cur = mul(cur, ipow2m1[cnts[v[j]]]);
        }
        cnts[v[j]]++;
        if (cnt0 == 0) {
          dp1[i][j] = cur;
        }
        cur = mul(cur, pow2m1[cnts[v[j]]]);
      }
    }

    vector<int> dp(n + 1);
    for (int i = 0; i <= n; i++) {
      dp[i] = mpow(2, n - i);
    }
    vector<int> ans(n + 1);
    if (c == 1) {
      for (int i = 1; i <= n; i++) {
        ans[i] = cnk[n][i];
      }
    } else {
      ans[0] = dp[0];
      sub(ans[0], 1);
      int lim = n - 1;
      for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= lim; j++) {
          dp[j] = 0;
          ll x = 0;
          for (int k = j; k <= lim; k++) {
            x += dp1[j][k] * 1LL * dp[k + 1];
            if (x >= MOD2) x -= MOD2;
          }
          dp[j] = x % MOD;
        }
        dp[n] = 0;
        ans[i] = dp[0];
        if (dp[0] == 0) break;
        while (dp[lim] == 0) lim--;
      }
      for (int i = 0; i < n; i++) {
        sub(ans[i], ans[i + 1]);
      }
    }


    for (int i = 0; i <= n; i++) {
      printf("%d ", ans[i]);
    }
    printf("\n");
  }


  return 0;
}
