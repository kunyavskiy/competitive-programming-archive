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

typedef __int128 ll;
typedef long double ld;


const ll INF = (1LL << 61) * (ll)(1LL << 62);
const ll is_query = -INF;

struct Line {
  ll m, b;
  mutable function<const Line *()> succ;

  bool operator<(const Line &rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line *s = succ();
    if (!s) return 0;
    ll x = rhs.m;
    return b - s->b < (s->m - m) * x;
  }
};

struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if (z == end()) return y->m == x->m && y->b <= x->b;
    return (x->b - y->b) * (z->m - y->m) >= (y->b - z->b) * (y->m - x->m);
  }

  void insert_line(ll m, ll b) {
    auto y = insert({m, b});
    y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
    if (bad(y)) {
      erase(y);
      return;
    }
    while (next(y) != end() && bad(next(y))) erase(next(y));
    while (y != begin() && bad(prev(y))) erase(prev(y));
  }

  ll eval(ll x) {
    if (empty()) return -INF;
//    cerr << x << endl;
    auto l = *lower_bound((Line) {x, is_query});
    return l.m * x + l.b;
  }
};

struct segtree {
  int n, N;
  vector<HullDynamic> t;

  segtree(int _n) {
    n = _n;
    N = 1;
    while (N < n) N <<= 1;

    t.resize(2 * N);
  }

  void add(int l, int r, ll m, ll b) {
    l += N;
    r += N;
    while (l <= r) {
      if (l & 1) t[l].insert_line(m, b);
      if (!(r & 1)) t[r].insert_line(m, b);
      l = (l + 1) >> 1;
      r = (r - 1) >> 1;
    }
  }

  ll get(int v, ll x) {
    ll res = -INF;
    v += N;
    while (v >= 1) {
      res = max(res, t[v].eval(x));
      v >>= 1;
    }
    return res;
  }
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
//  freopen("h.out", "w", stdout);
#endif


  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    for (int i = 0; i < n; i++) scanf("%d", &b[i]);
    for (int i = 0; i < n; i++) scanf("%d", &c[i]);

    vector<vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }

    vector<pair<int, int>> qr(q);
    for (int i = 0; i < q; i++) {
      scanf("%d%d", &qr[i].first, &qr[i].second);
      qr[i].first--;
    }
    vector<int> qid(q);
    iota(qid.begin(), qid.end(), 0);
    sort(qid.begin(), qid.end(), [&](int x, int y) {
      return qr[x].second > qr[y].second;
    });

    vector<int> in(n), out(n);
    int tmr = 0;
    function<void(int, int)> dfs = [&](int v, int pr) {
      in[v] = tmr++;
      for (int to : e[v]) {
        if (to == pr) continue;
        dfs(to, v);
      }
      out[v] = tmr - 1;
    };
    dfs(0, 0);


    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 0);
    sort(perm.begin(), perm.end(), [&](int x, int y) {
      return c[x] > c[y];
    });

    vector<ll> ans(q);
    int j = 0;

    segtree tr(n);
    for (int i = 0; i < n; i++) {
      int v = perm[i];
      tr.add(in[v], out[v], -b[v], -a[v]);

      while (j < q && (i == n - 1 || qr[qid[j]].second > c[perm[i + 1]])) {
        ans[qid[j]] = -tr.get(in[qr[qid[j]].first], qr[qid[j]].second);
        j++;
      }
    }

    for (int i = 0; i < q; i++) printf("%lld\n", (long long)ans[i]);
  }

  return 0;
}
