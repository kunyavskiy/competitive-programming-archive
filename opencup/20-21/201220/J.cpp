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

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> l(n);
    vector<int> w(n);
    for (int &x : l) scanf("%d", &x);
    for (int &x : w) scanf("%d", &x);

    vector<int> totw(1 << n);
    for (int i = 1; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
          totw[i] = totw[i & ~ (1 << j)] + w[j];
          break;
        }
      }
    }
    vector<double> dp(1 << n);
    dp[0] = 0;
    for (int i = 1; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
          dp[i] = max(dp[i], dp[i & ~(1 << j)] + (l[j] * w[j] / 2.0) / totw[i]);
          dp[i] = max(dp[i], l[j] / 2.0 * (1 + (totw[i] - w[j]) * 1.0 / totw[i]));
        }
      }
      eprintf("dp[%d] = %lf\n", i, dp[i]);
    }
    printf("%.18lf\n", dp.back());
  }

  return 0;
}
