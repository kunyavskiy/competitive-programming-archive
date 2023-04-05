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
  typedef ll value_t;
  typedef ll update_t;

  static constexpr value_t EMPTY_VALUE = 0;
  static constexpr update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return min(a, b);
  }

  void apply(int v, const update_t &u) {
    tree[v] += u;
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
    tree = vector<value_t>((size_t)(2 * lst), EMPTY_VALUE);
    upd = vector<update_t>((size_t)(2 * lst), EMPTY_UPDATE);
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
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    vector<int> sa = a;
    sort(sa.begin(), sa.end(), greater<>());
    vector<int> cb(n);
    for (int i = 0; i < m; i++) {
      scanf("%d", &b[i]);
      if (b[i]) {
        cb[min(b[i], n) - 1]++;
      }
    }
    for (int i = n - 2; i >= 0; i--) {
      cb[i] += cb[i + 1];
    }

    SegmentTree tree;
    tree.init(n);

    for (int i = 0; i < n; i++) {
      tree.update(i, n, cb[i]);
      tree.update(i, n, -sa[i]);
    }


    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
      int ty, pos;
      scanf("%d%d", &ty, &pos);
      --pos;

      if (ty == 1) {
        auto id = lower_bound(sa.begin(), sa.end(), a[pos], greater<>()) - sa.begin();
        sa[id] += 1;
        tree.update(id, n, -1);
        a[pos] += 1;
      } else if (ty == 2) {
        auto id = upper_bound(sa.begin(), sa.end(), a[pos], greater<>()) - sa.begin() - 1;
        sa[id] -= 1;
        tree.update(id, n, 1);
        a[pos] -= 1;
      } else if (ty == 3) {
        b[pos] += 1;
        if (b[pos] <= n) {
          cb[b[pos] - 1] += 1;
          tree.update(b[pos] - 1, n, 1);
        }
      } else if (ty == 4) {
        if (b[pos] <= n) {
          cb[b[pos] - 1] -= 1;
          tree.update(b[pos] - 1, n, -1);
        }
        b[pos] -= 1;
      }
      printf("%d\n", tree.get(0, n) < 0 ? 0 : 1);
    }
  }


  return 0;
}
