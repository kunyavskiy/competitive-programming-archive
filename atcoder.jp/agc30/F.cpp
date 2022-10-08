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
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> used(2 * n);
    int places = n;
    for (int i = 0; i < n; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      if (a != -2) {
        used[a]++;
      }
      if (b != -2) {
        used[b]++;
      }
      if (a != -2 && b != -2) {
        used[a]++;
        used[b]++;
      }
      if (a != -2 || b != -2) {
        places--;
      }
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    dp[0][0] = 1;

    for (int i = 0; i < 2 * n; i++) {
      if (used[i] == 2) continue;
      vector<vector<int>> ndp(n + 1, vector<int>(n + 1, 0));

      auto go = [&](int a, int b, int c, int d, int cf = 1) {
        if (0 <= c && c <= n && 0 <= d && d <= n) {
          if (dp[a][b]) {
            eprintf("%d,%d -> %d,%d * %d\n", a, b, c, d, cf);
          }
          add(ndp[c][d], mul(dp[a][b], cf));
        }
      };

      if (used[i] == 0) {
        for (int a = 0; a <= n; a++) {
          for (int b = 0; b <= n; b++) {
            int cf = i - a - b;
            if (cf < 0 || cf % 2 != 0) {
              assert(dp[a][b] == 0);
            } else {
              go(a, b, a + 1, b);
              go(a, b, a, b + 1);
              go(a, b, a - 1, b);
            }
          }
        }
      } else {
        for (int a = 0; a <= n; a++) {
          for (int b = 0; b <= n; b++) {
            go(a, b, a + 1, b);
            go(a, b, a, b - 1, b);
          }
        }
      }

      dp = ndp;

      for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
          eprintf("%d ", dp[i][j]);
        }
        eprintf("\n");
      }
      eprintf("\n");
    }

    int ans = dp[0][0];
    for (int i = 1; i < places; i++) {
      ans = mul(ans, i);
    }

    printf("%d\n", dp[0][0]);

  }


  return 0;
}
