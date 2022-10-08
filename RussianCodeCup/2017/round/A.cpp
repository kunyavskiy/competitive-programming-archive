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

void factor(int a, vector<int> &ps) {
  for (int i = 2; i * i <= a; i++) {
    while (a % (i * i) == 0) a /= i * i;
    if (a % i == 0) {
      ps.push_back(i);
      a /= i;
    }
  }
  if (a > 1) {
    ps.push_back(a);
  }
}

void solve() {
  int a, b;
  scanf("%d%d", &a, &b);
  int g = __gcd(a, b);
  a /= g;
  b /= g;
  vector<int> ps;
  factor(a, ps);
  factor(b, ps);

  sort(ps.begin(), ps.end());

  static map<vector<int>, pair<ll, ll>> cache;
  auto& ans = cache[ps];
  if (ans.first == 0) {
    ll bx, by;
    bx = by = 0;
    int n = ps.size();
    for (int i = 0; i < (1 << (n - 1)); i++) {
      ll x, y;
      x = y = 1;
      for (int j = 0; j < n; j++) {
        if (i & (1 << j)) {
          x *= ps[j];
        } else {
          y *= ps[j];
        }
      }
      if (bx == 0 || (bx + by > x + y)) {
        bx = x;
        by = y;
      }
    }
    ans = {bx, by};
  }
  printf("%lld %lld\n", ans.first, ans.second);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t --> 0) {
    solve();
  }
  return 0;
}
