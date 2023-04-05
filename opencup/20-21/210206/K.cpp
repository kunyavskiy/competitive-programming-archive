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

const int MAXN = 310;

int cnk[MAXN][MAXN];

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  cnk[0][0] = 1;
  for (int i = 0; i < MAXN; i++) {
    for (int j = 0; j < MAXN; j++) {
      if (i) add(cnk[i][j], cnk[i - 1][j]);
      if (i && j) add(cnk[i][j], cnk[i - 1][j - 1]);
    }
  }

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;

    auto trees = [](int n) {
      if (n <= 2) return 1;
      return mpow(n, n - 2);
    };

    for (int i = 1; i <= n; i++) {
      for (int c = 1; c <= i; c++) {
        for (int j = 1; j <= i && j <= k; j++) {
          int coef = dp[i - j][c - 1];
          coef = mul(coef, cnk[i - 1][j - 1]);
          coef = mul(coef, trees(j));
          coef = mul(coef, j);
          add(dp[i][c], coef);
        }
      }
    }

    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
      int c;
      scanf("%d", &c);
      cnt[c - 1]++;
    }
    int colors = 0;
    int ans = 1;
    for (int i = 0; i < n; i++) {
      if (!cnt[i]) continue;
      ++colors;
      int cur = 0;
      for (int j = 1; j <= cnt[i]; j++) {
        add(cur, mul(dp[cnt[i]][j], mpow(n - cnt[i], j - 1)));
      }
      ans = mul(ans, cur);
    }
    if (colors >= 2) {
      ans = mul(ans, mpow(n, colors - 2));
    } else if (n == k){
      ans = trees(n);
    } else {
      ans = 0;
    }
    printf("%d\n", ans);
  }



  return 0;
}
