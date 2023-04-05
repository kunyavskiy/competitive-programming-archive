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

inline ll rm_mmul(ll a, ll b, ll mod) {
  assert(0 <= a && a < mod);
  assert(0 <= b && b < mod);
  if (mod < int(1e9)) return a * b % mod;
  ll k = (ll)((long double)a * b / mod);
  ll res = a * b - k * mod;
  res %= mod;
  if (res < 0) res += mod;
  return res;
}
inline ll rm_mpow(ll a, ll b, ll mod) {
  if (mod==1)
    return 0;
  ll res = 1;
  for (; b; b >>= 1, a = rm_mmul(a, a, mod))
    if (b & 1) res = rm_mmul(res, a, mod);
  return res;
}
inline ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}
inline bool run_miller_rubbin(ll n) {
  if (n <= 1000) {
    for (int i = 2; i * i <= n; i++) {
      if (n % i == 0) {
        return false;
      }
    }
    return true;
  }
  assert(n > 27 && (n & 1));
  ll t = n - 1; int s = 0;
  while (!(t & 1)) {
    t >>= 1;
    s++;
  }
  const int as[] = { 2, 3, 5, 7, 11, 13,
                     17, 19, 23, 27, -1 };
  for (int i = 0; as[i] >= 0; i++) {
    ll cur = rm_mpow(as[i], t, n);
    if (cur==1)
      continue;
    bool good = false;
    for (int i2 = 0; i2 < s; i2++) {
      if (cur == n - 1) {
        good = true;
        break;
      }
      assert(0 <= cur && cur < n);
      cur = rm_mmul(cur, cur, n);
    }
    if (!good) return false;
  }
  return true;
}

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

int ans;

void solve(const vector<int>& p, int pos, int a, int b) {
//  eprintf("pos = %d, a = %d, b = %d\n", pos, a, b);
  if (pos == (int)p.size()) {
    add(a, MOD - 1);
//    eprintf("a = %d, b = %d\n", a, (b > MOD / 2) ? b - MOD : MOD);
    add(ans, mul(a, b));
    return;
  }
  solve(p, pos + 1, mpow(a, p[pos] + 1), b);
  solve(p, pos + 1, mpow(a, p[pos] + 0), mul(b, MOD - 2));
  if (p[pos] >= 2) {
    solve(p, pos + 1, mpow(a, p[pos] - 1), b);
  }
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  ll n;
  scanf("%lld\n", &n);

  vector<int> ps;

  for (ll i = 2; i * i * i <= n || i <= 1000000; i++) {
    int c = 0;
    while (n % i == 0) {
      n /= i;
      c += 1;
    }
    if (c) {
      ps.push_back(c);
    }
  }

  if (n != 1) {
    ll sq = sqrt(n);
    while (sq * sq < n) sq++;
    while (sq * sq > n) sq--;
    if (sq * sq == n) {
      ps.push_back(2);
    } else if (run_miller_rubbin(n)) {
      ps.push_back(1);
    } else {
      ps.push_back(1);
      ps.push_back(1);
    }
  }

  sort(ps.begin(), ps.end());

  solve(ps, 0, 2, 1);

  printf("%d\n", ans);

  return 0;
}
