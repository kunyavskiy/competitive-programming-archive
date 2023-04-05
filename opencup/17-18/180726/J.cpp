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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

//#define STRESS

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

ll solve_stupid(ll a, ll b, ll n) {
  ll l = a * b / __gcd(a, b);
  ll ans = 0;
  for (ll i = 0; i < l; i++) {
    ll cur = 0;
    for (ll j = 0; j < n; j++) {
      bool f = (i + j) % a == 0;
      bool s = (i + j) % b == 0;
      if (f == s) {
        cur++;
      }
    }
    if (ans < cur) {
      ans = cur;
    }
  }
  return ans;
}

ll max_rem(ll a, ll b, ll k);
ll min_rem(ll a, ll b, ll k);

ll max_rem_stupid(ll a, ll b, ll k) {
  ll ans = 0;
  for (ll i = 1; i <= k; i++) {
    ans = max(ans, (a * i) % b);
  }
  return ans;
}

ll max_rem_smart(ll a, ll b, ll k) {
  if (k >= b) {
    return b - __gcd(a, b);
  }
  if (a * k < b) {
    return a * k;
  }
  if (b % a == 0) {
    return b - a;
  }
  return b - a + (a - min_rem(b % a, a, (a * (k + 1)) / b));
}

ll max_rem(ll a, ll b, ll k) {
  ll res1 = max_rem_smart(a % b, b, k);
#ifdef STRESS
  ll res2 = max_rem_stupid(a, b, k);
  if (res1 != res2) {
    eprintf("max_rem(%lld, %lld, %lld) : %lld != %lld\n", a, b, k, res1, res2);
    assert(0);
  }
  eprintf("max_rem(%lld, %lld, %lld) : %lld\n", a, b, k, res1);
#endif
  return res1;
}


ll min_rem_stupid(ll a, ll b, ll k) {
  ll ans = b - 1;
  for (ll i = 1; i <= k; i++) {
    if ((a * i) % b != 0)
      ans = min(ans, (a * i) % b);
  }
  return ans;
}

ll min_rem_smart(ll a, ll b, ll k) {
  if (k >= b) {
    return __gcd(a, b);
  }
  if (a * k < b) {
    return a;
  }
  if (b % a == 0) {
    return a;
  }
  return (a - max_rem(b % a, a, (a * (k + 0)) / b));
}

ll min_rem(ll a, ll b, ll k) {
  ll res1 = min_rem_smart(a % b, b, k);
#ifdef STRESS
  ll res2 = min_rem_stupid(a, b, k);
  if (res1 != res2) {
    eprintf("min_rem(%lld, %lld, %lld) : %lld != %lld\n", a, b, k, res1, res2);
    assert(0);
  }
  eprintf("min_rem(%lld, %lld, %lld) : %lld\n", a, b, k, res1);
#endif
  return res1;
}


ll solve1(ll a, ll b, ll n) {
  if (n < a) {
    return n / b;
  }
  ll lcm = a / __gcd(a, b) * b;
  if (n >= lcm) {
    return solve1(a, b, n % lcm) + (a / __gcd(a, b) + b / __gcd(a, b) - 2) * (n / lcm);
  }
  ll d = 0;
  if (n % b != 0 && (max_rem(a, b, n / a) > n % b)) {
    d = 1;
  }
  ll ans = (n / a) + ((n + b - 1) / b) - 2 * ((n + lcm - 1) / lcm) - d;
  return ans;
}

ll solve(ll a, ll b, ll n) {
  if (a < b) swap(a, b);
  if (a % b == 0) {
    return n - (n / b) + ((n / b + a / b - 1) / (a / b));
  }
  return n - min(solve1(a, b, n), solve1(b, a, n));
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  min_rem(4, 5, 2);
  max_rem(18, 24, 3);
  max_rem(5, 8, 3);
  max_rem(8, 11, 5);
  max_rem(11, 25, 12);
//  max_rem(5, 4, 2);
  max_rem(5, 14, 7);

  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    int a, b;
    ll n;
    scanf("%lld%d%d", &n, &a, &b);
    ll ans = solve(a, b, n);
#ifdef STRESS
    ll ans2 = solve_stupid(a, b, n);
    if (ans != ans2) {
      eprintf("%d %d %lld: %lld != %lld\n", a, b, n, ans, ans2);
      assert(0);
    }
    eprintf("OK\n");
#endif
    printf("%lld\n", ans);
  }

  return 0;
}

/*
 *
max_rem(a, b, n / a) = 7
n % b = 7
n / a = 12
(n + b - 1) / b = 8
2 * ((n + lcm - 1) / lcm) = 4
d = 1
ans(5, 8, 63) = 15
max_rem(a, b, n / a) = 4
n % b = 3
n / a = 7
(n + b - 1) / b = 13
2 * ((n + lcm - 1) / lcm) = 4
d = 1
ans(8, 5, 63) = 15
5 8 63: 48 != 47
 */
