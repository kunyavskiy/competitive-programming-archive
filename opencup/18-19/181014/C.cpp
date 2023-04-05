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

const int MAXN = 5010;

int dp1[MAXN][MAXN];
int dp2[MAXN][MAXN];

void solve(const vector<int> &v, int dp[][MAXN], int a, int dis_prob) {
  int n = (int)v.size();
  for (int i = 0; i <= n; i++) {
    dp[n][i] = 0;
  }
  dp[n][a] = 1;
  for (int i = n - 1; i >= 0; i--) {
    dp[i][0] = 0;
    if (v[i]) {
      for (int j = 1; j <= i; j++) {
        dp[i][j] = dp[i + 1][j + 1];
      }
    } else {
      for (int j = 1; j <= i; j++) {
        dp[i][j] = mul(dp[i][j - 1], dis_prob);
        add(dp[i][j], mul(dp[i+1][j], MOD + 1 -  dis_prob));
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, r, h;
  scanf("%d%d%d", &n, &r, &h);
  static char buf[MAXN];
  scanf("%s", buf);
  int a, b;
  scanf("%d%d", &a, &b);

  vector<int> v(n);
  for (int i = 0; i < n; i++) {
    v[i] = buf[i] == 'R';
  }
  solve(v, dp1, a, mul(r, minv(r + h)));
  for (int i = 0; i < n; i++) {
    v[i] = buf[n - i - 1] == 'H';
  }
  solve(v, dp2, b, mul(h, minv(r + h)));

  int ans = 0;
  if (a == 0) {
    if (buf[n - 1] == 'H') {
      ans = dp2[1][1];
    }
  } else if (b == 0) {
    if (buf[0] == 'R') {
      ans = dp1[1][1];
    }
  } else {
    for (int i = 0; i + 1 < n; i++) {
      if (buf[i] == 'H' && buf[i + 1] == 'R') {
        eprintf("i = %d, rg_prob = %d, lf_prob = %d\n", i, dp1[i + 2][1], dp2[n - i][1]);
        add(ans, mul(dp1[i + 2][1], dp2[n - i][1]));
      }
    }
  }

  eprintf("%d %d\n", minv(64), mul(9, minv(64)));

  printf("%d\n", ans);

  return 0;
}
