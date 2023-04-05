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
#include <random>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

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
#define int long long

typedef long long ll;
typedef long double ld;

ll fast(vector<ll> a, ll n) {
  int d = a.size();

  vector<int> b;
  while (n) {
    b.push_back(n % 2);
    n /= 2;
  }
  int lg = b.size();

  vector<ll> multmask0(1 << d), multmask1(1 << d);
  vector<ll> stupidmask0(1 << d), stupidmask1(1 << d);
  for (int mask = 0; mask < (1 << d); mask++) {
    ll nmask = 0;
    for (int t = 0; t < d; t++) if (a[t]) nmask ^= ((ll)mask) << t;
    for (int t = 0; t < d * 2; t++) {
      if (t % 2 == 0) {
        multmask0[mask] |= ((nmask >> t) & 1) << (t / 2);
        stupidmask0[mask] |= ((mask >> t) & 1) << (t / 2);
      } else {
        multmask1[mask] |= ((nmask >> t) & 1) << (t / 2);
        stupidmask1[mask] |= ((mask >> t) & 1) << (t / 2);
      }
    }
  }

  vector<ll> dp(1 << d);
  for (int i = lg; i >= 0; i--) {
    vector<ll> ndp(1 << d);
    for (int mask = 0; mask < (1 << d); mask++) {
      if (i == lg) {
        ndp[mask] = __builtin_popcount(mask);
      } else {
        ll mask0 = 0, mask1 = 0;
        if (b[i]) {
          mask0 = multmask0[mask];
          mask1 = multmask1[mask];
        } else {
          mask0 = stupidmask0[mask];
          mask1 = stupidmask1[mask];
        }
        ndp[mask] = dp[mask0] + dp[mask1];
      }
    }
    dp = ndp;
  }
  return dp[1];
}

vector<ll> mul(vector<ll> a, vector<ll> b) {
  vector<ll> c(a.size() + b.size() - 1);
  for (int i = 0; i < (int)a.size(); i++) {
    for (int j = 0; j < (int)b.size(); j++) {
      c[i + j] ^= a[i] & b[j];
    }
  }
  return c;
}

ll slow(vector<ll> a, ll n) {
  vector<ll> cur(1, 1);
  for (int i = 0; i < n; i++) cur = mul(cur, a);
  ll res = 0;
  for (ll x : cur) res += x;
  return res;
}

void stress() {
  for (int it = 0;; it++) {
    db(it);
    mt19937_64 rnd(it);

    ll n = rnd() % ((ll)100) + 1;
    int d = rand() % 20 + 2;
    vector<ll> a(d);
    for (int i = 0; i < d; i++) a[i] = rnd() % 2;

    auto ans1 = fast(a, n);
    auto ans2 = slow(a, n);
    if (ans1 != ans2) {
      db2(ans1, ans2);
      dbv(a);
      db(n);
      exit(0);
    }
  }
}

signed main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  //freopen("j.out", "w", stdout);
#endif
//stress();

  ll d;
  while (scanf("%lld", &d) == 1) {
    d++;
    vector<ll> a(d);
    for (int i = 0; i < d; i++) scanf("%lld", &a[i]);

    ll n;
    scanf("%lld", &n);

    ll res = fast(a, n);
    printf("%lld\n", res);
  }

  return 0;
}
