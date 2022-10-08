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

typedef long long ll;
typedef long double ld;

class SegmentTree {
  typedef struct {
    int min_value;
    int min_count;
  } value_t;
  typedef int update_t;

  static constexpr value_t EMPTY_VALUE = {std::numeric_limits<int>::max(), 0};
  static constexpr update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
      if (a.min_value < b.min_value) return a;
      if (b.min_value < a.min_value) return b;
      return {a.min_value, a.min_count + b.min_count};
  }

  void apply(int v, const update_t &u) {
    tree[v].min_value += u;
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
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) 2 * lst, EMPTY_VALUE);
    for (int i = 0; i < n; i++) {
      tree[lst + i] = {0, 1};
    }
    for (int i = lst - 1; i > 0; i--) {
      tree[i] = merge_values(tree[2 * i], tree[2 * i + 1]);
    }
    upd = vector<update_t>((size_t) 2 * lst, EMPTY_UPDATE);
  }

  value_t get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  void update(int l, int r, update_t u) {
    if (l >= r) return;
    eprintf("[%d,%d)+=%d\n", l, r, u);
    return update(1, 0, lst, l, r, u);
  }
};


void PreCalc() {
}

void solve() {
  int n, c;
  scanf("%d%d", &n, &c);
  vector<int> a(c), b(c);
  for (int i = 0; i < c; i++) {
    scanf("%d%d", &a[i], &b[i]);
    if (a[i] == 0) a[i] = 1;
  }
  vector<int> v(2 * n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &v[i]);
    v[i]--;
    assert(0 <= v[i] && v[i] < c);
    v[i + n] = v[i];
  }
  SegmentTree t;
  t.init(2 * n);
  vector<vector<int>> poss(c);
  vector<int> id (2 * n);
  for (int i = 0; i < 2 * n; i++) {
    id[i] = poss[v[i]].size();
    poss[v[i]].push_back(i);
  }

  auto get = [&](int i, int id) {
    return id >= (int)poss[i].size() ? 2 * n : poss[i][id];
  };
  for (int i = 0; i < c; i++) {
    t.update(get(i, b[i]), 2 * n, 1);
    if (a[i]) t.update(get(i, 0), get(i, a[i] - 1), 1);
  }
  long long ans = 0;
  for (int i = 0; i < n; i++) {
    auto cur = t.get(i + 1, i + n - 1);
    if (cur.min_value == 0) {
      eprintf("i = %d, add = %d\n", i, cur.min_count);
      ans += cur.min_count;
    }
    int cc = v[i];
    int ccid = id[i];
    t.update(get(cc, ccid + b[cc]), get(cc, ccid + b[cc] + 1), -1);
    t.update(get(cc, ccid), get(cc, ccid + 1), -1);
    if (a[cc]) {
      t.update(get(cc, ccid + a[cc] - 1), get(cc, ccid + a[cc]), 1);
    }
  }
  printf("%lld\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
