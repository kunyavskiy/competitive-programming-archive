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

const int MAXN = 2010;

ll dp[MAXN];
ll ndp[MAXN];

int mask[MAXN];
char s[MAXN];

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, a, b, c;
  scanf("%d%d%d%d", &n, &a, &b, &c);

  for (int i = 0; i < n; i++) {
    static char buf[50];
    scanf("%s", buf);
    for (int j = 0; buf[j]; j++) {
      mask[i] |= (1 << (buf[j] - 'a'));
    }
  }

  scanf("%s", s);
  memset(dp, 0x3f, sizeof(dp));
  const ll INF = dp[0];
  dp[0] = 0;

  for (int i = 0; s[i]; i++) {
    int bit = 1 << (s[i] - 'a');

    for (int j = 0; j < n; j++) {
      if (mask[j] & bit) {
        ndp[j] = dp[j] + c;
      } else {
        ndp[j] = INF;
      }
    }

    rotate(dp, dp + n - 1, dp + n);
    for (int j = 0; j < n; j++) {
      dp[j] += a;
    }
    for (int it = 0; it < 2; it++) {
      dp[0] = min(dp[0], dp[n - 1] + b);
      for (int j = 1; j < n; j++) {
        dp[j] = min(dp[j], dp[j - 1] + b);
      }
    }

    for (int j = 0; j < n; j++) {
      if (mask[j] & bit) {
        ndp[j] = min(ndp[j], dp[j] + c);
      }
    }

    memcpy(dp, ndp, sizeof(dp));
    if (*min_element(dp, dp + n) == INF) {
      printf("-1\n");
      return 0;
    }
  }

  printf("%lld\n", *min_element(dp, dp + n));
  return 0;
}
