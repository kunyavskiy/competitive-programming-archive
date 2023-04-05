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

const ll INF = 1e18;
/*
struct segtree {
  int n, N;
  vector<pair<ll, int>> t;

  segtree(int _n) {
    n = _n;
    N = 1;
    while (N < n) N <<= 1;
    t.resize(2 * N);
    for (int i = 0; i < n; i++) t[i] = make_pair(0, i);
    for (int i = N - 1; i >= 1; i--) t[i] = max(t[i * 2], t[i * 2 + 1]);
  }

  void add(int i, ll delta) {
    i += N;
    t[i].first += delta;
    while (i > 1) {
      i >>= 1;
      t[i] = max(t[i * 2], t[i * 2 + 1]);
    }
  }

  pair<ll, int> get(int l, int r) {
    l += N;
    r += N;
    pair<ll, int> res = make_pair(-INF, -1);
    while (l <= r) {
      if (l & 1) res = max(res, t[l]);
      if (!(r & 1)) res = max(res, t[r]);
      l = (l + 1) >> 1;
      r = (r - 1) >> 1;
    }
    return res;
  }

  pair<ll, int> get_except(int l, int r) {
    return max(get(0, l - 1), get(r + 1, n - 1));
  }

  void add(int l, int r, ll delta) {

  }

  void add_except(int l, int r, ll delta) {
    add(0, l - 1, delta);
    add(r + 1, n - 1, delta);
  }
};
*/

template<typename Util>
struct segtree_fast {
  int n, h;
  vector<typename Util::data> t;
  vector<typename Util::update> p;

  segtree_fast() = default;
  explicit segtree_fast(int _n, const typename Util::data &val) {
    n = _n;
    h = __builtin_clz(1) - __builtin_clz(n);
    p.assign(2 * n, Util::NEUTRAL_UPDATE);
    t.assign(2 * n, val);
  }
  explicit segtree_fast(vector<typename Util::data> a) {
    n = a.size();
    h = __builtin_clz(1) - __builtin_clz(n);
    p.assign(2 * n, Util::NEUTRAL_UPDATE);
    t.assign(2 * n, Util::NEUTRAL_DATA);
    copy(a.begin(), a.end(), t.begin() + n);
    for (int i = n - 1; i > 0; i--) {
      t[i] = Util::combine(t[i * 2], t[i * 2 + 1]);
    }
  }

  void update_vertex(int v, const typename Util::update &x) {
    Util::update_vertex(t[v], x);
    if (v < n) {
      p[v] = Util::merge_updates(p[v], x);
    }
  }

  void push_updates_to(int v) {
    for (int s = h; s > 0; s--) {
      int cur = v >> s;
      if (p[cur] != Util::NEUTRAL_UPDATE) {
        update_vertex(cur * 2, p[cur]);
        update_vertex(cur * 2 + 1, p[cur]);
        p[cur] = Util::NEUTRAL_UPDATE;
      }
    }
  }

  void recalc_path(int v) {
    while (v > 1) {
      v >>= 1;
      t[v] = Util::combine(t[v * 2], t[v * 2 + 1]);
      Util::update_vertex(t[v], p[v]);
    }
  }

  typename Util::data get(int l, int r) {
    if (l > r) return Util::NEUTRAL_DATA;
    l += n; r += n;
    push_updates_to(l);
    push_updates_to(r);

    auto res_left = Util::NEUTRAL_DATA;
    auto res_right = Util::NEUTRAL_DATA;
    while (l <= r) {
      if (l & 1) {
        res_left = Util::combine(res_left, t[l++]);
      }
      if (!(r & 1)) {
        res_right = Util::combine(t[r--], res_right);
      }
      l >>= 1;
      r >>= 1;
    }
    return Util::combine(res_left, res_right);
  }

  typename Util::data get_except(int l, int r) {
    return Util::combine(get(0, l - 1), get(r + 1, n - 1));
  }

  void upd(int ql, int qr, const typename Util::update &x) {
    if (ql > qr) return;
    ql += n; qr += n;
    int l = ql, r = qr;

    push_updates_to(l);
    push_updates_to(r);
    while (l <= r) {
      if (l & 1) {
        update_vertex(l++, x);
      }
      if (!(r & 1)) {
        update_vertex(r--, x);
      }
      l >>= 1;
      r >>= 1;
    }
    recalc_path(ql);
    recalc_path(qr);
  }

  void upd_except(int l, int r, const typename Util::update &x) {
    upd(0, l - 1, x);
    upd(r + 1, n - 1, x);
  }
};

template<typename Util>
struct segtree_rec {
  int n;
  vector<typename Util::data> a, t;
  vector<typename Util::update> p;

  explicit segtree_rec(int _n, const typename Util::data &val) {
    n = _n;
    int N = 1;
    while (N < n) N <<= 1;
    t.assign(2 * N, val);
    p.assign(2 * N, Util::NEUTRAL_UPDATE);
  }
  explicit segtree_rec(const vector<typename Util::data> &_a) {
    a = _a;
    n = a.size();
    int N = 1;
    while (N < n) N <<= 1;
    t.assign(2 * N, Util::NEUTRAL_DATA);
    p.assign(2 * N, Util::NEUTRAL_UPDATE);
    build(1, 0, n - 1);
  }

  void build(int v, int tl, int tr) {
    if (tl == tr) {
      t[v] = a[tl];
      return;
    }
    int tm = (tl + tr) >> 1;
    build(v * 2, tl, tm);
    build(v * 2 + 1, tm + 1, tr);
    t[v] = Util::combine(t[v * 2], t[v * 2 + 1]);
  }

  void update_vertex(int v, const typename Util::update &x) {
    Util::update_vertex(t[v], x);
    p[v] = Util::merge_updates(p[v], x);
  }

  void push(int v) {
    if (p[v] != Util::NEUTRAL_UPDATE) {
      update_vertex(v * 2, p[v]);
      update_vertex(v * 2 + 1, p[v]);
      p[v] = Util::NEUTRAL_UPDATE;
    }
  }

  typename Util::data get(int v, int tl, int tr, int l, int r) {
    if (l > r) return Util::NEUTRAL_DATA;
    if (l == tl && r == tr) return t[v];
    push(v);
    int tm = (tl + tr) >> 1;
    return Util::combine(get(v * 2, tl, tm, l, min(r, tm)), get(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r));
  }

  typename Util::data get(int l, int r) {
    return get(1, 0, n - 1, l, r);
  }

  void upd(int v, int tl, int tr, int l, int r, const typename Util::update &x) {
    if (l > r) return;
    if (l == tl && r == tr) {
      update_vertex(v, x);
      return;
    }
    push(v);
    int tm = (tl + tr) >> 1;
    upd(v * 2, tl, tm, l, min(r, tm), x);
    upd(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, x);
    t[v] = Util::combine(t[v * 2], t[v * 2 + 1]);
  }

  void upd(int l, int r, const typename Util::update &x) {
    upd(1, 0, n - 1, l, r, x);
  }
};

struct Data {
  using data = pair<ll, int>;
  using update = ll;

  static constexpr data NEUTRAL_DATA = {-INF, -1};
  static constexpr update NEUTRAL_UPDATE = 0;

  static data combine(const data &left, const data &right) {
    return max(left, right);
  }

  static void update_vertex(data &value, const update &upd) {
    value.first += upd;
  }

  static update merge_updates(const update &old, const update &nw) {
    return old + nw;
  }
};

using segtree = segtree_fast<Data>;

struct edge {
  int u, v, w;
};

ll solve(int n, int k, vector<edge> ed) {
  vector<vector<pair<int, int>>> e(n);
  for (auto o : ed) {
    e[o.u].push_back({o.v, o.w});
    e[o.v].push_back({o.u, o.w});
  }
  vector<char> alive(n, 1);
  vector<int> vis(n);
  int tmr = 0;

  vector<int> sz(n);
  function<void(int)> dfs1 = [&](int v) {
    vis[v] = tmr;
    sz[v] = 1;
    for (auto o : e[v]) {
      int to = o.first;
      if (vis[to] == tmr || !alive[to]) continue;
      dfs1(to);
      sz[v] += sz[to];
    }
  };

  function<void(int)> build = [&](int root) {
    tmr++;
    dfs1(root);
    int all = sz[root], pr = -1;
    while (1) {
      bool found = 0;
      for (auto o : e[root]) {
        int to = o.first;
        if (to == pr || !alive[to]) continue;
        if (sz[to] * 2 >= all) {
          found = 1;
          pr = root;
          root = to;
          break;
        }
      }
      if (!found) break;
    }
    sz[root] = all;
    alive[root] = 0;

    for (auto o : e[root]) {
      int to = o.first;
      if (!alive[to]) continue;
      build(to);
    }
  };
  build(0);
  vector<int> is_cand(n);
  int cnt_cands = 0;
  for (int v = 0; v < n; v++) {
    is_cand[v] = sz[v] >= (k + 1) / 2;
    cnt_cands += is_cand[v];
  }
  dbv(is_cand);
  dbv(sz);


  vector<int> in(n), out(n);
  int timer = 0;
  vector<pair<ll, int>> tmp(n);
  for (int i = 0; i < n; i++) tmp[i] = {0, i};
  segtree tr(tmp);

  function<void(int, int, ll)> dfs2 = [&](int v, int pr, ll dist) {
    in[v] = timer++;
    tr.upd(in[v], in[v], dist);
    for (auto o : e[v]) {
      int to = o.first;
      if (to == pr) continue;
      dfs2(to, v, dist + o.second);
    }
    out[v] = timer - 1;
  };

  struct Set {
    multiset<ll> val;
    ll add;

    Set() : add(0) {}
    void insert(ll x) {
      val.insert(x - add);
    }
    void resize(int sz) {
      while ((int)val.size() > sz) {
        val.erase(val.begin());
      }
    }
  };
  auto Merge = [&](Set *a, Set *b) {
    if (a->val.size() < b->val.size()) swap(a,b);
    for (auto x : b->val) {
      a->insert(x + b->add);
    }
    return a;
  };
  vector<Set> st(n);

  ll ans = -1;
  function<Set*(int, int)> dfs3 = [&](int v, int pr) {
    Set* res = &st[v];
    res->insert(0);

    vector<Set*> vct;
    for (auto o : e[v]) {
      int to = o.first;
      if (to == pr) continue;

      tr.upd(in[to], out[to], -o.second);
      tr.upd_except(in[to], out[to], o.second);
      auto nw = dfs3(to, v);
      tr.upd_except(in[to], out[to], -o.second);
      tr.upd(in[to], out[to], o.second);

      vct.push_back(nw);
    }

    if (is_cand[v]) {
      vector<ll> dist;
      dist.push_back(0);
      for (auto ch : vct) {
        int cur = 0;
        for (auto it : ch->val) {
          cur++;
          if (cur > k / 2) break;
          dist.push_back(it + ch->add);
        }
      }
      vector<int> up;
      for (int i = 0; i < k / 2; i++) {
        auto o = tr.get_except(in[v], out[v]);
        if (o.first < 0) break;
        up.push_back(o.second);
        dist.push_back(o.first);
        tr.upd(in[o.second], in[o.second], -INF);
      }
      assert((int)dist.size() >= k);
      nth_element(dist.begin(), dist.begin() + k - 1, dist.end());
      ll sum = 0;
      for (int i = 0; i < k; i++) sum += dist[i];
      ans = max(ans, sum * 2);
      for (auto x : up) tr.upd(in[x], in[x], +INF);
    }

    for (auto nw : vct) {
      res = Merge(res, nw);
    }
    return res;
  };
  dfs3(0, -1);

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("in", "r", stdin);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int n, k;
    scanf("%d%d", &n, &k);
    vector<edge> ed(n - 1);
    for (int i = 0; i < n - 1; i++) {
      scanf("%d%d%d", &ed[i].u, &ed[i].v, &ed[i].w);
      ed[i].u--;
      ed[i].v--;
    }
    cout << solve(n, k, ed) << endl;
  }

  return 0;
}
