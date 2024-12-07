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

const int MOD = 998244353;

ll solve(const vector<vector<int>> &g) {
  int n = g.size();
  vector<int> cnt(n);
  ll total = 0;
  auto dfs = [&](auto self, int v, int p) -> vector<int> {
     vector<int> ans = {v};
     for (int u : g[v]) {
       if (u != p) {
         auto sub = self(self, u, v);
         ans.insert(ans.end(), sub.begin(), sub.end());
       }
     }
     if (v != 0) {
       for (int x : ans) {
         if (x > v) {
           total++;
         }
       }
     }

     return ans;
  };
  dfs(dfs, 0, -1);
  eprintf("pw = %lld\n", total);
  int a = 1;
  for (int i = 0; i < total; i++) {
    a = (a + a) % MOD;
  }
  return a;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<vector<int>> g(n);
  for (int i = 0; i < n - 2; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  vector<int> reachable;
  auto dfs1 = [&](auto self, int v, int p) -> void {
    reachable.push_back(v);
    for (int u : g[v]) {
      if (u != p) {
        self(self, u, v);
      }
    }
  };
  dfs1(dfs1, 0, -1);

  vector<int> other;
  for (int i = 0; i < n; i++) {
    if (find(reachable.begin(), reachable.end(), i) == reachable.end()) {
      other.push_back(i);
    }
  }

  ll ans = 0;

  if (other.size() == 1) {
    ans += solve(g);
  }
  for (int u : reachable) {
    for (int v : other) {
      g[u].push_back(v);
      g[v].push_back(u);
      eprintf("try %d -> %d\n", u, v);
      ans += solve(g);
      g[u].pop_back();
      g[v].pop_back();
    }
  }

  printf("%d\n", (int)(ans % MOD));

  return 0;
}