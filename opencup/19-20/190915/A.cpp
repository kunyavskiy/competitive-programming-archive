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

template<typename Util>
struct segtree_fast {
  int n, h;
  vector<typename Util::data> t;
  vector<typename Util::update> p;

  segtree_fast() = default;
  explicit segtree_fast(int _n, const typename Util::data &val) {
    n = _n;
    h = __builtin_clz(1) - __builtin_clz(n);
    p.assign(2 * n, Util::NEUTRAL_UPDATE);
    t.assign(2 * n, val);
  }
  explicit segtree_fast(vector<typename Util::data> a) {
    n = a.size();
    h = __builtin_clz(1) - __builtin_clz(n);
    p.assign(2 * n, Util::NEUTRAL_UPDATE);
    t.assign(2 * n, Util::NEUTRAL_DATA);
    copy(a.begin(), a.end(), t.begin() + n);
    for (int i = n - 1; i > 0; i--) {
      t[i] = Util::combine(t[i * 2], t[i * 2 + 1]);
    }
  }

  void update_vertex(int v, const typename Util::update &x) {
    Util::update_vertex(t[v], x);
    if (v < n) {
      p[v] = Util::merge_updates(p[v], x);
    }
  }

  void push_updates_to(int v) {
    for (int s = h; s > 0; s--) {
      int cur = v >> s;
      if (p[cur] != Util::NEUTRAL_UPDATE) {
        update_vertex(cur * 2, p[cur]);
        update_vertex(cur * 2 + 1, p[cur]);
        p[cur] = Util::NEUTRAL_UPDATE;
      }
    }
  }

  void recalc_path(int v) {
    while (v > 1) {
      v >>= 1;
      t[v] = Util::combine(t[v * 2], t[v * 2 + 1]);
      Util::update_vertex(t[v], p[v]);
    }
  }

  typename Util::data get(int l, int r) {
    if (l > r) return Util::NEUTRAL_DATA;
    l += n; r += n;
    push_updates_to(l);
    push_updates_to(r);

    auto res_left = Util::NEUTRAL_DATA;
    auto res_right = Util::NEUTRAL_DATA;
    while (l <= r) {
      if (l & 1) {
        res_left = Util::combine(res_left, t[l++]);
      }
      if (!(r & 1)) {
        res_right = Util::combine(t[r--], res_right);
      }
      l >>= 1;
      r >>= 1;
    }
    return Util::combine(res_left, res_right);
  }

  void upd(int ql, int qr, const typename Util::update &x) {
    if (ql > qr) return;
    ql += n; qr += n;
    int l = ql, r = qr;

    push_updates_to(l);
    push_updates_to(r);
    while (l <= r) {
      if (l & 1) {
        update_vertex(l++, x);
      }
      if (!(r & 1)) {
        update_vertex(r--, x);
      }
      l >>= 1;
      r >>= 1;
    }
    recalc_path(ql);
    recalc_path(qr);
  }
};

struct Data {
  using data = pair<double, int>;
  using update = pair<bool, double>;

  static constexpr data NEUTRAL_DATA = {0, 1};
  static constexpr update NEUTRAL_UPDATE = {0, 0};

  static data combine(const data &left, const data &right) {
    return {left.first + right.first, left.second + right.second};
  }

  static void update_vertex(data &value, const update &upd) {
    if (upd.first) {
      value.first = value.second * upd.second;
    }
  }

  static update merge_updates(const update &old __attribute__((unused)), const update &nw) {
    return nw;
  }
};

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
#endif

  int n, q;
  scanf("%d%d", &n, &q);
  vector<pair<double, int>> a(n);
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    a[i] = {x, 1};
  }
  segtree_fast<Data> t(a);
  while (q--) {
    static char buf[111];
    scanf(" %s", buf);
    string s = buf;
    if (s == "get") {
      int l;
      scanf("%d", &l);
      l--;
      printf("%.15f\n", t.get(l, l).first);
    }
    if (s == "shuffle") {
      int l, r;
      scanf("%d%d", &l, &r);
      l--; r--;
      auto sum = t.get(l, r).first;
      t.upd(l, r, {1, sum / (r - l + 1)});
    }

//    vector<double> b(n);
//    for (int i = 0; i < n; i++) b[i] = t.get(i, i).first;
//    dbv(b);
  }

  return 0;
}
