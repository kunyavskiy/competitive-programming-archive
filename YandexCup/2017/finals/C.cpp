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

const int MAXN = 10001;

int dp[MAXN][MAXN];
char s[MAXN];
int nextc[MAXN][3];

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

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  scanf("%s", s);

  nextc[n][0] = nextc[n][1] = nextc[n][2] = n;

  for (int i = n - 1; i >= 0; i--) {
    memcpy(nextc[i], nextc[i + 1], sizeof(nextc[i]));
    if (s[i] == 'M') {
      nextc[i][0] = i;
    } else if (s[i] == 'W') {
      nextc[i][1] = i;
    } else if (s[i] == 'U') {
      nextc[i][2] = i;
    } else {
      assert(0);
    }
  }

  dp[0][0] = 1;

  int ans = 0;

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j <= n; j++) {
      int nextm = min(nextc[i][0], nextc[max(i, j)][2]);
      int nextw = min(nextc[j][1], nextc[max(i, j)][2]);
      if (nextm == n && nextw == n) {
        add(ans, dp[i][j]);
      } else {
        if (nextm == nextw) {
          add(dp[nextm + 1][nextw + 1], dp[i][j]);
        } else {
          if (nextm < n) {
            add(dp[nextm + 1][j], dp[i][j]);
          }
          if (nextw < n) {
            add(dp[i][nextw + 1], dp[i][j]);
          }
        }
      }
    }
  }

  printf("%d\n", ans);

  return 0;
}
