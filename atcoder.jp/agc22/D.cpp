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

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  ll L;
  while (scanf("%d%lld", &n, &L) == 2) {
    ll add = 0;
    vector<ll> x(n);
    vector<ll> t(n);
    assert(n <= 5000);

    for (int i = 0; i < n; i++) {
      scanf("%lld", &x[i]);
    }

    for (int i = 0; i < n; i++) {
      scanf("%lld", &t[i]);
      add += t[i] / (2 * L);
      t[i] %= 2 * L;
    }

    int ptr = 0;
    for (int i = 0; i < n; i++) {
      if (t[i]) {
        x[ptr] = x[i];
        t[ptr] = t[i];
        ptr++;
      }
    }

    n = ptr;
    x.resize(n);
    t.resize(n);

    vector<int> dp(n + 1, -1e9);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
      vector<int> ndp = dp;
      if (t[i] <= 2 * x[i]) {
        for (int j = 0; j < n; j++) {
          ndp[j + 1] = max(ndp[j + 1], dp[j]);
        }
      }
      if (t[i] <= 2 * (L - x[i])) {
        for (int j = 0; j < n; j++) {
          ndp[j] = max(ndp[j], dp[j + 1] + 1);
        }
      }
      dp = ndp;
    }

    int ans = *max_element(dp.begin(), dp.end());
    eprintf("ans = %d\n", ans);

    printf("%lld\n", 2 * (n + 1 - ans + add) * L);
  }

  return 0;
}
