#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <unistd.h>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;


class ParallelSolver {
  string output_buffer;
  static int solved;
public:
  static int testNum;
  int _testId;

  explicit ParallelSolver(int testId) : _testId(testId) {
    printf("Case #%d: ", testId);
  }

  __attribute__((format(printf, 2, 3)))
  void printf(const char *format, ...) {
    va_list ap;
    va_start (ap, format);
    char *output_part;
    vasprintf(&output_part, format, ap);
    output_buffer += output_part;
    free(output_part);
    va_end (ap);
  }

  virtual void solve() = 0;

  string run() {
    solve();
#pragma omp critical
    {
      solved++;
      if ((solved - 1) * 100 / testNum != solved * 100 / testNum || solved <= 20 || testNum - solved <= 20)
        TIMESTAMPf("%d%% of tests solved (%d/%d, %d more)", solved * 100 / testNum, solved, testNum, testNum - solved);
    }
    return std::move(output_buffer);
  }
};

int ParallelSolver::solved;
int ParallelSolver::testNum;

void PreCalc() {
}

struct dsu {
  vector<int> p;
  vector<int> id;
  explicit dsu(int n) : p(n), id(n) {
    for (int i = 0; i < n; i++) {
      p[i] = id[i] = i;
    }
  }

  int get(int a) {
    if (a == p[a]) return a;
    return p[a] = get(p[a]);
  }

  int join(int a, int b, int mid) {
    a = get(a);
    b = get(b);
    assert(a != b);
    p[a] = b;
    return id[b] = mid;
  }
};

const int LOG = 21;

struct MergeSortTree {
  vector<vector<int>> data;
  int lst;

  void build(const vector<int>& t, const vector<int>& tin) {
    lst = 2;
    while (lst < (int)t.size()) {
      lst *= 2;
    }
    data.resize(2 * lst);
    for (int i = 0; i < (int)tin.size(); i++) {
      if (t[i] >= 0) {
        data[lst + tin[i]].push_back(t[i]);
      }
    }
    for (int i = lst - 1; i > 0; i--) {
      merge(
        data[2 * i].begin(), data[2 * i].end(),
        data[2 * i + 1].begin(), data[2 * i + 1].end(),
        back_inserter(data[i])
        );
    }
  }

  int get(int v, int L, int R, int l, int r, int lt, int rt) {
    if (R <= l || R <= L) return 0;
    if (L <= l && r <= R) {
      return upper_bound(data[v].begin(), data[v].end(), rt) -
        lower_bound(data[v].begin(), data[v].end(), lt);
    }
    return get(2 * v, L, (L + R) / 2, l, r, lt, rt) +
           get(2 * v + 1, (L + R) / 2, R, l, r, lt, rt);
  }

  int get(int l, int r, int lt, int rt) {
    return get(1, 0, lst, l, r, lt, rt);
  }

};

struct tree {
  vector<int> lf;
  vector<int> rg;
  vector<int> extra_lf;
  vector<int> extra_rg;
  vector<int> tm;
  vector<int> enter_tm;
  vector<int> exit_tm;
  int timer = 0;
  vector<int> tin, tout;
  vector<vector<int>> up;
  vector<int> for_free;
  vector<int> best;
  vector<int> two_best;
  vector<int> from_root;
  MergeSortTree mst;

  void dfs(int v) {
    tin[v] = timer++;
    if (lf[v] != -1) {
      up[lf[v]][0] = up[rg[v]][0] = v;
      dfs(lf[v]);
      dfs(rg[v]);
    }
    tout[v] = timer;
  }

  explicit tree(int n): lf(n, -1), rg(n, -1), tm(n, 1e9) {}
  int add(int l, int r, int t) {
    lf.push_back(l);
    rg.push_back(r);
    tm.push_back(t);
    assert(t <= tm[l] && t < tm[r]);
    return lf.size() - 1;
  }

  void calc_for_free(int v, set<int>& s) {
    if (lf[v] == -1) {
      s.insert(enter_tm[v]);
      return;
    }
    set<int> my_lf, my_rg;
    calc_for_free(lf[v], my_lf);
    calc_for_free(rg[v], my_rg);
    auto cut = [&](set<int> &m, int &a) {
      while (!m.empty() && *m.rbegin() > tm[v]) {
        m.erase(--m.end());
        a++;
      }
    };
    auto merge = [&](set<int> &a, set<int> &b) {
      if (a.size() < b.size()) {
        a.swap(b);
      }
      for (int x : b) {
        a.insert(x);
      }
      b.clear();
    };
    cut(my_lf, extra_lf[v]);
    cut(my_rg, extra_rg[v]);
    merge(my_lf, my_rg);
    for_free[v] = my_lf.size();
    merge(s, my_lf);
    best[v] = max(extra_lf[v] + best[lf[v]], extra_rg[v] + best[rg[v]]);
    two_best[v] = max(
      max(extra_lf[v] + two_best[lf[v]], extra_rg[v] + two_best[rg[v]]),
      extra_lf[v] + extra_rg[v] + best[lf[v]] + best[rg[v]]
    );
  }

  void calc_from_root(int v, int cur) {
    from_root[v] = cur;
    if (lf[v] != -1) {
      calc_from_root(lf[v], cur + extra_lf[v]);
      calc_from_root(rg[v], cur + extra_rg[v]);
    }
  }

  int path_length(int u, int v) {
    assert(tin[u] <= tin[v] && tout[v] <= tout[u]);
    return from_root[v] - from_root[u];
  }

  int get_up_time(int v, int t) {
    for (int i = LOG - 1; i >= 0; i--) {
      if (tm[up[v][i]] >= t) {
        v = up[v][i];
      }
    }
    return v;
  }

  void precalc() {
    exit_tm.resize(lf.size(), -25);
    int n = lf.size();
    tin.resize(n);
    tout.resize(n);
    up.resize(n, vector<int>(LOG));
    int root = n - 1;
    up[root][0] = root;
    dfs(root);
    for (int i = 1; i < LOG; i++) {
      for (int j = 0; j < n; j++) {
        up[j][i] = up[up[j][i - 1]][i - 1];
      }
    }
    set<int> temp;
    extra_lf.resize(lf.size());
    extra_rg.resize(lf.size());
    best.resize(lf.size());
    two_best.resize(lf.size());
    for_free.resize(lf.size());
    calc_for_free(root, temp);
    from_root.resize(lf.size());
    calc_from_root(root, 0);
    mst.build(exit_tm, tin);
  }

  int exit_before(int v, int tm) {
    return mst.get(tin[v], tout[v], -25, tm + 1);
  }
  int get_between(int up1, int up2) {
    return mst.get(tin[up1], tout[up1], tm[up2] + 1, tm[up1] + 1);
  }
};


class Solver : public ParallelSolver {
  int n, m;
  vector<int> st;
  vector<int> en;
  vector<int> x, y;
  vector<int> colapse;
  vector<int> qx, qy;

public:
  explicit Solver(int _testId) : ParallelSolver(_testId) {
    int k, s;
    scanf("%d%d%d%d", &n, &m, &k, &s);
    st.resize(n, -25);
    en.resize(n, -25);
    x.resize(m);
    y.resize(m);
    colapse.resize(m, -1);
    qx.resize(s);
    qy.resize(s);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &x[i], &y[i]);
      --x[i], --y[i];
    }
    for (int i = 0; i < k; i++) {
      int e, v;
      scanf("%d%d", &e, &v);
      if (e == 1) {
        colapse[v - 1] = i;
      } else if (e == 2) {
        st[v - 1] = i;
      } else {
        en[v - 1] = i;
      }
    }
    for (int i = 0; i < s; i++) {
      scanf("%d%d", &qx[i], &qy[i]);
    }
    int tt = m;
    for (int i = 0; i < m; i++) {
      if (colapse[i] == -1) {
        colapse[i] = tt++;
      }
    }
  }

  void solve() override {
    dsu d(n);
    vector<int> order(m);
    for (int i = 0; i < m; i++) {
      order[i] = i;
    }
    sort(order.begin(), order.end(), [&](int a, int b) { return colapse[a] > colapse[b];});
    tree t(n);
    for (int i = 0; i < m; i++) {
      int u = d.get(x[order[i]]);
      int v = d.get(y[order[i]]);
      if (u == v) continue;
      d.join(u, v, t.add(d.id[u], d.id[v], colapse[order[i]]));
    }
    t.enter_tm = st;
    t.exit_tm = en;

    t.precalc();
    int ans = 0;
    int total_ans = 0;

    for (int i = 0; i < (int)qx.size(); i++) {
      qx[i] ^= ans;
      qy[i] ^= ans;
      assert(1 <= qx[i] && qx[i] <= n);
      ans = 0;

      int up1 = t.get_up_time(qx[i] - 1, qy[i]);
      int up2 = t.get_up_time(qx[i] - 1, qy[i] - 24);

      if (t.best[up2] != t.best[up1] + t.path_length(up2, up1)) {
        ans = t.for_free[up2] + t.best[up2] + t.best[up1];
      } else {
        ans = t.path_length(up2, up1) + t.two_best[up1];
        if (t.two_best[up2] != t.two_best[up1] + t.path_length(up2, up1)) {
          ans = max(ans, (t.two_best[up2] - t.best[up2]) + t.best[up1]);
        }
        ans += t.for_free[up2] + t.get_between(up1, up2);
      }

      eprintf("ans = %d\n", ans);
      ans -= t.exit_before(up2, qy[i] - 24);
      total_ans += ans;
      eprintf("%d %d %d\n", qx[i], qy[i], ans);
    }
    printf("%d\n", total_ans);

  }

};

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &ParallelSolver::testNum);

  vector<std::unique_ptr<Solver>> solvers(ParallelSolver::testNum);

  for (int i = 0; i < ParallelSolver::testNum; i++) {
    solvers[i] = make_unique<Solver>(i + 1);
  }

  vector<std::string> results(ParallelSolver::testNum);

//#pragma omp parallel for
  for (int i = 0; i < ParallelSolver::testNum; i++) {
    results[i] = solvers[i]->run();
    solvers[i] = nullptr;
  }

  for (const auto &result : results) {
    printf("%s", result.c_str());
  }

  TIMESTAMP(end);
  return 0;
}
