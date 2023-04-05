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

const int MAXN = 1e8;
bitset<MAXN> isnp;
vector<int> ps;

vector<ll> primes(ll n) {
  vector<ll> p;
  for (int i: ps) {
    if (n % i == 0) {
      p.push_back(i);
    }
    while (n % i == 0) n /= i;
  }
  if (n != 1) {
    p.push_back(n);
  }
  return p;
}

int ord(ll n, ll p) {
  int k = 0;
  while (n % p == 0) {
    k++;
    n /= p;
  }
  return k;
}

int MOD = 1000000007;

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

void solve(ll n) {
  vector<ll> p = primes(n);
  vector<pair<ll, int>> md;
  vector<ll> divs;
  md.push_back({1, 1});
  divs.push_back(1);

  for (ll i : p) {
    int k = ord(n, i);
    int s = (int)divs.size();
    for (int j = 0; j < s * k; j++) {
      divs.push_back(divs[j] * i);
    }
    s = (int)md.size();
    for (int j = 0; j < s; j++) {
      md.push_back({md[j].first * i, -md[j].second});
    }
  }
  sort(md.begin(), md.end());
  sort(divs.begin(), divs.end());

  MOD = 1e9 + 7;
  if (n % MOD == 0) MOD += 2;

  vector<int> b(divs.size());
  b[0] = 1;

  auto id = [&](ll x) {
    return lower_bound(divs.begin(), divs.end(), x) - divs.begin();
  };

  auto addc = [](int &a, int b, int c) {
    if (c > 0) {
      add(a, b);
    } else {
      sub(a, b);
    }
  };

  for (int i = 1; i < (int)divs.size(); i++) {
    ll div = divs[i];
    for (auto d : md) {
      if (d.first != 1 && div % d.first == 0) {
        addc(b[i], b[id(div / d.first)], -d.second);
      }
    }
    b[i] = mul(b[i], 2);
  }
  int inv2 = minv(2);
  for (int i = 1; i < (int)divs.size(); i++) {
    b[i] = mul(b[i], inv2);
  }

  vector<int> b2(divs.size());
  for (int i = 0; i < (int)divs.size(); i++) {
    b2[i] = mul(b[i], minv(divs[i] % MOD));
  }

  for (int i = 1; i < (int)divs.size(); i++) {
    ll div = divs[i];
    for (auto d : md) {
      if (d.first != 1 && div % d.first == 0) {
        addc(b2[i], b2[id(div / d.first)], -d.second);
      }
    }
  }

  for (int i = 0; i < (int)divs.size(); i++) {
    sub(b2[i], mul(b[i], minv(divs[i] % MOD)));
  }


  vector<int> a(divs.size());

  for (int i = 1; i < (int)divs.size(); i++) {
    ll div = divs[i];
    for (auto d : md) {
      if (d.first != 1 && div % d.first == 0) {
        addc(a[i], a[id(div / d.first)], -d.second);
      }
    }
    a[i] = mul(a[i], 2);
    add(a[i], mul(div % MOD, b2[i]));
    sub(a[i], b[i]);
  }

  for (int i = 1; i < (int)divs.size(); i++) {
    ll div = divs[i];
    add(a[i], mul(div % MOD, b2[i]));
    sub(a[i], b[i]);
    a[i] = mul(a[i], inv2);
  }

  printf("%d\n", a.back());
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  for (int i = 2; i < MAXN; i++) {
    if (!isnp[i]) {
      ps.push_back(i);
      if (i * 1LL * i > MAXN) continue;
      for (int j = i * i; j < MAXN; j += i) {
        isnp[j] = 1;
      }
    }
  }

  int t;
  scanf("%d", &t);
  while (t-->0) {
    ll n;
    scanf("%lld\n", &n);
    solve(n + 1);
  }


  return 0;
}
