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

constexpr ll INF = 1LL << 60;

struct item {
  ll mins[6]{INF, INF, INF, INF, INF, INF};
  int count{};
};

struct change {
  ll add[6]{0,0,0,0,0,0};
};


item merge(item a, item b) {
  item res{};
  res.count = a.count + b.count;
  int shift = (6 - a.count % 6) % 6;
  for (int i = 0; i < 6; i++) {
    res.mins[i] = min(a.mins[i], b.mins[(i + shift) % 6]);
  }
  return res;
}

struct tree {
  vector<item> vals;
  vector<change> changes;
  int lst;

  explicit tree(int n) {
    lst = 1;
    while (lst < n) lst *= 2;
    vals.resize(2 * lst);
    changes.resize(2 * lst);
  }

  void apply(const change& c, int v) {
    for (int i = 0; i < 6; i++) {
      vals[v].mins[i] += c.add[i];
      changes[v].add[i] += c.add[i];
    }
  }

  void push(int v) {
    apply(changes[v], 2 * v);
    rotate(changes[v].add, changes[v].add + vals[2 * v].count % 6, changes[v].add + 6);
    apply(changes[v], 2 * v + 1);
    changes[v] = {};
  }

  item get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) return {};
    if (L <= l && r <= R) return vals[v];
    push(v);
    return merge(
      get(2 * v, l, (l + r) / 2, L, R),
      get(2 * v + 1, (l + r) / 2, r, L, R)
      );
  }

  item get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  void set_count(int v, int l, int r, int L, int R, int c) {
    if (r <= L || R <= l) return;
    if (L <= l && r <= R) {
      assert(r - l == 1);
      vals[v].count = c;
      fill(vals[v].mins, vals[v].mins + 6, INF);
      if (c == 1) {
        vals[v].mins[0] = 0;
      }
      return;
    }
    push(v);
    set_count(2 * v, l, (l + r) / 2, L, R, c);
    set_count(2 * v + 1, (l + r) / 2, r, L, R, c);
    vals[v] = merge(vals[2 * v], vals[2 * v + 1]);
  }


  void set_count(int pos, int c) {
    return set_count(1, 0, lst, pos, pos + 1, c);
  }

  int add(int v, int l, int r, int L, int R, change c) {
    if (r <= L || R <= l) return 0;
    if (L <= l && r <= R) {
      apply(c, v);
      return vals[v].count % 6;
    }
    push(v);
    int x = add(2 * v, l, (l + r) / 2, L, R, c);
    rotate(c.add, c.add + x, c.add + 6);
    x += add(2 * v + 1, (l + r) / 2, r, L, R, c);
    vals[v] = merge(vals[2 * v], vals[2 * v + 1]);
    return x % 6;
  }

  void add(int l, int r, const change &c) {
    add(1, 0, lst, l, r, c);
  }

  int get_kth(int k) {
    int v = 1;
    while (v < lst) {
      push(v);
      if (vals[2 * v].count <= k) {
        k -= vals[2 * v].count;
        v = 2 * v + 1;
      } else {
        v = 2 * v;
      }
    }
    return v - lst;
  }

};

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, q;
  while (scanf("%d%d", &n, &q) == 2) {
    tree t(n);
    for (int i = 0; i < n; i++) {
      t.set_count(i, 1);
    }
    for (int i = 0; i < q; i++) {
      char s[20];
      scanf("%s", s);
      if (!strcmp(s, "change")) {
        int l, r, k, x;
        scanf("%d%d%d%d", &l, &r, &k, &x);
        --l;
        l = t.get_kth(l);
        r = t.get_kth(r - 1) + 1;
        t.add(l, r, k == 2 ? change{{x, 0, x, 0, x, 0}} : change{{x, 0, 0, x, 0, 0}});
      } else if (!strcmp(s, "getmin")) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        --l;
        l = t.get_kth(l);
        r = t.get_kth(r - 1) + 1;
        item res = t.get(l, r);
        ll ans;
        if (k == 2) {
          ans = min({res.mins[0], res.mins[2], res.mins[4]});
        } else {
          ans = min(res.mins[0], res.mins[3]);
        }
        printf("%lld\n", ans);
      } else if (!strcmp(s, "kill")) {
        int l;
        scanf("%d", &l);
        l = t.get_kth(l - 1);
        t.set_count(l, 0);
      } else if (!strcmp(s, "revive")) {
        int l;
        scanf("%d", &l);
        t.set_count(l - 1, 1);
      }
    }
  }

  return 0;
}
