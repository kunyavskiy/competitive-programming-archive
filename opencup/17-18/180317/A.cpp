#include <bits/stdc++.h>

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, ll b) {
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

pair<ll, ll> getxy(ll n) {
  ll l = 0;
  ll r = 2e9;
  while (r - l > 1) {
    ll m = (l + r) / 2;
    if (m * (m + 1) / 2 >= n) {
      r = m;
    } else {
      l = m;
    }
  }
  ll last = n - r * (r - 1) / 2;
  assert(0 < last && last <= r);
  return {r, r - last};
}

const long long LIM = 1LL << 62;

const int N = 1e5, K = 100;

ll C[N][K];

ll cnk(ll n, ll k) {
  if (n < k || k < 0) return 0;
  k = min(k, n - k);
  assert(k < K - 2);
  if (n <= N - 2)
    return C[n][k];
  long double res = 1;
  for (int i = 1; i <= k; i++) {
    res *= n - i + 1;
    res /= i;
    if (res >= LIM)
      return LIM;
  }
  return roundl(res);
}

int solve_cnk(ll n, ll k, ll num) {
  int res = 0;
  assert(k <= K);
  res = 0;
  while (k > 0) {
    ll l = k - 1, r = max(l + 1, 1LL);
    while (r < n && cnk(r, k) <= num)
      r = min(r * 2, n);
    while (r > l + 1) {
      ll m = (l + r) / 2;
      if (cnk(m, k) > num)
        r = m;
      else
        l = m;
    }
    num -= cnk(l, k);
    add(res, mpow(2, l));
    n = l, k--;
  }
  return res;
}

int solve_cn(ll n, ll num) {
  ll k;
  long double res = 1;
  for (k = 0;; k++) {
    ll c = (res > LIM ? LIM : roundl(res));
    res *= n - k, res /= k + 1;
    if (c <= num) {
      num -= c;
    } else {
      break;
    }
  }
  return solve_cnk(n, k, num);
}

int solve( ll n, ll k ) {
  ll x, y;
  {
    auto r = getxy(n);
    x = r.first;
    y = r.second;
  }

  int res = mpow(2, x);
  sub(res, mpow(2, y));
  if (y == 0) {
    if (k == 1) {
      return res;
    } else {
      return -1;
    }
  }
  if (y <= 60 && (1LL << (y - 1)) < k) {
    return -1;
  }
  add(res, solve_cn(y - 1, k - 1));
  return res;
}

unordered_map<ll, int> m;

int main() {
  C[0][0] = 1;
  for (int i = 0; i < N - 1; i++)
    for (int j=  0; j < K - 1; j++) {
      if (C[i][j] > LIM) C[i][j] = LIM;
      C[i + 1][j + 1] += C[i][j];
      C[i + 1][j] += C[i][j];
    }
  int t;
  scanf("%d", &t);
  while (t-->0) {
    ll n, k;
    scanf("%lld %lld\n", &n, &k);
    // ll hash = n * ((ll)1e18 + 3) + k * (int(1e9) + 9);
    // if (m.count(hash)) {
    //   printf("%d\n", m[hash]);
    //   continue;
    // }
    int res = solve( n, k);
    printf("%d\n", res);
    // m[hash] = res;
  }
}
