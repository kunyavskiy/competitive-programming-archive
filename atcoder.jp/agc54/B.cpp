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

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<int>> dp(1, {1});
    int sum = 0;
    for (int it = 0; it < n; it++) {
      int a;
      scanf("%d", &a);
      sum += a;
      vector<vector<int>> ndp(dp.size() + 1, vector<int>(sum + 1));
      for (int i = 0; i < (int) dp.size(); i++) {
        for (int j = 0; j < (int) dp[i].size(); j++) {
          add(ndp[i][j], dp[i][j]);
          add(ndp[i + 1][j + a], dp[i][j]);
        }
      }
      dp = std::move(ndp);
    }
    int ans = 0;
    if (sum % 2 == 0) {
      for (int i = 0; i <= n; i++) {
        int r = dp[i][sum / 2];
        eprintf("%d %d\n", i, r);
        for (int j = 1; j <= i; j++) {
          r = mul(r, j);
        }
        for (int j = 1; j <= n - i; j++) {
          r = mul(r, j);
        }
        add(ans, r);
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
