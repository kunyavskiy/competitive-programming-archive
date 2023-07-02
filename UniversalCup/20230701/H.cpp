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
#include <numeric>
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

struct edge {
  int u, v;
  ll w;
};

struct dsu {
  vector<int> v;
  explicit dsu(int n) : v(n) {
    std::iota(v.begin(), v.end(), 0);
  }

  int get(int a) {
    if (a == v[a]) return a;
    return v[a] = get(v[a]);
  }

  void join(int a, int b) {
    v[get(a)] = get(b);
  }
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m, q; ll V;
  while (scanf("%d%d%d%lld", &n, &m, &q, &V) == 4) {
    vector<edge> es(m);
    for (int i = 0; i < m; i++) {
      scanf("%d%d%lld", &es[i].u, &es[i].v, &es[i].w);
      --es[i].u, --es[i].v;
    }
    auto gen = [&](long long mask) {
      dsu d(n);
      for (auto [u, v, w] : es) {
        if ((w & mask) == mask) {
          d.join(u, v);
        }
      }
      return d;
    };

    vector<dsu> ds;
    ds.push_back(gen(V));
    for (int i = 59; i >= 0; i--) {
      if (!(V & (1LL << i))) {
        ds.push_back(gen((V | ((1LL << i) - 1))+1));
      }
    }

    for (int i = 0; i < q; i++) {
      int u, v;
      scanf("%d%d\n", &u, &v);
      --u, --v;
      if (std::any_of(ds.begin(), ds.end(), [&](dsu& d) { return d.get(u) == d.get(v); })) {
        printf("Yes\n");
      } else {
        printf("No\n");
      }
    }
  }

  return 0;
}
