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

class SegmentTree {
  struct value_t {
    int min;
    int min_pos;
    int max;
  };
  typedef int update_t;

  static constexpr value_t EMPTY_VALUE{numeric_limits<int>::max(), -1, numeric_limits<int>::min()};
  static const update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    value_t res;
    res.max = max(a.max, b.max);
    pair<int, int> m = min<pair<int, int>>({a.min, a.min_pos}, {b.min, b.min_pos});
    res.min = m.first;
    res.min_pos = m.second;
    return res;
  }

  void apply(int v, const update_t &u) {
    tree[v].min += u;
    tree[v].max += u;
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
  void init(vector<int> v) {
    int n = (int) v.size();
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) 2 * lst, EMPTY_VALUE);
    for (int i = 0; i < n; i++) {
      tree[lst + i] = {v[i], i, v[i]};
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
    return update(1, 0, lst, l, r, u);
  }
};


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    vector<int> bals;
    bals.push_back(0);
    int cur = 0;
    for (char c : s) {
      if (c == '1') {
        cur++;
      } else {
        cur--;
      }
      bals.push_back(cur);
    }
    set<int> qs;
    for (int i = 0; i < (int)s.size(); i++) {
      if (s[i] == '?') {
        qs.insert(i);
      }
    }

    SegmentTree tree;
    tree.init(bals);
    int ans = numeric_limits<int>::max();

    while (true) {
      auto res = tree.get(0, bals.size());
      ans = min(ans, res.max - res.min);
      auto it = qs.lower_bound(res.min_pos);
      if (it == qs.begin()) {
        break;
      }
      --it;
      s[*it] = '1';
      eprintf("%d %d %d: %s\n", res.min, res.max, res.min_pos, s.c_str());
      tree.update(*it, bals.size(), 2);
    }
    printf("%d\n", ans);
    break;
  }

  return 0;
}
