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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

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

struct log_double {
  double logv = 0;
  friend log_double operator*(log_double a, log_double b) {
    return log_double{a.logv + b.logv};
  }
  friend log_double operator/(log_double a, log_double b) {
    return log_double{a.logv - b.logv};
  }
  friend log_double operator+(log_double a, log_double b) {
    double m = min(a.logv, b.logv);
    double M = max(a.logv, b.logv);
    auto res = log_double{M + log1p(exp(m - M))};
    eprintf("%lf + %lf = %lf\n", a.get(), b.get(), res.get());
    return res;
  }
  log_double log1m() const { return { log1p(-exp(logv))}; }
  friend bool operator<(log_double a, log_double b) { return a.logv < b.logv; }
  double get() { return exp(logv); }
};

struct item {
  log_double cost;
  log_double p;
  int first, last;
  bool operator<(const item &other) const __attribute__((noinline)){
    return cost / p.log1m() < other.cost / other.p.log1m();
  }
  friend item operator+(const item& a, const item& b) {
    return {{a.cost + b.cost * a.p}, {a.p * b.p}, a.first, b.last};
  }
};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<item> tasks(n + 1);
    vector<vector<int>> g(n + 1);
    for (int i = 1; i <= n; i++) {
      double c, p; int d;
      scanf("%lf%lf%d", &c, &p, &d);
      tasks[i] = item{ log_double{log(c)}, log_double{log(p)}, i, i};
      g[d].push_back(i);
    }

    vector<int> next(n + 1, -1);

    auto merge = [&](multiset<item>& a, multiset<item>& b) {
      if (a.size() < b.size()) a.swap(b);
      for (const auto& item : b) {
        a.insert(item);
      }
      b.clear();
    };

    auto dfs = [&](auto dfs, int v) -> multiset<item> {
      multiset<item> res;
      for (int u : g[v]) {
        auto r = dfs(dfs, u);
        merge(res, r);
      }
      if (v != 0) {
        item cur = tasks[v];
        while (!res.empty()) {
          auto nxt = res.begin();
          if (!(cur < *nxt)) {
            next[cur.last] = nxt->first;
            //eprintf("[%d..%d] + [%d..%d]\n", cur.first, cur.last, nxt->first, nxt->last);
            cur = cur + *nxt;
            res.erase(res.begin());
          } else {
            break;
          }
        }
        res.insert(cur);
      }
      return res;
    };

    auto r = dfs(dfs, 0);
    for (auto item : r) {
      //eprintf("show: %d..%d, score = %lf\n", item.first, item.last, (item.cost / item.p).get());
      for (int i = item.first; i != -1; i = next[i]) {
        printf("%d\n", i);
      }
    }
  }
}
