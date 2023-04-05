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

struct item {
  int val;
  int cnt;

  item() : val(0), cnt(0) {}
  item(int x) : val(x), cnt(1) {}
};

item combine(item a, item b) {
  if (a.cnt < b.cnt) swap(a, b);
  if (a.val == b.val) a.cnt += b.cnt;
  else a.cnt -= b.cnt;
  return a;
}

struct segtree {
  int n, N;
  vector<item> t;

  segtree() {}
  segtree(vector<int> c) {
    n = c.size();
    N = 1;
    while (N < n) N <<= 1;

    t.resize(2 * N);
    for (int i = 0; i < n; i++) t[N + i] = item(c[i]);
    for (int i = N - 1; i >= 1; i--) t[i] = combine(t[i * 2], t[i * 2 + 1]);
  }

  item get(int l, int r) {
    l += N;
    r += N;
    item res;
    while (l <= r) {
      if (l & 1) res = combine(res, t[l]);
      if (!(r & 1)) res = combine(res, t[r]);
      l = (l + 1) >> 1;
      r = (r - 1) >> 1;
    }
    return res;
  }
};

namespace hld {
  const int N = 1 << 18;
  int par[N], heavy[N], h[N];
  int root[N], pos[N];
  int n;
  vector<vector<int> > e;
  segtree tree;

  int dfs(int v) {
    int sz = 1, mx = 0;
    for (int to : e[v]) {
      if (to == par[v]) continue;
      par[to] = v;
      h[to] = h[v] + 1;
      int cur = dfs(to);
      if (cur > mx) heavy[v] = to, mx = cur;
      sz += cur;
    }
    return sz;
  }

  template <typename T>
  int path(int u, int v, T op) {
    for (; root[u] != root[v]; v = par[root[v]]) {
      if (h[root[u]] > h[root[v]]) swap(u, v);
      op(pos[root[v]], pos[v]);
    }
    if (h[u] > h[v]) swap(u, v);
    op(pos[u], pos[v]);
    return u;
  }

  void init(vector<vector<int> > _e, vector<int> cc) {
    e = _e;
    n = e.size();
    memset(heavy, -1, sizeof(heavy[0]) * n);
    par[0] = -1;
    h[0] = 0;
    dfs(0);
    for (int i = 0, cpos = 0; i < n; i++) {
      if (par[i] == -1 || heavy[par[i]] != i) {
        for (int j = i; j != -1; j = heavy[j]) {
          root[j] = i;
          pos[j] = cpos++;
        }
      }
    }
    vector<int> colors(n);
    for (int i = 0; i < n; i++) colors[pos[i]] = cc[i];
    tree = segtree(colors);
  }

  item get(int u, int v, int &lca) {
    item res;
    lca = path(u, v, [&](int l, int r) {
      res = combine(res, tree.get(l, r));
    });
    return res;
  }
}


int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
//  freopen("f.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &c[i]);
      c[i]--;
    }

    vector<vector<int>> e(n);
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      e[u].push_back(v);
      e[v].push_back(u);
    }
    hld::init(e, c);

    vector<int> cnt(q);
    vector<int> len(q);
    vector<int> res(q);
    vector<vector<pair<int, int>>> vct(n);

    for (int i = 0; i < q; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      int w;

      auto cand = hld::get(u, v, w);
//      cerr << cand.val << " " << cand.cnt << endl;

      vct[u].push_back({cand.val, i});
      vct[v].push_back({cand.val, i});

      if (w != 0) {
        vct[hld::par[w]].push_back({cand.val, ~i});
      }
      len[i]--;
      cnt[i] -= c[w] == cand.val;

      res[i] = cand.val + 1;
    }

    vector<int> cur_cnt(n);
    function<void(int, int, int)> dfs = [&](int v, int pr, int ch) {
      cur_cnt[c[v]]++;
      for (auto o : vct[v]) {
        int id = o.second;
        int coef = 1;
        if (id < 0) {
          id = ~id;
          coef = -2;
        }
        int col = o.first;
        len[id] += coef * ch;
        cnt[id] += coef * cur_cnt[col];
      }
      for (int to : e[v]) {
        if (to == pr) continue;
        dfs(to, v, ch + 1);
      }
      cur_cnt[c[v]]--;
    };
    dfs(0, -1, 1);

    for (int i = 0; i < q; i++) {
//      cerr << cnt[i] << " " << len[i] << endl;
      if (cnt[i] * 2 <= len[i]) res[i] = -1;
      printf("%d\n", res[i]);
    }
  }

  return 0;
}
