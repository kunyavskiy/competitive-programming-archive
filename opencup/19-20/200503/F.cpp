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

struct dsu {
  vector<int> p;
  vector<int> data;
  explicit dsu(int n) : p(n), data(n) {
    for (int i = 0; i < n; i++) {
      p[i] = data[i] = i;
    }
  }

  int get(int v) {
    assert(0 <= v && v < (int)p.size());
    if (p[v] == v) return v;
    return p[v] = get(p[v]);
  }

  bool join(int a, int b) {
    a = get(a);
    b = get(b);
    if (a == b) return false;
    p[a] = b;
    return true;
  }
};

struct edge {
  int a, b, w;
};

struct query {
  int x;
  int ly, ry;
  int *to;
  int coef;
};

void solve() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  vector<edge> es(m);
  vector<int> ws;
  for (auto &e : es) {
    scanf("%d%d%d", &e.a, &e.b, &e.w);
    --e.a, --e.b;
    ws.push_back(e.w);
  }
  ws.push_back(0);
  sort(ws.begin(), ws.end());
  ws.erase(unique(ws.begin(), ws.end()), ws.end());
  sort(es.begin(), es.end(), [](const edge &a, const edge &b) { return a.w < b.w; });


  vector<pair<int, int>> tree(2 * n - 1);
  vector<int> cost(2 * n - 1);
  vector<bool> is_root(2 * n - 1);

  for (int i = 0; i < n; i++) {
    is_root[i] = true;
  }

  int pt = n;
  dsu d(n);

  vector<edge> other;

  for (auto &e : es) {
    int oa = d.data[d.get(e.a)];
    int ob = d.data[d.get(e.b)];
    assert(is_root[oa] && is_root[ob]);
    if (d.join(e.a, e.b)) {
      assert(oa != ob);
      tree[pt] = {oa, ob};
      cost[pt] = e.w;
      is_root[pt] = true;
      is_root[oa] = is_root[ob] = false;
      d.data[d.get(e.a)] = pt++;
    } else {
      other.push_back(e);
    }
  }

  tree.resize(pt);
  cost.resize(pt);
  is_root.resize(pt);

  vector<int> tin(tree.size()), tout(tree.size());
  int timer = 0;
  vector<vector<int>> up(17, vector<int>(tree.size()));

  auto dfs = [&](const auto &self, int v) -> void {
    if (v < n) {
      tin[v] = timer;
      tout[v] = ++timer;
    } else {
      self(self, tree[v].first);
      self(self, tree[v].second);
      up[0][tree[v].first] = up[0][tree[v].second] = v;
      tin[v] = tin[tree[v].first];
      tout[v] = tout[tree[v].second];
    }
  };
  for (int i = 0; i < (int) is_root.size(); i++) {
    if (is_root[i]) {
      up[0][i] = i;
      dfs(dfs, i);
    }
  }

  for (int i = 1; i < (int) up.size(); i++) {
    for (int j = 0; j < (int) up[i].size(); j++) {
      up[i][j] = up[i - 1][up[i - 1][j]];
    }
  }

  vector<query> qs;
  for (const edge &e : other) {
    qs.push_back({tin[e.a], tin[e.b], tin[e.b], nullptr, 0});
    qs.push_back({tin[e.b], tin[e.a], tin[e.a], nullptr, 0});
  }

  vector<int> a(q);
  vector<int> b(q);
  vector<int> lf(q);
  vector<int> rg(q);

  for (int i = 0; i < q; i++) {
    scanf("%d%d", &a[i], &b[i]);
    --a[i], --b[i];
    lf[i] = -1;
    rg[i] = ws.size();
  }

  auto get_up = [&](int v, int lim) {
    for (int i = up.size() - 1; i >= 0; i--) {
      if (cost[up[i][v]] <= lim) {
        v = up[i][v];
      }
    }
    return v;
  };

  while (true) {
    TIMESTAMP("iter");
    vector<query> pq = qs;
    vector<int> count(q);
    bool any = false;
    for (int i = 0; i < q; i++) {
      any |= rg[i] - lf[i] > 1;
      int m = ws[(lf[i] + rg[i]) / 2];
      int aa = get_up(a[i], m);
      int bb = get_up(b[i], m);
      if (up[0][aa] == up[0][bb]) {
        count[i] = 1;
      } else {
        pq.push_back({tin[aa], tin[bb], tout[bb], &count[i], -1});
        pq.push_back({tout[aa], tin[bb], tout[bb], &count[i], +1});
      }
    }
    if (!any) break;
    sort(pq.begin(), pq.end(), [](const query &a, const query &b) {
      if (a.x != b.x) {
        return a.x < b.x;
      }
      return a.to != nullptr && b.to == nullptr;
    });

    vector<int> f(n);

    auto add = [&](int pos, int val) {
      while (pos < (int)f.size()) {
        f[pos] += val;
        pos = pos | (pos + 1);
      }
    };
    auto get = [&](int pos) {
      int ans = 0;
      while (pos >= 0) {
        ans += f[pos];
        pos = (pos & (pos + 1)) - 1;
      }
      return ans;
    };

    for (const auto &q : pq) {
      if (q.to == nullptr) {
        add(q.ly, 1);
      } else {
        *q.to += q.coef * (get(q.ry - 1) - get(q.ly - 1));
      }
    }

    for (int i = 0; i < q; i++) {
      if (count[i] == 0) {
        lf[i] = (lf[i] + rg[i]) / 2;
      } else {
        rg[i] = (lf[i] + rg[i]) / 2;
      }
    }
  }

  for (int i = 0; i < q; i++) {
    if (rg[i] == (int)ws.size()) {
      printf("-1\n");
    } else {
      printf("%d\n", ws[rg[i]]);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    TIMESTAMPf("%d", t);
    solve();
  }

  return 0;
}
