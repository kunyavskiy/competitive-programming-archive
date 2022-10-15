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

ll intersect(vector<ll> s, vector<ll> d, ll lim) {
  sort(s.begin(), s.end());
  sort(d.begin(), d.end());

  ll ans = 0;

  for (ll v : s) {
    ans += upper_bound(d.begin(), d.end(), v) - upper_bound(d.begin(), d.end(), v - lim);
  }

  eprintf("ans = %lld\n", ans);

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, h;
  while (scanf("%d%d", &n, &h) == 2) {
    vector<ll> s[2], d[2];
    for (int i = 0; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      int m = ((x + y) & 1);
      s[m].push_back(x + y);
      d[m].push_back(x - y);
    }
    ll ans = n * (2LL * h - 1);

    ans -= intersect(s[0], d[0], 2LL * h - 1);
    ans -= intersect(s[1], d[1], 2LL * h - 1);
    printf("%lld\n", ans);
  }

  return 0;
}
