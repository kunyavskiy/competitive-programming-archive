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

const ll INF = (ll)1.1e18;

ll sum(ll a, ll b) {
  if (a >= INF - b) {
    return INF;
  }
  return a + b;
}

ll mul(ll a, ll b) {
  if (a >= INF / b) {
    return INF;
  }
  return a * b;
}

ll psum(ll x) {
  ll a = x;
  ll b = x + 1;
  if (a % 2 == 0) {
    a /= 2;
  } else {
    b /= 2;
  }
  return mul(a, b);
}

ll get_sum(ll l) {
  ll s = 0;
  ll c = 1;
  while (l != 0) {
    s = sum(s, mul(psum(l), c));
    l /= 2;
    c *= 2;
  }
  return s;
}

ll get_val(ll l) {
  ll s = 0;
  while (l != 0) {
    s = sum(s, l);
    l /= 2;
  }
  return s;
}


void solve() {
  ll n;
  scanf("%lld", &n);
  ll l = 0;
  ll r = n;

  while (r - l > 1) {
    ll m = (l + r) / 2;
    ll val = get_sum(m);
    if (val > n) {
      r = m;
    } else {
      l = m;
    }
  }

//  assert(get_sum(l) < n);

  eprintf("l = %lld, sum(l) = %lld, val(l) = %lld\n", l, get_sum(l), get_val(l));
  ll extra = (n - get_sum(l));
  eprintf("extra = %lld\n", extra);

  printf("%lld\n", get_val(l) + extra / (l + 1));
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    solve();
  }

  return 0;
}
