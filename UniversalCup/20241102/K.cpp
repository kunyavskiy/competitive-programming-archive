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
#include <numeric>
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

const int B = 32000;

int maxp[B];
int divs[B];

int get_divs(int n) {
  int ans = 0;
  for (int i = 2; i * i <= n; i++) {
    while (n % i == 0) {
      n /= i;
      ans++;
    }
  }
  if (n != 1) ans++;
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  divs[1] = 0;
  vector<int> p;
  for (int i = 2; i < B; i++) {
    if (maxp[i] == 0) {
      p.push_back(i);
      maxp[i] = i;
      for (int j = 2 * i; j < B; j += i) {
        maxp[j] = max(maxp[j], i);
      }
    }
  }
  for (int i = 2; i < B; i++) {
    divs[i] = divs[i / maxp[i]] + 1;
  }

  int n;
  while (scanf("%d", &n) == 1) {
    map<int, int> id_;
    vector<int> dcnt;
    vector<vector<int>> g;
    vector<int> a(n);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
      int& x = a[i];
      scanf("%d", &x);
      int dd = get_divs(x);
      ans += dd;
      auto id = [&](int y) {
        auto [it, ins] = id_.emplace(y, (int)id_.size());
        if (ins) {
          g.emplace_back();
          dcnt.push_back((y < B) ? divs[y] : (dd - divs[x / y]));
          assert(it->second == (int)g.size() - 1);
        }
        return it->second;
      };
      auto add = [&](int d, int vid) {
        int did = id(d);
        g[did].push_back(vid);
      };
      for (int j = 1; j * j <= x; j++) {
        if (x % j == 0) {
          add(j, i);
          if (j != x / j) {
            add(x / j, i);
          }
        }
      }
    }

    vector<int> order(dcnt.size());
    std::iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) { return dcnt[a] < dcnt[b]; });

    vector<int> used(dcnt.size());
    vector<int> mt(n, -1);
    int used_col = 1;

    auto dfs = [&](auto self, int v) -> bool {
      if (used[v] == used_col) return false;
      used[v] = used_col;
      for (auto u : g[v]) {
        if (mt[u] == -1 || self(self, mt[u])) {
          mt[u] = v;
          return true;
        }
      }
      return false;
    };

    for (int i = 0; i < (int)order.size(); i++) {
      ++used_col;
      if (dfs(dfs, order[i])) {
        ans -= dcnt[order[i]];
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
