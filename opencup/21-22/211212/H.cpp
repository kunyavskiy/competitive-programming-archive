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

int n;
vector<vector<int>> g;
vector<int> a, t;
vector<ll> ans1, ans2;

void dfs(int v, int p) {
  ll mx1 = 0, mx2 = 0;
  ll maxa = 0;
  for (int u: g[v]) {
    if (u != p) {
      dfs(u, v);
      ans2[v] += ans1[u];
      ll temp = a[u] + ans2[u] - ans1[u];
      maxa = max(maxa, (ll)a[u]);
      if (mx1 < temp) swap(mx1, temp);
      if (mx2 < temp) swap(mx2, temp);
    }
  }
  ans1[v] = ans2[v] + maxa;
  for (int u: g[v]) {
    if (u == p || t[u] != 3) continue;
    ans1[v] = max(ans1[v], ans2[v] + a[u] + ((a[u] + ans2[u] - ans1[u] == mx1) ? mx2 : mx1));
  }
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int tst;
  scanf("%d", &tst);
  while (tst-->0) {
    scanf("%d", &n);
    g = vector<vector<int>>(n);
    a = vector<int>(n);
    t = vector<int>(n);
    ans1 = vector<ll>(n);
    ans2 = vector<ll>(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%d", &t[i]);
    }
    for (int i = 0; i < n - 1; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      --u, --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }
    dfs(0, -1);
    printf("%lld\n", ans1[0] + a[0]);
  }

  return 0;
}
