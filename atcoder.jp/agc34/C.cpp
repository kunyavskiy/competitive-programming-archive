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

struct item {
  int b, l, u;
  ll score;
};

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, x;
  while (scanf("%d%d", &n, &x) == 2) {
    ll target = 0;
    vector<item> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d%d", &v[i].b, &v[i].l, &v[i].u);
      target += v[i].b * 1LL * v[i].l;
      v[i].score = v[i].b * 1LL * v[i].l + (x - v[i].b) * 1LL * v[i].u;
    }

    sort(v.begin(), v.end(), [](const item& a, const item& b) { return a.score > b.score;});

    auto best = [&](ll hours) {
      int full = hours / x;
      int extra = hours % x;
      ll sum = 0;
      for (int i = 0; i < full; i++) {
        sum += v[i].score;
      }
      if (extra == 0) return sum;
      sum += v[full].score;
      ll ans = 0;
      for (int i = 0; i < n; i++) {
        ll cur = sum - v[min(i, full)].score;
        int small = min(extra, v[i].b);
        int big = extra - small;
        cur += small * 1LL * v[i].l + big * 1LL * v[i].u;
        ans = max(ans, cur);
      }
      return ans;
    };

    ll lf = -1;
    ll rg = n * 1LL * x;

    while (rg - lf > 1) {
      ll mid = (lf + rg) / 2;
      if (best(mid) >= target) {
        rg = mid;
      } else {
        lf = mid;
      }
    }

    printf("%lld\n", rg);
  }

  return 0;
}
