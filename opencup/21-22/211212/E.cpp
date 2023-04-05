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

const int MOD = 1000000007;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

int sum(int a, int b) {
  add(a, b);
  return a;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

struct Lin {
  int a, b;
  int eval(int x, int y) const {
    return sum(mul(a, x), mul(b, y));
  }
};
void add(Lin& x, const Lin& y) {
  add(x.a, y.a);
  add(x.b, y.b);
}
Lin sum(Lin x, const Lin& y) {
  add(x, y);
  return x;
}

class SegmentTree {
public:
  struct value_t {
    Lin fun;
    int sum;
    int count;
  };
  struct update_t {
    int add;
    Lin add_a;
    Lin add_b;
  };

private:

  static constexpr value_t EMPTY_VALUE = {{0, 0}, 0, 0};
  static constexpr update_t EMPTY_UPDATE = {0, {0, 0}, {0, 0}};

  static inline value_t merge_values(const value_t &a, const value_t &b) {
    return {sum(a.fun, b.fun), sum(a.sum, b.sum), a.count + b.count};
  }

  void apply(int v, const update_t &u) {
    add(tree[v].fun.a, u.add_a.eval(tree[v].sum, tree[v].count));
    add(tree[v].fun.b, u.add_b.eval(tree[v].sum, tree[v].count));
    add(tree[v].sum, mul(u.add, tree[v].count));
    add(upd[v].add_a, u.add_a);
    add(upd[v].add_b, u.add_b);
    add(upd[v].add_a.b, mul(u.add_a.a, upd[v].add));
    add(upd[v].add_b.b, mul(u.add_b.a, upd[v].add));
    add(upd[v].add, u.add);
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
  explicit SegmentTree(int n) {
    lst = 2;
    while (lst < n) lst *= 2;
    tree = vector<value_t>((size_t) (2 * lst), EMPTY_VALUE);
    upd = vector<update_t>((size_t) (2 * lst), EMPTY_UPDATE);
    for (int i = lst; i < lst + n; i++) {
      tree[i].count = 1;
    }
    for (int i = lst - 1; i > 0; i--) {
      tree[i] = merge_values(tree[2 * i], tree[2 * i + 1]);
    }
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

  struct query {
    int time;
    int type;
    int l, r;
    int addOrQid;
  };

  int n, m, q;
  while (scanf("%d%d%d", &n, &m, &q) == 3) {
    vector<query> qs;
    SegmentTree tree(n);
    for (int i = 0; i < n; i++) {
      int x;
      scanf("%d", &x);
      if (x < 0) x += MOD;
      tree.update(i, i + 1, {x, {0, mul(x, x)}, {0, 0}});
    }
    for (int i = 0; i < m; i++) {
      int l, r, x;
      scanf("%d%d%d", &l, &r, &x);
      if (x < 0) x += MOD;
      qs.push_back({i + 1, 0, l - 1, r, x});
    }
    for (int i = 0; i < q; i++) {
      int l, r, x, y;
      scanf("%d%d%d%d", &l, &r, &x, &y);
      if (x != 0) {
        qs.push_back({x - 1, 1, l - 1, r, i});
      }
      qs.push_back({y, 2, l - 1, r, i});
    }
    sort(qs.begin(), qs.end(), [](const query &a, const query &b) {
      return std::tie(a.time, a.type) < std::tie(b.time, b.type);
    });
    vector<int> ans(q, 0);
    for (auto &query: qs) {
      if (query.type == 0) {
        int x = query.addOrQid;
        int daa = mul(2, x);
        int dab = mul(x, x);
        int dba = mul(daa, MOD - query.time);
        int dbb = mul(dab, MOD - query.time);
        tree.update(query.l, query.r,
                    {x,
                     {daa, dab},
                     {dba, dbb}});
      } else {
        int res = tree.get(query.l, query.r).fun.eval(query.time + 1, 1);
        if (query.type == 1) {
          res = MOD - res;
        }
        //eprintf("%d %d %d\n", query.type, query.addOrQid, res);
        add(ans[query.addOrQid], res);
      }
    }
    for (int x : ans) {
      printf("%d\n", x);
    }
  }
  return 0;
}
