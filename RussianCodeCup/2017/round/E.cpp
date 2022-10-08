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

const int MAXN = 3010;

#define next next_aaa

int next[2][MAXN][MAXN];
int n[2];
int a[2][MAXN];

int dp[2][MAXN];

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  for (int i = 0; i < 2; i++) {
    scanf("%d", &n[i]);
    for (int j = 0; j < n[i]; j++) {
      scanf("%d", &a[i][j]);
    }
    for (int j = 0; j <= MAXN; j++) {
      next[i][n[i]][j] = n[i];
    }
    for (int j = n[i] - 1; j >= 0; j--) {
      memcpy(next[i][j], next[i][j+1], sizeof(next[i][j]));
      next[i][j][a[i][j]] = j;
    }
  }

  int k;
  scanf("%d", &k);

  for (int it = 0; it < k; it++) {
#ifdef LOCAL
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < n[i]; j++) {
        eprintf("%d ", dp[i][j]);
      }
      eprintf("\n");
    }
    eprintf("\n");
#endif

    int minv = MAXN;
    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < n[i]; j++) {
        if (dp[i][j] > n[i ^ 1]) continue;
//        if (it == k - 1 && dp[i][j] == 0) continue;
        if (n[i] - j - 1 + n[i ^ 1] - dp[i][j] >= k - it - 1) {
          minv = min(minv, a[i][j]);
        }
      }
    }
    printf("%d ", minv);

    for (int i = 0; i < 2; i++) {
      for (int j = n[i] - 1; j >= 0; j--) {
        int ne = next[i][j][minv];
        if (ne < n[i]) {
          dp[i][ne + 1] = min(dp[i][ne + 1], dp[i][j]);
        }
        if (dp[i][j] <= n[i ^ 1]) {
          dp[i][j] = next[i ^ 1][dp[i][j]][minv] + 1;
        }
      }
      for (int j = 1; j < n[i]; j++) {
        dp[i][j] = min(dp[i][j], dp[i][j - 1]);
      }
    }
  }
  printf("\n");
  return 0;
}
