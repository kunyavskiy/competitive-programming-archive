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

const int MAXN = 510;

int dp[MAXN][MAXN];
int a[MAXN];
int cnk[MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }


  int n;
  while (scanf("%d", &n) == 1) {
    a[0] = -1;
    for (int i = 1; i <= n; i++) {
      scanf("%d", &a[i]);
    }
    a[n + 1] = -2;

    n += 2;
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++) {
      dp[i][i + 1] = 1;
    }
    for (int len = 3; len <= n; len++) {
      for (int i = 0; i + len <= n; i++) {
        int j = i + len - 1;
        if (a[i] == a[j]) continue;
        dp[i][j] = 0;
        for (int k = i + 1; k < j; k++) {
          if (a[i] != a[k] && a[j] != a[k]) {
            int cur = dp[i][k];
            cur = mul(cur, dp[k][j]);
            cur = mul(cur, cnk[j - i - 2][k - i - 1]);
            add(dp[i][j], cur);
          }
        }
      }
    }
    printf("%d\n", dp[0][n - 1]);
  }

  return 0;
}
