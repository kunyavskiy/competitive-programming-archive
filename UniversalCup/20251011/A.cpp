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

constexpr int MOD = 998244353;

void add(int& a, int b) {
    if ((a += b) >= MOD) a -= MOD;
}

void sub(int& a, int b) {
    if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
   return (int)((a * 1LL * b) % MOD);
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

int fact[510000];
int ifact[510000];

int cnk(int n, int k) {
  if (n < k) return 0;
  return mul(fact[n], mul(ifact[k], ifact[n - k]));
}

vector<int> &add(vector<int> &a, const vector<int> &b, int shift, int coef) {
  assert(shift >= 0);
  if (a.size() < b.size() + shift) {
    a.resize(b.size() + shift);
  }
  for (int i = 0; i < (int)b.size(); i++) {
    a[i + shift] += b[i] * coef;
  }
  return a;
}

void solve() {
  int n, k;
  scanf("%d%d", &n, &k);
  vector<vector<int>> g(n);
  vector<int> p(n);
  for (int i = 1; i < n; i++) {
    scanf("%d", &p[i]);
    --p[i];
    g[p[i]].push_back(i);
  }
  if (k == 1) {
    printf("%d\n", n);
    return;
  }
  vector<vector<int>> dp(n, vector<int>(1, 1));
  for (int i = n - 1; i > 0; i--) {
    add(dp[p[i]], dp[i], 1, 1);
  }

  vector<int> count(n + 1);

  //eprintf("======\n");
  auto dfs = [&](auto self, int v, vector<int> &data) -> void {
    add(data, dp[v], 0, 1);
    for (int i = 1; i < (int)data.size(); i++) {
      //eprintf("%d on disatnace %d from %d\n", data[i], i, v);
      count[data[i]]++;
    }
    data.insert(data.begin(), 0);
    for (int u : g[v]) {
      add(data, dp[u], 2, -1);
      self(self, u, data);
      add(data, dp[u], 2, 1);
    }
    data.erase(data.begin());
    add(data, dp[v], 0, -1);
  };
  auto v = vector<int>();
  dfs(dfs, 0, v);
  int ans = 0;
  for (int i = 1; i < (int)count.size(); i++) {
    add(ans, mul(count[i], cnk(i, k-1)));
  }
  printf("%d\n", ans);
}

int main() {
  #ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  fact[0] = ifact[0] = 1;
  for (int i = 1; i < (int)size(fact); i++) {
    fact[i] = mul(fact[i - 1], i);
    ifact[i] = minv(fact[i]);
  }

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
