#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &a[i], &b[i]);
    }
    vector<int> dp(std::accumulate(a.begin(), a.end(), 0) + 1, std::numeric_limits<int>::max() / 2);
    dp[0] = 0;
    for (int i = 0; i < n; i++) {
      for (int j = dp.size() - 1; j >= 0; j--) {
        if (j < a[i]) dp[j] = dp[j] + b[i];
        else dp[j] = min(dp[j] + b[i], dp[j-a[i]]);
      }
    }
    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < (int)dp.size(); i++) {
      ans = min(ans, max(i, dp[i]));
    }
    printf("%d\n", ans);
  }

  return 0;
}
