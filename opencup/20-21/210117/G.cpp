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

typedef long long ll;
typedef long double ld;

// mod should be not greater than 4e18
inline int64_t mmul(uint64_t a, uint64_t b, uint64_t mod) {
  if (mod < int(1e9)) return a * b % mod;
  uint64_t k = (uint64_t)((long double)a * b / mod);
  uint64_t res = a * b - (k - 1) * mod;
  while (res >= mod) res -= mod;
  return res;
}

ll mmul(ll a, ll b, ll mod) {
  return mmul((uint64_t)a, (uint64_t)b, (uint64_t)mod);
}

inline ll mpow(ll a, ll b, ll mod) {
  if (mod==1)
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
  seed=seed*1664525u+1013904223u;
  return l+seed%(r-l+1);
}

//run \emph{only} if n%as[i]!=0 for all i
inline bool run_miller_rubbin(ll n) {
  assert(n > 27 && (n & 1));
  ll t = n - 1; int s = 0;
  while (!(t & 1)) {
    t >>= 1;
    s++;
  }
  const int as[] = { 2, 3, 5, 7, 11, 13,
                     17, 19, 23, 27, -1 };
  for (int i = 0; as[i] >= 0; i++) {
    ll cur = mpow(as[i], t, n);
    if (cur==1)
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

const int MAXD = 110;

//\emph{only} for n>MAXD
inline void pollard(ll n, vector<ll>& res) {
  if (n < MAXD) {
    for (int i = 2; i * i <= n; i++) {
      while (n % i == 0) {
        n /= i;
        res.push_back(i);
      }
    }
    if (n != 1) {
      res.push_back(n);
    }
    return;
  }
  if (run_miller_rubbin(n)) {
    res.push_back(n);
    return;
  }

  const ll MAXX = int(1e9);

  int sumIt = 0;
  for (int i = 0; i<3 || sumIt<1000; i++) {
    int q = randint(2, MAXD);
    ll x = randint(1, min(MAXX, n - 1));
    ll y = x, g = 0;
    int maxJ = 1 << (i + 18);
    for (int j = 1; j < maxJ; j++) {
      sumIt++;
      x = mmul(x, x, n);
      if ((x += q) >= n) x -= n;
      ll z = abs(x - y);
      g = gcd(z, n);
      if (g != 1) break;
      if ((j & (j - 1)) == 0) {
        y = x;
      }
    }
    if (1 < g && g < n) {
      pollard(g, res);
      pollard(n / g, res);
      return;
    }
  }
  eprintf("Failed at n=%lld\n", n);
  assert(false);
}

const int MAX = 3e5;
vector<int> primes;
vector<int> minp;

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  minp.resize(MAX);

  for (int i = 2; i < MAX; i++) {
    if (minp[i] == 0) {
      minp[i] = i;
      primes.push_back(i);
    }
    for (int j = 0; primes[j] <= minp[i] && primes[j] * i < MAX; j++) {
      minp[primes[j] * i] = primes[j];
    }
  }

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<ll>> v(n);
    vector<ll> x(n);
    vector<ll> y(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &x[i]);
      y[i] = x[i];
      for (int p : primes) {
        while (y[i] % p == 0) {
          y[i] /= p;
          v[i].push_back(p);
        }
      }
    }
    vector<int> cands;
    for (int i = 1; i < n; i++) {
      cands.push_back(__gcd(y[i], y[i-1]));
    }
    for (int i = 1; i < n; i++) {
      cands.push_back(sqrt(y[i]));
    }

    for (ll g : cands) {
      for (int j = 0; j < n; j++) {
        if (y[j] % g == 0 && g != 1 && g != y[j]) {
          v[j].push_back(g);
          v[j].push_back(y[j] / g);
        }
      }
    }

    for (int i = 0; i < n; i++) {
      if (y[i] != 1 && run_miller_rubbin(y[i])) {
        v[i].push_back(y[i]);
      }
    }

    for (int i = 0; i < n; i++) {
      sort(v[i].begin(), v[i].end());
      v[i].erase(unique(v[i].begin(), v[i].end()), v[i].end());
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (ll p : v[i]) {
        for (int j = i + 1; j <= n; j++) {
          if (j == n || x[j] % p != 0) {
            ans ^= (j - i);
            eprintf("%lld %d %d\n", p, i, j);
            break;
          }
          v[j].erase(find(v[j].begin(), v[j].end(), p));
        }
      }
    }
    printf("%s\n", (ans == 0 ? "Second" : "First"));
  }


  return 0;
}
