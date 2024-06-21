#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct item { int min; int sum; };

class SegmentTree {
  typedef item value_t;
  typedef int update_t;

  static constexpr value_t EMPTY_VALUE = {std::numeric_limits<int>::max() / 2, 0};
  static constexpr update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    if (a.min == b.min) return {a.min, a.sum + b.sum};
    if (a.min < b.min) return a;
    return b;
  }

  void apply(int v, const update_t &u) {
    tree[v].min += u;
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
    return merge_values(get(2 * v, l, (l + r) / 2, L, R),
                        get(2 * v + 1, (l + r) / 2, r, L, R));
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
    while (lst < n)
      lst *= 2;
    tree = vector<value_t>((size_t)(2 * lst), EMPTY_VALUE);
    upd = vector<update_t>((size_t)(2 * lst), EMPTY_UPDATE);
  }

  void init(vector<value_t> v) {
    int n = (int)v.size();
    lst = 2;
    while (lst < n)
      lst *= 2;
    tree = vector<value_t>((size_t)2 * lst, EMPTY_VALUE);
    for (int i = 0; i < n; i++) {
      tree[lst + i] = v[i];
    }
    for (int i = lst - 1; i > 0; i--) {
      tree[i] = merge_values(tree[2 * i], tree[2 * i + 1]);
    }
    upd = vector<update_t>((size_t)2 * lst, EMPTY_UPDATE);
  }

  value_t get(int l, int r) { return get(1, 0, lst, l, r); }

  void update(int l, int r, update_t u) { return update(1, 0, lst, l, r, u); }
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  double sqrt2 = sqrt(2.0);

  int q, w;
  while (scanf("%d%d", &q, &w) == 2) {
    struct event {
      int l, r, ch;
    };
    std::set<pair<int, int>> s;
    vector<event> events;
    vector<int> cs;
    for (int i = 0; i < q; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      auto [it, ok] = s.insert({x, y});
      if (!ok) {
        s.erase(it);
      }
      events.push_back({max(0, x - y), min(w, x + y), ok ? 1 : -1});
      cs.push_back(events.back().l);
      cs.push_back(events.back().r);
    }
    sort(cs.begin(), cs.end());
    cs.erase(unique(cs.begin(), cs.end()), cs.end());
    for (auto &e : events) {
      e.l = lower_bound(cs.begin(), cs.end(), e.l) - cs.begin();
      e.r = lower_bound(cs.begin(), cs.end(), e.r) - cs.begin();
    }
    vector<item> items(cs.size() - 1);
    for (int i = 0; i < (int)items.size(); i++) {
      items[i] = item{0, cs[i+1] - cs[i]};
    }
    SegmentTree t;
    t.init(items);
    for (auto [l, r, ty]: events) {
      t.update(l, r, ty);
      auto x = t.get(0, cs.size());
      int ans = (cs.back() - cs[0]) - ((x.min == 0) ? x.sum : 0);
      printf("%.10lf\n", ans * sqrt2);
    }
  }

  return 0;
}
