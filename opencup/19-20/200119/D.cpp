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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

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

int deg(ll m, int x) {
  int cnt = 0;
  while (m % x == 0) {
    cnt++;
    m /= x;
  }
  return cnt;
}

void gcdex(ll a, ll b, ll &x, ll &y) {
  if (!a) {
    x = 0, y = 1;
    return;
  }
  ll x1, y1;
  gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
}

ll merge(ll mod1, ll r1, ll mod2, ll r2) {
  ll d = __gcd(mod1, mod2);
  assert(d == 1);
  if (r1 % d != r2 % d)
    return -1;
  ll rd = r1 % d;
  mod1 /= d, mod2 /= d, r1 /= d, r2 /= d;

  if (mod1 < mod2)
    swap(mod1, mod2), swap(r1, r2);

  ll k = (r2 - r1) % mod2;
  if (k < 0)
    k += mod2;

  ll x, y;
  gcdex(mod1, mod2, x, y);
  x %= mod2;
  if (x < 0)
    x += mod2;
  k *= x, k %= mod2;
  return (k * mod1 + r1) * d + rd;
}

inline ll mmul(ll a, ll b, ll mod) {
  return (__int128) a * (__int128) b % mod;

  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  ll k = (ll) ((long double) a * b / mod);
  ll res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}

inline ll mpow(ll a, ll b, ll mod) {
  if (mod == 1)
    return 0;
  ll res = 1;
  for (; b; b >>= 1, a = mmul(a, a, mod))
    if (b & 1) res = mmul(res, a, mod);
  return res;
}

inline ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

inline int randint(int l, int r) {
  static unsigned int seed = 239017u;
  seed = seed * 1664525u + 1013904223u;
  return l + seed % (r - l + 1);
}

//run \emph{only} if n%as[i]!=0 for all i
inline bool run_miller_rubbin(ll n) {
  assert(n > 27 && (n & 1));
  ll t = n - 1;
  int s = 0;
  while (!(t & 1)) {
    t >>= 1;
    s++;
  }
  const int as[] = {2, 3, 5, 7, 11, 13,
                    17, 19, 23, 27, -1};
  for (int i = 0; as[i] >= 0; i++) {
    ll cur = mpow(as[i], t, n);
    if (cur == 1)
      continue;
    bool good = false;
    for (int i2 = 0; i2 < s; i2++) {
      if (cur == n - 1) {
        good = true;
        break;
      }
      assert(0 <= cur && cur < n);
      cur = mmul(cur, cur, n);
    }
    if (!good) return false;
  }
  return true;
}

ll findp(ll m, int v) {
  for (ll i = 2; i <= 2e6; i++) {
    while (m % i == 0) {
      if (i % v == 1) return i;
      m /= i;
    }
  }
  if (m == 1) {
    return -1;
  }
  for (ll i = v + 1; i * i <= m; i += v) {
    while (m % i == 0) {
      if (i % v == 1) return i;
      m /= i;
    }
  }
  for (ll i = v + (m % v); i * i <= m; i += v) {
    while (m % i == 0) {
      if ((m / i) % v == 1) return m / i;
      m /= i;
    }
  }
  if (run_miller_rubbin(m)) {
    if (m % v == 1) {
      return m;
    }
  }
  return -1;
}

ll findphi(ll p, ll phi, int k) {
  assert(deg(phi, 2) >= k);
  ll phi2 = phi;
  while (phi2 % 2 == 0) phi2 /= 2;
  int ops = 0;
  while (ops++ < 100000) {
    ll r = (rand() * 1LL * RAND_MAX + rand()) % p;
    if (__gcd(r, p) != 1) continue;
    r = mpow(r, phi2, p);
    if (mpow(r, (1 << (k - 1)) , p) == 1) continue;
    ll rr = mpow(r, (1 << k), p);
    while (rr != 1) {
      rr = mmul(rr, rr, p);
      r = mmul(r, r, p);
    }
    assert(mpow(r, (1 << k), p) == 1);
    assert(mpow(r, (1 << (k - 1)), p) != 1);
    return r;
  }
  return -1;
}

ll solve(ll m, int k) {
  ll deg2 = deg(m, 2);
  if (deg2 >= k + 1) {
    ll r = findphi(1LL << deg2, 1LL << (deg2 - 1), k);
    if (r != -1) {
      return merge(m >> deg2, 1, 1LL << deg2, r);
    }
  }
  int v = (1 << k);
  ll p = findp(m, v);
  if (p == -1) return -1;
  ll degp = deg(m, p);
  ll phi = p - 1;
  ll pp = p;
  for (int i = 1; i < degp; i++) {
    pp *= p;
    phi *= p;
  }
  return merge(m / pp, 1, pp, findphi(pp, phi, k));

}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  ll m;
  int k;
  while (scanf("%lld %d", &m, &k) == 2) {
    ll ans = solve(m, k);
    if (ans != -1) {
      assert(mpow(ans, 1 << k, m) == 1);
      assert(mpow(ans, 1 << (k - 1), m) != 1);
    }
    printf("%lld\n", ans);
  }

  return 0;
}
