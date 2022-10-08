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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d\n", &n) == 1) {
    ll x;
    scanf("%lld", &x);
    vector<ll> v(n);
    for (ll &a : v) scanf("%lld", &a);

    vector<ll> dp(n + 1, 1LL << 60);
    dp[0] = 0;

    for (int i = 0; i < n; i++) {
      for (int j = 0; j <= i; j++) {
        ll to_add = v[i];
        to_add += v[j] * (i - j + 2) * (i - j + 2);
        for (int k = i; k > j; k--) {
          to_add += (v[k] - v[k - 1]) * (i - k + 2) * (i - k + 2);
        }
        dp[i + 1] = min(dp[i + 1], dp[j] + to_add + x);
      }
    }

    printf("%lld\n", dp[n] + n * x);
  }

  return 0;
}
