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

struct segtree {
  int n, N;
  vector<int> t;
  function<int(int, int)> f;

  segtree() {}
  segtree(vector<int> c, function<int(int, int)> ff) {
    f = ff;

    n = c.size();
    N = 1;
    while (N < n) N <<= 1;

    t.assign(2 * N, -1);
    for (int i = 0; i < n; i++) t[N + i] = c[i];
    for (int i = N - 1; i >= 1; i--) t[i] = f(t[i * 2], t[i * 2 + 1]);
  }

  int get(int l, int r) {
    l += N;
    r += N;
    int res = -1;
    while (l <= r) {
      if (l & 1) res = f(res, t[l]);
      if (!(r & 1)) res = f(res, t[r]);
      l = (l + 1) >> 1;
      r = (r - 1) >> 1;
    }
    return res;
  }

  void upd(int x, int y) {
    x += N;
    t[x] = y;
    while (x > 1) {
      x >>= 1;
      t[x] = f(t[x * 2], t[x * 2 + 1]);
    }
  }
};


void print(vector<int> v) {
  for (int i = 0; i < (int)v.size(); i++) printf("%d%c", v[i], " \n"[i + 1 == (int)v.size()]);
}

vector<int> subsolve(vector<int> p) {
  int n = p.size();
  int N = 1;
  while (N < n) N <<= 1;

  segtree tmax(vector<int>(N, 0), [&](int x, int y) { return max(x, y); });

  vector<int> dp(n);
  for (int i = 0; i < n; i++) {
    dp[i] = tmax.get(0, p[i]) + 1;
    tmax.upd(p[i], dp[i]);
  }

//  for (int x : dp) cerr << x << " ";
//  cerr << endl;

  int K = 0;
  while ((1 << K) < n + 1) K++;

  vector<vector<int>> pr(n + 1, vector<int>(K, -1));
  pr[0].assign(K, 0);
  vector<int> h(n + 1);

  auto lca = [&](int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    for (int i = 0; i < K; i++) if ((h[u] - h[v]) & (1 << i)) u = pr[u][i];
    if (u == v) return u;
    for (int i = K - 1; i >= 0; i--) {
      if (pr[u][i] != pr[v][i]) {
        u = pr[u][i];
        v = pr[v][i];
      }
    }
    return pr[u][0];
  };

  int mx = *max_element(dp.begin(), dp.end());

  vector<vector<int>> vct(mx + 1);
  for (int i = 0; i < n; i++) {
    vct[dp[i]].push_back(p[i]);
  }

  vector<segtree> tlca(mx + 1);
  for (int i = 0; i <= mx; i++) {
    sort(vct[i].begin(), vct[i].end());
    int cn = 1;
    while (cn < (int)vct[i].size()) cn <<= 1;

    tlca[i] = segtree(vector<int>(cn, -1), [&](int x, int y) {
      if (x == -1) return y;
      if (y == -1) return x;
//      cerr << x << " " << y << endl;
      return lca(x, y);
    });
  }

  int o = 0;
    o++;
  for (int i = 0; i < n; i++) {
    int id = lower_bound(vct[dp[i] - 1].begin(), vct[dp[i] - 1].end(), p[i]) - vct[dp[i] - 1].begin();
    int x = tlca[dp[i] - 1].get(0, id - 1);
    if (x == -1) x = 0;
//    else x++;

    h[i + 1] = h[x] + 1;
    pr[i + 1][0] = x;
    for (int j = 1; j < K; j++) pr[i + 1][j] = pr[pr[i + 1][j - 1]][j - 1];

    id = lower_bound(vct[dp[i]].begin(), vct[dp[i]].end(), p[i]) - vct[dp[i]].begin();
    tlca[dp[i]].upd(id, i + 1);
  }
  h.erase(h.begin());
  for (int i = 0; i < n; i++) h[i]--;
  return h;
}

vector<int> solve(vector<int> p) {
  int n = p.size();
  auto v1 = subsolve(p);
  reverse(p.begin(), p.end());
  for (int &x : p) x = n - 1 - x;
  auto v2 = subsolve(p);
  for (int i = 0; i < n; i++) v1[i] += v2[n - 1 - i];
  return v1;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> p(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &p[i]);
      p[i]--;
    }

    print(solve(p));
  }

  return 0;
}
