#include <bits/stdc++.h>

#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using namespace std;

const ll MOD = 1e9 + 7;

ll pw(ll a, ll b) {
        ll ans = 1; while (b) {
                while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
                ans = (ans * a) % MOD, --b;
        } return ans;
}


const ll MX = 3000;

ll fc[MX];
ll bfc[MX];
ll K;
ll dp[MX];
ll idp[MX];

void init() {
  fc[0] = 1;
  for (int i = 1; i < MX; ++i) {
    fc[i] = (fc[i - 1] * i) % MOD;
  }
  bfc[MX - 1] = pw(fc[MX - 1], MOD - 2);
  for (int i = MX - 2; i >= 0; -- i) {
    bfc[i] = (bfc[i + 1] * (i + 1)) % MOD;
  }

  dp[0] = 1;
  for (int i = 1; i < MX; ++i) {
    dp[i] = dp[i - 1] * (K - i + 1) % MOD;
  }
  for (int i = 0; i < MX; ++i) {
    idp[i] = pw(dp[i], MOD - 2);
  }
}

ll cnk(ll n, int k) {
  if (n < k) {
    return 0;
  }
  ll ans = dp[K - (n - k)] * idp[K - n] % MOD;
//  ll ans = 1;
//  for (ll x = n; x > n - k; --x) {
//    ans = (ans * x) % MOD;
//  }
  return ans * bfc[k] % MOD;
}

ll get_cntpat(int m, ll k) {
  ll ans = 0;
  ll i2 = pw(2, MOD - 2);
  ll x2 = 1;
  for (int x = 0; x * 2 <= m; ++x, x2 = (x2 * i2) % MOD) {
    ans = (ans + fc[m] * cnk(k, x) % MOD * cnk(k - x, m - 2 * x) % MOD * x2 % MOD) % MOD;
  }
  return ans;
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cout.setf(ios::fixed), cout.precision(20);
  int n, m;
  ll k;

  cin >> n >> m >> k;
  K = k;
  init();

  ll all = get_cntpat(m, k);
  ll ans = 0;
  for (int p = 1; p * 2 <= m; ++p) {
    ll cnt = cnk(k, p) * fc[p] % MOD * get_cntpat(m - 2 * p, k - p) % MOD;
    all = (all - cnt + MOD) % MOD;

    int len = m;
    for (int oc = 1; len <= n; ++oc, len += m - p) {
      ll cur = pw(k, n - len) * (n - len + 1) % MOD * cnt % MOD;
      if (oc % 2 == 1) {
        ans = (ans + cur) % MOD;
      } else {
        ans = (ans - cur + MOD) % MOD;
      }
    }
  }

  ll cur = pw(k, n - m) * (n - m + 1) % MOD * all % MOD;
  ans = (ans + cur) % MOD;

  cout << ans << "\n";

  return 0;
}

