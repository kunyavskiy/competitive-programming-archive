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

struct tree {
  vector<ll> z;
  vector<int> t;
  int coef = 0;
  int lst = 0;

  tree() = default;
  tree(const vector<pair<int, ll>> &zs, int coef_) {
    coef = coef_;
    lst = 2;
    while (lst < (int) zs.size() + 1) lst *= 2;
    z = vector<ll>(2 * lst);
    for (int i = 0; i < (int) zs.size(); i++) {
      t.push_back(zs[i].first);
      z[i + lst] = zs[i].second * coef;
    }
    t.push_back(1e9);
    z[zs.size() + lst] = numeric_limits<ll>::max();
    for (int i = lst - 1; i > 0; i--) {
      z[i] = max(z[2 * i], z[2 * i + 1]);
    }
  }

  int get(int tm, ll val) {
    int pos = upper_bound(t.begin(), t.end(), tm) - t.begin();
    assert(pos != 0);
    pos--;
    val *= coef;
    pos += lst;
    while (z[pos] < val) {
      assert(pos != 1);
      if (pos % 2 == 1) pos++;
      pos /= 2;
    }
    while (pos < lst) {
      if (z[2 * pos] >= val) {
        pos = 2 * pos;
      } else {
        assert(z[2 * pos + 1] >= val);
        pos = 2 * pos + 1;
      }
    }
    assert(z[pos] >= val);
    return max(tm, t[pos - lst]);
  }
};

struct edge {
  int a, b, t;
};

struct dsu {
  vector<int> p;
  vector<set<int>> s;
  dsu(int n) : p(n), s(n) {
    for (int i = 0; i < n; i++) {
      p[i] = i;
    }
  }
  int get(int a) {
    if (a == p[a]) return a;
    return p[a] = get(p[a]);
  }
  vector<int> join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return {};
    if (s[a].size() > s[b].size()) swap(a, b);
    p[a] = b;
    vector<int> res;
    for (int x : s[a]) {
      if (s[b].count(x)) {
        res.push_back(x);
        s[b].erase(x);
      } else {
        s[b].insert(x);
      }
    }
    return res;
  }
};

void solve() {
  int n;
  scanf("%d", &n);
  vector<map<int, int>> g(n);
  vector<int> x(n);
  vector<int> y(n);
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }
  int m;
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    int a, b, l;
    scanf("%d%d%d", &a, &b, &l);
    --a, --b;
    g[a][b] = l;
    g[b][a] = l;
  }
  vector<vector<pair<int, ll>>> zs(n, vector<pair<int, ll>>(1, {-1, 0}));
  int k;
  scanf("%d", &k);
  for (int i = 0; i < k; i++) {
    int id, z;
    scanf("%d%d", &id, &z);
    --id;
    zs[id].emplace_back(i, zs[id].back().second + z);
  }
  vector<edge> es;

  set<pair<int, int>> q;
  for (int i = 0; i < n; i++) {
    q.emplace(g[i].size(), i);
  }

  vector<tree> mint, maxt;
  for (int i = 0; i < n; i++) {
    maxt.emplace_back(zs[i], 1);
    mint.emplace_back(zs[i], -1);
  }

  while (!q.empty()) {
    int v = q.begin()->second;
    q.erase(q.begin());
    auto remove = [&](int i, int j) {
      q.erase({g[i].size(), i});
      g[i].erase(j);
      if (!g[i].empty()) q.emplace(g[i].size(), i);
    };

    for (auto [u, lim] : g[v]) {
      auto sqr = [](int x) { return x * 1LL * x;};
      ll l2 = sqr(lim) - sqr(x[u] - x[v]) - sqr(y[u] - y[v]);
      ll l = sqrt(l2);
      while (l * 1LL * l > l2) l--;
      while (l * 1LL * l <= l2) l++;

      int time = k;
      for (int id = 0; id < (int)zs[v].size(); id++) {
        int from = zs[v][id].first;
        int to = (id == (int)zs[v].size() - 1) ? numeric_limits<int>::max() : zs[v][id+1].first;

        int r1 = maxt[u].get(from, zs[v][id].second + l);
        int r2 = mint[u].get(from, zs[v][id].second - l);
        int r = min(r1, r2);
        if (r < to) {
          time = min(time, r);
        }
      }
      eprintf("%d %d %d\n", u, v, time);
      es.push_back({u, v, time});
      remove(u, v);
    }
    g[v].clear();
  }

  sort(es.begin(), es.end(), [](edge a, edge b) {
    return a.t > b.t;
  });
  dsu d(n);
  int qs;
  scanf("%d", &qs);
  vector<int> ans(qs);
  for (int i = 0; i < qs; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    d.s[a].insert(i);
    d.s[b].insert(i);
  }

  for (auto & e : es) {
    for (auto qid : d.join(e.a, e.b)) {
      ans[qid] = e.t;
    }
  }

  for (int a : ans) {
    printf("%d\n", (a == k) ? -1 : (a + 1));
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();

  return 0;
}
