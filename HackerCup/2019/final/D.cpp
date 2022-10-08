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


class SegmentTree {
  struct value_t {
    int minv;
    int cnt_minv;
  };
  typedef int update_t;

  static constexpr value_t EMPTY_VALUE{1'000'000'000, 0};
  static constexpr update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    if (a.minv == b.minv) {
      return {a.minv, a.cnt_minv + b.cnt_minv};
    }
    if (a.minv < b.minv) {
      return a;
    }
    return b;
  }

  void apply(int v, const update_t &u) {
    tree[v].minv += u;
    upd[v] += u;
  }

  vector<value_t> tree;
  vector<update_t> upd;
  int lst;

  void push(int v) {
    apply(2 * v, upd[v]);
    apply(2 * v + 1, upd[v]);
    upd[v] = EMPTY_UPDATE;
  }

  value_t get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return EMPTY_VALUE;
    }
    if (L <= l && r <= R) {
      return tree[v];
    }
    push(v);
    return merge_values(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
  }

  void update(int v, int l, int r, int L, int R, const update_t &u) {
    if (r <= L || R <= l) {
      return;
    }
    if (L <= l && r <= R) {
      apply(v, u);
      return;
    }
    push(v);
    update(2 * v, l, (l + r) / 2, L, R, u);
    update(2 * v + 1, (l + r) / 2, r, L, R, u);
    tree[v] = merge_values(tree[2 * v], tree[2 * v + 1]);
  }

public:

  void init(int n) {
    init(vector<value_t>(n, {0, 1}));
  }

  void init(vector<value_t> v) {
    int n = (int) v.size();
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) 2 * lst, EMPTY_VALUE);
    for (int i = 0; i < n; i++) {
      tree[lst + i] = v[i];
    }
    for (int i = lst - 1; i > 0; i--) {
      tree[i] = merge_values(tree[2 * i], tree[2 * i + 1]);
    }
    upd = vector<update_t>((size_t) 2 * lst, EMPTY_UPDATE);
  }

  value_t get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  int getAll(int v) {
    std::ignore = v;
//    eprintf("get %d %d\n", v, tree[1].minv == 0 ? tree[1].cnt_minv : 0);
    return tree[1].minv == 0 ? tree[1].cnt_minv : 0;
  }

  vector<vector<tuple<int, int, int>>> ops;

  void update(int l, int r, update_t u) {
//    eprintf("update %d %d %d\n", l, r, u);
    if (!ops.empty()) {
      ops.back().emplace_back(l, r, -u);
    }
    return update(1, 0, lst, l, r, u);
  }

  void init_rollback() {
    ops.emplace_back();
  }

  void rollback() {
//    eprintf("revert begin\n");
    auto rev = std::move(ops.back());
    for (auto [l, r, u] : rev) {
      update(l, r, u);
    }
    ops.pop_back();
//    eprintf("revert end\n");
  }
};


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

class Solver : public ParallelSolver {
  vector<vector<int>> tree;
  vector<pair<int, int>> bads;
  map<int, int> other_bad;
  vector<int> tin;
  vector<int> tout;
  vector<vector<int>> ctin;
  int timer = 0;
  long long ans;

  void dfs1(int v, int p) {
    if (p != -1) {
      tree[v].erase(find(tree[v].begin(), tree[v].end(), p));
    }
    tin[v] = timer++;
    for (int u : tree[v]) {
      ctin[v].push_back(timer);
      dfs1(u, v);
    }
    tout[v] = timer;
  }

  int get_pre(int u, int v) {
    int pre_id = upper_bound(ctin[u].begin(), ctin[u].end(), tin[v]) - ctin[u].begin();
    assert(pre_id);
    return tree[u][pre_id - 1];
  }

  void dfs2(int v,  SegmentTree &t) {
    t.init_rollback();
    int good_sub = -1;
    int good_rem = -1;
    if (other_bad.count(v)) {
      int u = other_bad[v];
      if (is_parent(v, u)) {
        good_sub = get_pre(v, u);
        good_rem = u;
      } else if (is_parent(u, v)) {
        t.update(tin[0], tout[0], +1);
        int pre = get_pre(u, v);
//        eprintf("pre[%d, %d] = %d\n", u, v, pre);
        t.update(tin[pre], tout[pre], -1);
      } else {
        t.update(tin[u], tout[u], +1);
      }
    }
    ans += t.getAll(v);
    for (int u : tree[v]) {
      if (u == good_sub) {
        t.update(tin[good_rem], tout[good_rem], -1);
      }
      dfs2(u, t);
      if (u == good_sub) {
        t.update(tin[good_rem], tout[good_rem], +1);
      }
    }
    t.rollback();
  }

  bool is_parent(int u, int v) {
    return tin[u] <= tin[v] && tout[v] <= tout[u];
  }

public:
  explicit Solver(int _testId) : ParallelSolver(_testId) {
    int n;
    scanf("%d", &n);
    tree.resize(n);
    map<string, int> s;

    for (int i = 0; i < n; i++) {
      static char buf[100];
      scanf("%s", buf);
      if (!strcmp(buf, "-")) continue;
      if (s.count(buf)) {
        bads.emplace_back(i, s[buf]);
      } else {
        s[buf] = i;
      }
    }
    for (int i = 1; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      --x, --y;
      tree[x].push_back(y);
      tree[y].push_back(x);
    }
  }

  void solve() override {
    tin.resize(tree.size());
    tout.resize(tree.size());
    ctin.resize(tree.size());
    dfs1(0, -1);
    SegmentTree t;
    t.init(tree.size());

    for (auto [u, v] : bads) {
      other_bad[u] = v;
      other_bad[v] = u;
      if (is_parent(v, u)) {
        t.update(tin[u], tout[u], 1);
      }
      if (is_parent(u, v)) {
        t.update(tin[v], tout[v], 1);
      }
    }

    dfs2(0, t);
    ans -= tree.size();

    printf("%lld\n", ans);
  }

};

int main() {
#ifdef LOCAL
//  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
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

#pragma omp parallel for
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
