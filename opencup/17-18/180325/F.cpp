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

// number of (x, y) : (0 <= x < n && 0 < y < k/d x + b/d)
ll count_solve(ll n, ll k, ll b, ll d) {
  if (k == 0) {
    return (b / d) * n;
  }
  if (k >= d || b >= d) {
    return ((k / d) * (n - 1) + 2 * (b / d)) * n / 2 + count_solve(n, k % d, b % d, d);
  }
  return count_solve((k * n + b) / d, d, (k * n + b) % d, k);
}

ll count_under_smart(ll n, ll m, ll p, ll q) {
  if (q == 0) return 0;
  if (p == 0) return n * m - n;

  assert(__gcd(p, q) == 1);
  ll on_diag = min((m - 1) / p, (n - 1) / q);
  if (p * (n - 1) >= q * (m - 1)) {
    return count_solve(m, q, 0, p) + m - 1 - on_diag;
  } else {
    ll r = count_under_smart(m, n, q, p);
    return n * m - r - on_diag - 1;
  }
}

ll count_under(ll n, ll m, ll p, ll q) {
  ll ans2 = count_under_smart(n, m, p, q);
#ifdef LOCAL2
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if ((i || j) && i * p < q * j) {
        ans++;
      }
    }
  }
  if (ans != ans2) {
    eprintf("n = %lld, m = %lld, p = %lld, q = %lld, ans1 = %lld, ans2 = %lld\n", n, m, p, q, ans, ans2);
    assert(0);
  }
#endif
  return ans2;
}

const ll INF = 1e9;

void solve(ll n, ll m, ll x) {
  if (x >= n * m - n) {
    printf("%lld %d\n", x - n * m + n + 2, 1);
    return;
  }
  ll p1 = 1, q1 = 0;
  ll p2 = 0, q2 = 1;

  while (true) {
    eprintf("%lld %lld %lld %lld\n", p1, q1, p2, q2);
    assert(count_under(n, m, p1, q1) <= x);
    assert(count_under(n, m, p2, q2) > x);

    ll limk = min(p2 ? (m - p1 - 1) / p2 : INF, q2 ? (n - q1 - 1) / q2 : INF);
    if (limk == 0) break;
    {
      ll l = -1;
      ll r = limk + 1;
      while (r - l > 1) {
        ll mid = (l + r) / 2;
        if (count_under(n, m, p1 + mid * p2, q1 + mid * q2) <= x) {
          l = mid;
        } else {
          r = mid;
        }
      }
      assert(l >= 0);
      p1 += l * p2;
      q1 += l * q2;
      assert(count_under(n, m, p1, q1) <= x);
      assert(count_under(n, m, p2, q2) > x);
    }

    ll limk2 = min(p1 ? (m - p2 - 1) / p1 : INF, q1 ? (n - q2 - 1) / q1 : INF);
    if (limk2 == 0) break;

    {
      ll l = -1;
      ll r = limk2 + 1;
//      assert(count_under(n, m, p2 + r * q2, q2 + r * q1) > x);

      while (r - l > 1) {
        ll mid = (l + r) / 2;
        if (count_under(n, m, mid * p1 + p2, mid * q1 + q2) > x) {
          l = mid;
        } else {
          r = mid;
        }
      }
      assert(l >= 0);
      p2 += l * p1;
      q2 += l * q1;
      assert(count_under(n, m, p1, q1) <= x);
      assert(count_under(n, m, p2, q2) > x);
    }


  }

  assert(count_under(n, m, p1, q1) <= x);
  assert(count_under(n, m, p2, q2) > x);

  x -= count_under(n, m, p1, q1);

  printf("%lld %lld\n", (x + 1) * q1 + 1, (x + 1) * p1 + 1);
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif


  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  for (int i = 0; i < q; i++) {
    ll x;
    scanf("%lld", &x);
    solve(n, m, x - 1);
  }

  return 0;
}
