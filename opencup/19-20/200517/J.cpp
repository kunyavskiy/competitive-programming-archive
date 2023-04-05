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
typedef unsigned long long ull;
typedef long double ld;

ull mod(ull a, ull b) {
  int large = 63 - __builtin_clzll(b);
  for (int i = 62; i >= large; i--) {
    if (a & (1ull << ull(i))) {
      a ^= (b << ull(i - large));
    }
  }
  return a;
}

class SegmentTree {
  typedef ull value_t;

  static constexpr value_t EMPTY_VALUE = 0;

  static inline value_t merge_values(value_t a, value_t b) {
//    eprintf("gcd(%llu, %llu) = ", a, b);
    if (a < b) swap(a, b);
    while (b) {
      value_t c = mod(a, b);
      a = b;
      b = c;
    }
//    eprintf("%llu\n", a);
    return a;
  }

  vector<value_t> tree;
  int lst;

  value_t get(int v, int l, int r, int L, int R) {
    if (r <= L || R <= l) {
      return EMPTY_VALUE;
    }
    if (L <= l && r <= R) {
      return tree[v];
    }
    return merge_values(get(2 * v, l, (l + r) / 2, L, R), get(2 * v + 1, (l + r) / 2, r, L, R));
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
  }

  value_t get(int l, int r) {
    return get(1, 0, lst, l, r);
  }

  void update(int pos, value_t val) {
    pos += lst;
    tree[pos] = val;
    while (pos /= 2) {
      tree[pos] = merge_values(tree[2 * pos], tree[2 * pos + 1]);
    }
  }

};


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<ull> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%llu", &v[i]);
      while (v[i] % 2 == 0) v[i] /= 2;
    }
    SegmentTree t;
    t.init(v);
    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
      int ty;
      scanf("%d", &ty);
      if (ty == 1) {
        int x; ull y;
        scanf("%d%llu", &x, &y);
        while (y % 2 == 0) y /= 2;
        t.update(x - 1, y);
      } else {
        int l, r;
        scanf("%d%d", &l, &r);
        ull val = t.get(l - 1, r );
        printf("%llu\n", val);
      }
    }
  }

  return 0;
}
