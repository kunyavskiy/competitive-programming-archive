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
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, a;
  while (scanf("%d%d", &n, &a) == 2) {
    vector<int> fs(n + 1);
    vector<int> ifs(n + 1);
    fs[0] = ifs[0] = 1;
    for (int i = 1; i <= n; i++) {
      fs[i] = fs[i - 1] * i;
      ifs[i] = minv(fs[i]);
    }
    auto cnk = [&](int n, int k) {
      return mul(fs[n], mul(ifs[k], ifs[n - k]));
    };

    vector<int> dp(a + 1);
    dp[0] = 0;
    for (int i = 1; i <= a; i++) {
      dp[i] = i;
      for (int j = 1; j <= i; j++) {
        sub(dp[i], mul(cnk(i, j), dp[i - j]));
      }
    }

    int ans = mul(dp[a], fs[n - a]);
    for (int i = 0; i < a; i++) {
      for (int j = 0; j <= i; j++) {
        int cur = cnk(i, j);
        cur = mul(cur, mul(dp[a - i - 1], fs[n - j - 2]));
        add(ans, cur);
      }
    }


    printf("%d\n", ans);
  }

  return 0;
}
