#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <numeric>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

typedef vector<int> perm;
typedef long long llong;

perm operator *(const perm& a, const perm& b) {
  assert(a.size() == b.size());
  perm c(a.size());
  for (int i = 0; i < (int)a.size(); i++) {
    c[i] = a[b[i]];
  }
  return c;
}

perm inv(const perm& a) {
  perm c(a.size());
  for (int i = 0; i < (int)a.size(); i++)
    c[a[i]] = i;
  return c;
}

perm identity_perm(int n) {
  perm c(n);
  for (int i = 0; i < n; i++)
    c[i] = i;
  return c;
}

void DFS(const perm& cur, const vector<perm>& generators, vector<perm>& sigma) {
  sigma[cur[0]] = cur;
  for (const perm& g : generators) {
    perm y = g * cur;
    if (sigma[y[0]].empty()) {
      DFS(y, generators, sigma);
    }
  }
}

void reduceGenerators(vector<perm>& generators) {
  if (generators.empty())
    return;
  int n = generators.front().size();
  int pt = 0;
  for (int i = 0; i < n; i++) {
    vector<int> posByFirst(n, -1);
    for (int j = pt; j < (int)generators.size(); j++) {
      perm& g = generators[j];
      assert(g[i] >= i);
      if (g[i] == i)
        continue;
      else if (posByFirst[g[i]] == -1) {
        posByFirst[g[i]] = pt;
        g.swap(generators[pt]);
        pt++;
      } else {
        g = inv(generators[posByFirst[g[i]]]) * g;
      }
    }
  }
  assert(pt <= n * (n - 1) / 2);
  generators.resize(pt);
}

void calc(vector<perm> generators, vector<vector<perm>> &result) {
  if (generators.empty())
    return;
  int n = generators.front().size();
  if (n == 0)
    return;

  vector<perm> sigma(n, perm());
  DFS(identity_perm(n), generators, sigma);
  vector<perm> invSigma(n, perm());
  for (int i = 0; i < n; i++)
    invSigma[i] = inv(sigma[i]);

  vector<perm> newGenerators;
  vector<perm> current;
  for (int i = 0; i < n; i++) {
    if (sigma[i].empty())
      continue;
    current.push_back(sigma[i]);
    for (const perm& g : generators) {
      perm x = g * sigma[i];
      assert(!invSigma[x[0]].empty());
      newGenerators.emplace_back(invSigma[x[0]] * x);
    }
  }

  reduceGenerators(newGenerators);
  for (perm& g : newGenerators) {
    assert(g[0] == 0);
    g.erase(g.begin() + 0);
    for (int& x : g)
      --x;
  }
  calc(newGenerators, result);
  for (auto& x : result) {
    for (auto &p : x) {
      for (int& y : p) y++;
      p.insert(p.begin(), 0);
    }
  }
  result.push_back(current);
}

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<perm> gens(m, perm(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &gens[i][j]);
        --gens[i][j];
      }
    }
    vector<vector<perm>> result;
    calc(gens, result);
    int ans = 0;

    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        dp[i][j] = 1;
      }
    }
    for (const auto &v : result) {
      vector<vector<int>> ndp(n, vector<int>(n, 0));
      for (int a = 0; a < n; a++) {
        for (int b = 0; b < n; b++) {
          for (const auto &p : v) {
            add(ndp[p[a]][p[b]], dp[a][b]);
          }
        }
      }
      dp = std::move(ndp);
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        add(ans, dp[j][i]);
      }
    }
    printf("%d\n", ans);
  }

  return 0;
}
