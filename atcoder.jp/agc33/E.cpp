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

const int MAXN = 210000;

char s[MAXN];

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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    scanf("%s", s);
    if (s[0] != 'B') {
      for (int i = 0; i < m; i++) {
        s[i] = s[i] ^ 'B' ^ 'R';
      }
    }
    int first = find(s, s + m, 'R') - s;

    if (first == m) {
      vector<int> dp(n + 1);
      dp[0] = 1;
      dp[1] = 2;
      for (int i = 2; i <= n; i++) {
        dp[i] = dp[i - 1];
        add(dp[i], dp[i - 2]);
      }
      int ans = dp[n];
      if (n == 3) {
        sub(ans, dp[n - 3]);
      } else if (n > 3) {
        sub(ans, dp[n - 4]);
      }
      printf("%d\n", ans);
      continue;
    }

    int lim = n;
    int prev_r = 0;
    for (int i = 0; i < m; i++) {
      if (s[i] == 'R') {
        if ((i - prev_r) % 2 == 1) {
          lim = min(lim, i - prev_r);
        }
        prev_r = i + 1;
      }
    }
    lim = min(lim, first + 1);
    eprintf("lim = %d\n", lim);

    if (n % 2 != 0) {
      printf("0\n");
    } else {
      vector<int> dp(n / 2 + 1);
      vector<int> dp2(n / 2 + 2);
      dp[0] = 1;
      dp2[1] = 1;
      for (int i = 1; i <= n / 2; i++) {
        dp[i] = dp2[i];
        int pos = i - (lim + 1) / 2;
        if (pos >= 0)
          sub(dp[i], dp2[pos]);
        dp2[i + 1] = dp2[i];
        add(dp2[i + 1], dp[i]);
      }

      int ans = 0;
      for (int i = 1; i <= (lim + 1) / 2; i++) {
        add(ans, mul(2 * i, dp[n / 2 - i]));
      }
      printf("%d\n", ans);
    }

  }

  return 0;
}
