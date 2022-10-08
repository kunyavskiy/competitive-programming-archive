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

const int MOD = 998244353;

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

const int MAXN = 1000;

int f[MAXN];
int invf[MAXN];

int cnk(int n, int k) {
  if (k > n || n < 0 || k < 0) return 0;
  return mul(f[n], mul(invf[k], invf[n - k]));
}

int dp[MAXN];
int ndp[MAXN];

int A[MAXN][MAXN];
int B[MAXN][MAXN];
int C[MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
    invf[i] = mul(invf[i - 1], minv(i));
  }

  int N, M;
  scanf("%d%d", &N, &M);

  A[0][0] = B[0][0] = C[0][0] = 1;

  for (int n = 1; n <= N; n++) {
    for (int k = 0; k <= n; k++) {
      C[n][k] = C[n - 1][k];
      if (k) add(C[n][k], C[n - 1][k - 1]);
      assert(C[n][k] == cnk(n, k));

      B[n][k] = C[n - 1][k];
      if (k) add(B[n][k], C[n - 1][k - 1]);
      if (k) add(B[n][k], B[n - 1][k - 1]);

      A[n][k] = B[n - 1][k];
      if (k) add(A[n][k], B[n - 1][k - 1]);
      if (k) add(A[n][k], A[n - 1][k - 1]);
    }
  }

  dp[0] = 1;
  for (int i = 0; i < M; i++) {
    memset(ndp, 0, sizeof(ndp));

    for (int j = 0; j <= N; j++) {
      for (int k = 0; k <= j; k++) {
        add(ndp[j], mul(dp[k], A[j][k]));
      }
    }

    memcpy(dp, ndp, sizeof(ndp));

    for (int j = 0; j <= N; j++) {
      eprintf("%d ", dp[j]);
    }
    eprintf("\n");
  }

  int ans = 0;
  for (int i = 0; i <= N; i++) {
    add(ans, mul(dp[i], cnk(N, i)));
  }
  printf("%d\n", ans);
  return 0;
}
