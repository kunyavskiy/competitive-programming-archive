#ifndef BZ
#pragma GCC optimize "-O3"
#endif
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)

using ll = long long;
using ld = long double;
using ull = unsigned long long;

using namespace std;

const ll MOD = 998244353;

ll pw(ll a, ll b) {
  ll ans = 1;
  while (b) {
    while (!(b & 1))
      b >>= 1, a = (a * a) % MOD;
    ans = (ans * a) % MOD, --b;
  }
  return ans;
}

const int N = 210000;
vector<int> eds[N];
vector<ll> down[N];
ll up[N];
int n;

struct Fenwick {
  int n;
  vector<ll> t;
  Fenwick(int n) : n(n), t(n) {}
  void add(int i, ll x) {
    for (; i < n; i |= i + 1) {
      t[i] += x;
    }
  }
  ll get(int i) {
    ll res = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
      res += t[i];
    }
    return res;
  }
};

ll cnt1 = 0;
ll cnt2 = 0;

Fenwick fen1(N);
int used[N];
vector<int> other;

vector<ll> parts1, parts2;

void dfs1(int v, int p = -1) {
  used[v] = 1;
  cnt1 = (cnt1 + fen1.get(v));
  if (v != 0) {
    fen1.add(v, 1);
  }
  for (int u : eds[v]) {
    if (u == p) {
      continue;
    }
    dfs1(u, v);
  }
  if (v != 0) {
    fen1.add(v, -1);
  }
}

void dfs2(int v, int p, ll sm) {
  if (v != 0) {
    ll cc = (int)other.size() - fen1.get(v);
    sm += cc;
  }

  parts1.push_back(sm);

  for (int u : eds[v]) {
    if (u == p) {
      continue;
    }
    dfs2(u, v, sm);
  }
}

void dfs3(int v, int p) {
  fen1.add(v, 1);
  ll prev = fen1.get(n) - fen1.get(v);
  for (int u : eds[v]) {
    if (u == p) {
      down[v].push_back(0);
      continue;
    }
    dfs3(u, v);
    ll cur = fen1.get(n) - fen1.get(v);
    down[v].push_back(cur - prev);
    cnt2 += down[v].back();
    up[v] -= down[v].back();
    prev = cur;
  }
}

void dfs4(int v, int p, ll sm) {
  sm += up[v];
  parts2.push_back(sm);
  for (int i = 0; i < (int)eds[v].size(); ++i) {
    int u = eds[v][i];
    if (u == p) {
      continue;
    }
    dfs4(u, v, sm - down[v][i]);
  }
}

int main() {
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cout.setf(ios::fixed), cout.precision(20);
  cin >> n;
  for (int i = 0; i < n - 2; ++i) {
    int a, b;
    cin >> a >> b;
    --a, --b;
    eds[a].push_back(b);
    eds[b].push_back(a);
  }

  dfs1(0);
  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      other.push_back(i);
    }
  }

  fen1 = Fenwick(N);
  for (int i : other) {
    fen1.add(i, 1);
  }
  dfs2(0, -1, cnt1);

  for (int i = 0; i < (int)other.size(); ++i) {
    up[other[i]] = other.size() - 1 - i;
  }

  fen1 = Fenwick(N);
  dfs3(other[0], -1);

  dfs4(other[0], -1, cnt2);

  auto get_sum = [&](const vector<ll> &a) {
    ll res = 0;
    for (ll x : a) {
      res = (res + pw(2, x)) % MOD;
    }
    return res;
  };

  ll ans = (get_sum(parts1) * get_sum(parts2)) % MOD;
  if (other.size() == 1) {
    ans = (ans + pw(2, cnt1)) % MOD;
  }

  cout << ans << "\n";

  return 0;
}
