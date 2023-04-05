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

class SegmentTree {
  typedef ll value_t;
  typedef ll update_t;

  static constexpr value_t EMPTY_VALUE = std::numeric_limits<value_t>::min();
  static constexpr update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return max(a, b);
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

  void update(int l, int r, update_t u) {
    return update(1, 0, lst, l, r, u);
  }
};

class SegmentTreeSum {
  typedef ll value_t;
  typedef ll update_t;

  static constexpr value_t EMPTY_VALUE = 0;
  static constexpr update_t EMPTY_UPDATE = 0;

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return a + b;
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

  void update(int l, int r, update_t u) {
    return update(1, 0, lst, l, r, u);
  }
};


int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    SegmentTree t;
    SegmentTreeSum t2;
    t.init(vector<ll>(n + 1));
    t2.init(vector<ll>(n + 1));
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      t.update(i + 1, i + 2, a[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &b[i]);
      t.update(i + 1, n + 1, -b[i]);
      t2.update(i + 1, i + 2, b[i]);
    }
    for (int i = 0; i < q; i++) {
      int ty;
      scanf("%d", &ty);
      if (ty == 1) {
        int x, y;
        scanf("%d%d", &x, &y);
        t.update(x, x + 1, y - a[x - 1]);
        a[x - 1] = y;
      } else if (ty == 2) {
        int x, y;
        scanf("%d%d", &x, &y);
        t.update(x, n + 1, -(y - b[x - 1]));
        t2.update(x, x + 1, y - b[x - 1]);
        b[x - 1] = y;
      } else if (ty == 3) {
        int x;
        scanf("%d", &x);
        printf("%lld\n", t.get(0, x + 1) + t2.get(0, x + 1));
      }
    }
  }


  return 0;
}
