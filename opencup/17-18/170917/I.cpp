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

int MOD;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

const int MAXN = 55;

int dp[MAXN][MAXN];
int ndp[MAXN][MAXN];

void solve() {
  int v, e;
  scanf("%d%d%d", &v, &e, &MOD);
  memset(dp, 0, sizeof(dp));
  dp[v][0] = 1;
  for (int i = 0; i < e; i++) {
    memset(ndp, 0, sizeof(ndp));
    for (int j = 1; j <= v; j++) {
      for (int k = 0; k < j; k++) {
        if (k < j - 1) {
          add(ndp[j][k+1], dp[j][k]);
        }
        for (int t = 1; t <= k; t++) {
          add(ndp[j - t][k - t], dp[j][k]);
        }
        if (k == j - 1) {
          int ef = v * (v - 1) / 2;
          int eb = (v - j) * (v - j + 1) / 2;
          if (ef + eb > i) {
            add(ndp[j][k], dp[j][k]);
          }
        }
      }
    }
    int tot = 0;
    eprintf("i = %d\n", i);
    for (int j = 1; j <= v; j++) {
      for (int k = 0; k < j; k++) {
        add(tot, dp[j][k] = ndp[j][k]);
        eprintf("%d ", dp[j][k]);
      }
      eprintf("\n");
    }
    printf("%d ", tot);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int q;
  scanf("%d", &q);
  while (q-- > 0) {
    solve();
  }

  return 0;
}
