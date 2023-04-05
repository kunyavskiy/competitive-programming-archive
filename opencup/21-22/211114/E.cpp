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

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m, c;
  while (scanf("%d%d%d", &n, &m, &c) == 3) {
    vector<vector<pair<int, int>>> g(n);
    int ans = 0;
    for (int i = 0; i < m; i++) {
      int a, b, w;
      scanf("%d%d%d", &a, &b, &w);
      --a, --b;
      g[a].emplace_back(b, w);
      if (w <= c) ans = 1;
    }
    for (int i = 0; i < n && ans == 1; i++) {
      vector<int> d(n, 2e9);
      d[i] = 0;
      priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
      q.emplace(0, i);
      while (!q.empty()) {
        auto [curd, v] = q.top();
        q.pop();
        if (curd != d[v]) continue;
        for (auto [u, w] : g[v]) {
          if (d[u] > d[v] + w) {
            d[u] = d[v] + w;
            q.emplace(d[u], u);
          }
          if (u == i && d[v] + w <= c) {
            ans = 2;
          }
        }
      }
    }
    printf("%d\n", ans);
  }


  return 0;
}
