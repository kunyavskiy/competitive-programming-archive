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
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<ll> dp(1 << n);
    vector<int> g(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);--a, --b;
      g[a] |= (1 << b);
      g[b] |= (1 << a);
    }
    vector<int> join(1 << n);
    for (int i = 1; i < (1 << n); i++) {
      for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
          join[i] = join[i & ~(1 << j)] | g[j];
          break;
        }
      }
    }

    dp[0] = 1;
    for (int i = 0; i < (1 << n); i++) {
      for (int j = i; j; j = (j - 1) & i) {
        if (((~(join[j]|j)) & i) == 0 && (join[j] & j) == 0) {
          dp[i] += dp[i & ~j];
        }
      }
      eprintf("dp[%d] = %lld\n", i, dp[i]);
    }

    printf("%lld\n", dp[(1 << n) - 1]);
  }

  return 0;
}
