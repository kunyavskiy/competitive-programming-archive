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

void solve() {
  ll n;
  ll a, b, c, d;
  scanf("%lld%lld%lld%lld%lld", &n, &a, &b, &c, &d);
  set<pair<ll, ll>> s;
  map<ll, ll> cost;
  auto add = [&](ll val, ll c) {
    if (!cost.count(val) || cost[val] > c) {
      s.erase({cost[val], val});
      cost[val] = c;
      s.insert({cost[val], val});
    }
  };
  auto down = [](ll x, ll m) {
    return x / m * m;
  };
  auto up = [&](ll x, ll m) {
    return down(x + m - 1, m);
  };
  add(n, 0);
  while (!s.empty()) {
    auto [cost, val] = *s.begin();
    s.erase(s.begin());
    eprintf("%lld %lld\n", cost, val);
    if (0 < val && val < 10) {
      add(val - 1, cost + d);
    }
    if (val < numeric_limits<ll>::max() / d / 2) {
      add(0, cost + val * d);
    }
    add(up(val, 2) / 2, cost + a + (up(val, 2) - val) * d);
    add(up(val, 3) / 3, cost + b + (up(val, 3) - val) * d);
    add(up(val, 5) / 5, cost + c + (up(val, 5) - val) * d);
    add(down(val, 2) / 2, cost + a + (val - down(val, 2)) * d);
    add(down(val, 3) / 3, cost + b + (val - down(val, 3)) * d);
    add(down(val, 5) / 5, cost + c + (val - down(val, 5)) * d);
  }
  printf("%lld\n", cost[0]);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
