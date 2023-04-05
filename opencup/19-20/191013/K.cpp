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
#include <numeric>
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

typedef long long ll;
typedef long double ld;

const ll INF = 1e18;
const int K = 4;

struct sep {
  int centr;
  vector<int> v1, v2;
};

template <typename T, class F = function<T(const T&, const T&)>>
class sparse_table {
public:
  int n;
  vector<vector<T>> mat;
  F func;

  sparse_table() {}
  sparse_table(const vector<T>& a, const F& f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = min(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return min(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};


struct tree {
  int n;
  vector<vector<pair<int, int>>> e;
  vector<int> h;
  vector<ll> d;
  sparse_table<pair<int, int>> s;
  vector<pair<int, int>> vct;
  vector<int> L, R;
  vector<int> id, coef;

  tree(int _n) {
    n = _n;
    e.resize(n);
    L.resize(n);
    R.resize(n);
    d.resize(n);
    h.resize(n);
    id.resize(n);
    coef.resize(n);
  }

  void add_edge(int u, int v, int w) {
    e[u].push_back({v, w});
    e[v].push_back({u, w});
  }

  void read() {
    for (int i = 0; i < n - 1; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      u--; v--;
      add_edge(u, v, w);
    }
  }

  void dfs(int v, int ch, int pr, ll cd) {
    d[v] = cd;
    L[v] = R[v] = vct.size();
    vct.push_back({ch, v});
    for (auto o : e[v]) {
      int to = o.first;
      if (to == pr) continue;
      dfs(to, ch + 1, v, cd + o.second);
      R[v] = vct.size();
      vct.push_back({ch, v});
    }
  }

  void init() {
    dfs(0, 0, -1, 0);
    s = sparse_table<pair<int, int>>(vct, [&](const pair<int, int> &x, const pair<int, int> &y) {
      return min(x, y);
    });
  }

  int lca(int u, int v) {
    int l = L[u], r = L[v];
    if (l > r) swap(l, r);
    int w = s.get(l, r).second;
    return w;
  }

  ll dist(int u, int v) {
    int w = lca(u, v);
    return d[u] + d[v] - 2 * d[w];
  }


  sep centr(vector<int> vct, bool sorted = false) {
    auto cmp = [&](int u, int v) {
      return L[u] < L[v];
    };
    if (!sorted) {
      sort(vct.begin(), vct.end(), cmp);
    }
    vector<int> nvct;
    for (int i = 0; i < (int)vct.size(); i++) {
      nvct.push_back(vct[i]);
      if (i + 1 < (int)vct.size()) {
        nvct.push_back(lca(vct[i], vct[i + 1]));
      }
    }
    sort(nvct.begin(), nvct.end(), cmp);
    nvct.resize(unique(nvct.begin(), nvct.end()) - nvct.begin());

    vector<pair<int, int>> ed;
    vector<int> st;
    for (int i = 0; i < (int)nvct.size(); i++) {
      int v = nvct[i];
      while (!st.empty() && !(L[st.back()] <= L[v] && R[v] <= R[st.back()])) st.pop_back();
      if (!st.empty()) {
        ed.push_back({st.back(), v});
      }
      st.push_back(v);
    }

    for (int i = 0; i < (int)nvct.size(); i++) {
      id[nvct[i]] = i;
    }
    int m = nvct.size();
    vector<vector<int>> g(m);
    vector<int> cnt(m, -1);
    for (auto o : ed) {
      g[id[o.first]].push_back(id[o.second]);
      g[id[o.second]].push_back(id[o.first]);
    }

    for (int v : nvct) coef[id[v]] = 0;
    for (int v : vct) coef[id[v]] = 1;

    function<void(int)> dfs1 = [&](int v) {
      cnt[v] = coef[v];
      for (int to : g[v]) {
        if (cnt[to] != -1) continue;
        dfs1(to);
        cnt[v] += cnt[to];
      }
    };
    int c = 0;
    dfs1(c);
    int all = cnt[c], pr = -1;
    while (1) {
      bool f = 0;
      for (int to : g[c]) {
        if (to != pr && cnt[to] * 2 >= all) {
          pr = c;
          c = to;
          f = 1;
          break;
        }
      }
      if (!f) break;
    }
    cnt.assign(cnt.size(), -1);
    vector<vector<int>> vv(m);
    function<void(int, int)> dfs2 = [&](int v, int x) {
      if (x != -1 && coef[v]) {
        vv[x].push_back(v);
      }
      cnt[v] = 1;
      for (int to : g[v]) {
        if (cnt[to] != -1) continue;
        dfs2(to, x == -1 ? to : x);
        cnt[v] += cnt[to];
      }
    };
    dfs2(c, -1);

    sep res;
    res.centr = nvct[c];
    int cur = 0;
    sort(g[c].begin(), g[c].end(), [&](int u, int v) {
      return vv[u].size() < vv[v].size();
    });
    for (int to : g[c]) {
      cur += vv[to].size();
      if (cur * 2 >= all) {
        for (auto v : vv[to]) res.v1.push_back(nvct[v]);
      } else {
        for (auto v : vv[to]) res.v2.push_back(nvct[v]);
      }
    }
    if (res.v1.size() < res.v2.size()) res.v1.swap(res.v2);
    return res;
  }

  void print() {
    for (int i = 0; i < n; i++) {
      for (auto o : e[i]) {
        if (i < o.first) {
          cout << i << " " << o.first << " " << o.second << endl;
        }
      }
    }
  }
};

void print(vector<ll> v) {
  for (auto x : v) printf("%lld\n", x);
}

vector<ll> solve(int n, tree t1, tree t2) {
  t1.init();
  t2.init();

  vector<ll> ans(n, INF);
  vector<ll> col(n), d1(n);

  function<void(vector<int>)> solve2 = [&](vector<int> vct) {
    if (vct.size() <= 1) return;
#ifndef LOCAL
    if ((int)vct.size() <= K) {
        for (int i = 0; i < (int)vct.size(); i++) {
          for (int j = i + 1; j < (int)vct.size(); j++) {
            int u = vct[i];
            int v = vct[j];
            if (col[u] != col[v]) {
              ll d = d1[u] + d1[v] + t2.dist(u, v);
              ans[u] = min(ans[u], d);
              ans[v] = min(ans[v], d);
            }
          }
        }
        return;
      }
#endif

    auto o = t2.centr(vct);
//      dbv(vct);
//      db(o.centr);
//      dbv(o.v1);
//      dbv(o.v2);

    if (find(vct.begin(), vct.end(), o.centr) != vct.end()) {
      o.v2.push_back(o.centr);
    }

//    auto vv = o.v1;
//    vv.insert(vv.end(), o.v2.begin(), o.v2.end());
//    vector<ll> cd(vv.size());
//
//    vector<ll> mn(2);
//    for (int i = 0; i < (int)cd.size(); i++) {
//      cd[i] = t2.dist(o.centr, vv[i]);
//    }
    vector<ll> cd1(o.v1.size());
    vector<ll> cd2(o.v2.size());
    vector<ll> mn1(2, INF), mn2(2, INF);

    for (int i = 0; i < (int) o.v1.size(); i++) {
      cd1[i] = t2.dist(o.centr, o.v1[i]) + d1[o.v1[i]];
      mn1[col[o.v1[i]]] = min(mn1[col[o.v1[i]]], cd1[i]);
    }
    for (int i = 0; i < (int) o.v2.size(); i++) {
      cd2[i] = t2.dist(o.centr, o.v2[i]) + d1[o.v2[i]];
      mn2[col[o.v2[i]]] = min(mn2[col[o.v2[i]]], cd2[i]);
    }

    for (int i = 0; i < (int) o.v1.size(); i++) {
      int v = o.v1[i];
      ans[v] = min(ans[v], cd1[i] + mn2[col[v] ^ 1]);
    }
    for (int i = 0; i < (int) o.v2.size(); i++) {
      int v = o.v2[i];
      ans[v] = min(ans[v], cd2[i] + mn1[col[v] ^ 1]);
    }

    solve2(o.v1);
    solve2(o.v2);
  };

  function<void(vector<int>)> solve = [&](vector<int> vct) {
    if (vct.size() == 1) return;
#ifndef LOCAL
    if ((int)vct.size() <= K) {
      for (int i = 0; i < (int)vct.size(); i++) {
        for (int j = i + 1; j < (int)vct.size(); j++) {
          int u = vct[i];
          int v = vct[j];
          ll d = t1.dist(u, v) + t2.dist(u, v);
          ans[u] = min(ans[u], d);
          ans[v] = min(ans[v], d);
        }
      }
      return;
    }
#endif


    sort(vct.begin(), vct.end());
    auto o = t1.centr(vct);
    assert(binary_search(vct.begin(), vct.end(), o.centr));

    o.v2.push_back(o.centr);
    for (int v : o.v1) {
      col[v] = 0;
      d1[v] = t1.dist(o.centr, v);
    }
    for (int v : o.v2) {
      col[v] = 1;
      d1[v] = t1.dist(o.centr, v);
    }
    solve2(vct);
    solve(o.v2);

    if (vct.size() > 2) {
      o.v1.push_back(o.centr);
      solve(o.v1);
    }
  };
  vector<int> vct(n);
  iota(vct.begin(), vct.end(), 0);
  solve(vct);
  return ans;
}

vector<ll> slow(int n, tree t1, tree t2) {
  t1.init();
  t2.init();
  vector<ll> ans(n, INF);

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      ll d = t1.dist(i, j) + t2.dist(i, j);
      ans[i] = min(ans[i], d);
      ans[j] = min(ans[j], d);
    }
  }

  return ans;
}

mt19937 rnd;
tree gen(int n) {
  tree t1(n);
  for (int i = 1; i < n; i++) {
    int pr, w;

    pr = rnd() % i;
    w = rnd() % (int) 1e9 + 1;
    t1.add_edge(i, pr, w);
  }
  return t1;
}

void test() {
  int n = 2e5;
  auto t1 = gen(n);
  auto t2 = gen(n);
  print(solve(n, t1, t2));
  exit(0);
}

void stress() {
  for (int it = 116;; it++) {
    rnd = mt19937(it);
    db(it);

    int n = rnd() % 50 + 2;
    auto t1 = gen(n);
    auto t2 = gen(n);

    auto ans1 = solve(n, t1, t2);
    auto ans2 = slow(n, t1, t2);
    if (ans1 != ans2) {
      cout << "----------" << endl;
      print(ans1);
      cout << "instead of" << endl;
      print(ans2);
      cout << "----------" << endl;
      t1.print();
      t2.print();
      db(n);
      exit(0);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
//  freopen("k.out", "w", stdout);
#endif
//  stress();
//  test();

  int n;
  bool first = 1;
  while (scanf("%d", &n) == 1) {
    if (first) first = 0;
    else printf("\n");

    tree t1(n), t2(n);
    t1.read();
    t2.read();

    auto ans = solve(n, t1, t2);
    for (int i = 0; i < n; i++) printf("%lld\n", ans[i]);
  }

  return 0;
}
