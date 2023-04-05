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

ll mul(ll a, ll b, ll mod) {
  ll x = ld(a) * ld(b) / ld(mod);
  ll res = a * b - x * mod;
  while (res < 0) res += mod;
  while (res >= mod) res -= mod;
#ifdef LOCAL
  assert(mod > 1e9 || (a * b) % mod == res);
#endif
  return res;
}

ll mpow(ll a, ll b, ll mod) {
  ll res = 1;
  while (b) {
    if (b & 1) res = mul(res, a, mod);
    a = mul(a, a, mod);
    b >>= 1;
  }
  return res;
}

void gcdex(ll a,ll b,ll &x,ll &y) {
  if (!a){
    x = 0, y = 1;
    return;
  }
  ll x1, y1;
  gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
}

ll norm(ll x, ll mod) {
  x %= mod;
  if (x < 0) x += mod;
  return x;
}

ll mod_inv(ll a, ll b) {
  ll x, y;
  gcdex(a, b, x, y);
  x = norm(x, b);
  assert(mul(a, x, b) == 1);
  return x;
}

ll ipow(ll a, int k) {
  ll res = 1;
  for (int i = 0; i < k; i++) {
    res *= a;
  }
  return res;
}

ll discrete_log(ll a, ll b, ll deg, ll q) {
//  eprintf("%lld %lld %lld %lld\n", a, b, deg, q);
  assert(mpow(a, deg, q) == 1);
  assert(mpow(b, deg, q) == 1);
  assert(a != 1);

  int S = sqrt(deg) + 5;
  vector<pair<ll, int>> v;

  ll res = 1;
  for (int i = 0; i < S; i++) {
    v.push_back({res, i});
    res = mul(res, a, q);
  }
  ll B = mod_inv(res, q);
  res = 1;
  sort(v.begin(), v.end());

  for (int i = 0; i < S; i++) {
    ll val = mul(res, b, q);
    auto it = lower_bound(v.begin(), v.end(), make_pair(val, -1));
    if (it != v.end() && it->first == val) {
      ll ans = norm(S * i + it->second, deg);
//      eprintf("ans = %lld\n", ans);
      assert(mpow(a, ans, q) == b);
      return ans;
    }
    res = mul(res, B, q);
  }

  assert(0);
}

void solve() {
  ll p, a, q;
  scanf("%lld %lld %lld", &p, &a, &q);
  if (a == 0) {
    printf("0\n");
    return;
  }
  if (q == 2) {
    printf("1\n");
    return;
  }
  if (p == q) {
    printf("%lld\n", a);
    return;
  }
  if ((q - 1) % p != 0) {
    ll k = mod_inv(p, q - 1);
    ll res = mpow(a, k, q);
    assert(mpow(res, p, q) == a);
    printf("%lld\n", res);
    return;
  }
  if (mpow(a, (q - 1) / p, q) != 1) {
    printf("-1\n");
    return;
  }

  int k = 0;
  ll Q = q - 1;
  while (Q % p == 0) {
    k++;
    Q /= p;
  }
  ll R, t;

  ll pk = ipow(p, k - 1);

  {
    ll x = mod_inv(norm(-Q, p), p);
    ll v = (ld(x) * ld(Q) + 1) / ld(p);
    for (int i = -5; i <= 6; i++) {
      assert(i < 6);
      if ((v + i) * p == x * Q + 1) {
        v = v + i;
        break;
      }
    }

    R = mpow(a, v, q);
    t = mul(mpow(R, p, q), mod_inv(a, q), q);

    assert(mpow(R, p, q) == mul(a, t, q));
    assert(mpow(t, pk, q) == 1);
  }

  ll pk_root = 1;
  while (mpow(pk_root, pk, q) <= 1) {
    pk_root = mpow(norm(rand(), q), (q - 1) / (pk * p), q);
  }

  while (pk != 1) {
//    eprintf("%lld %lld %lld %lld\n", R, t, pk, pk_root);
    assert(mpow(pk_root, pk * p, q) == 1);
    assert(mpow(pk_root, pk, q) != 1);

    ll deg = discrete_log(mpow(pk_root, pk, q), mod_inv(mpow(t, pk / p, q), q), p, q);
    ll x = mpow(pk_root, deg, q);
//    eprintf("x = %lld, deg = %lld\n", x, deg);
    R = mul(R, x, q);
    t = mul(t, mpow(x, p, q), q);
//    eprintf("new %lld %lld\n", R, t);

    pk_root = mpow(pk_root, p, q);
    pk /= p;

    assert(mpow(t, pk, q) == 1);
    assert(mpow(R, p, q) == mul(a, t, q));
  }
  printf("%lld\n", R);
  assert(mpow(R, p, q) == a);
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
