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

void add(int &x, int y) {
  x += y;
  if (x >= MOD) x -= MOD;
}

int mul(int a, int b) {
  return (ll)a * b % MOD;
}

int bin(int a, int n) {
  int res = 1;
  while (n) {
    if (n & 1) res = mul(res, a);
    a = mul(a, a);
    n >>= 1;
  }
  return res;
}

int inv(int x) {
  return bin(x, MOD - 2);
}

vector<vector<int>> slow(int N, int M) {
  vector<int> fct(N + 1);
  fct[0] = 1;
  for (int i = 1; i <= N; i++) {
    fct[i] = mul(fct[i - 1], i);
  }

  vector<vector<int>> c(N + 1, vector<int>(M + 1));
  c[0][0] = 1;
  for (int n = 0; n < (int)c.size() - 1; n++) {
    for (int k = 0; k <= n; k++) {
      add(c[n + 1][k], c[n][k]);
      add(c[n + 1][k + 1], c[n][k]);
    }
  }

  vector<vector<int>> dp(N + 1, vector<int>(M + 1));
  for (int n = 1; n <= N; n++) {
    dp[n][1] = mul(fct[n], 1LL * n * (n - 1) / 2 % MOD);
    dp[n][1] = mul(dp[n][1], (MOD + 1) / 2);
    for (int k = 2; k <= M; k++) {
      for (int m = 0; m < n; m++) {
        add(dp[n][k], mul(mul(2, mul(dp[m][k - 1], fct[n - m - 1])), c[n - 1][m]));
      }
    }
  }
  return dp;
}

vector<vector<int>> fast(int N, int K) {
  vector<int> fct(N + 1);
  fct[0] = 1;
  for (int i = 1; i <= N; i++) {
    fct[i] = mul(fct[i - 1], i);
  }
  vector<int> rev(N + 1);
  for (int i = 1; i <= N; i++) rev[i] = inv(i);

  vector<vector<int>> dp(N + 1, vector<int>(K + 1));
//  vector<vector<int>> pref(N + 1, vector<int>(K + 1));
  for (int n = 1; n <= N; n++) {
    dp[n][1] = mul(fct[n], 1LL * n * (n - 1) / 2 % MOD);
    dp[n][1] = mul(dp[n][1], (MOD + 1) / 2);
    dp[n][1] = mul(dp[n][1], inv(fct[n]));

    add(dp[n][1], dp[n - 1][1]);
  }

  for (int k = 2; k <= K; k++) {
    for (int n = 2; n <= N; n++) {
      dp[n][k] = dp[n - 1][k];
      add(dp[n][k], mul(2, mul(rev[n], dp[n - 1][k - 1])));
    }
  }
  for (int n = N; n >= 1; n--) {
    for (int k = 1; k <= K; k++) {
      dp[n][k] = (dp[n][k] - dp[n - 1][k] + MOD) % MOD;
      dp[n][k] = mul(dp[n][k], fct[n]);
    }
  }

  return dp;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
//  freopen("h.out", "w", stdout);
#endif

  auto old = slow(50, 50);
  auto dp = fast(50, 50);
  assert(old == dp);
  dp = fast(6000, 6000);

//return 0;
  int T;
  scanf("%d", &T);
  for (int test = 1; test <= T; test++) {
    int n, k;
    scanf("%d%d", &n, &k);
    printf("Case #%d: %d\n", test, dp[n][k]);
  }

  return 0;
}
