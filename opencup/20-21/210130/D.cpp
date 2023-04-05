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

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> g(n, vector<int>(n));
  vector<int> cnt0(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      scanf("%d", &g[i][j]);
      cnt0[i] += g[i][j] == 0;
    }
  }

  int v = min_element(cnt0.begin(), cnt0.end()) - cnt0.begin();
  int u = max_element(cnt0.begin(), cnt0.end()) - cnt0.begin();

  vector<ll> d(n, 1e18);
  vector<int> p(n);
  d[v] = 0;
  vector<bool> used(n);
  for (int i = 0; i < n; i++) {
    int minid = -1;
    for (int j = 0; j < n; j++) {
      if (!used[j] && (minid == -1 || d[minid] > d[j])) {
        minid = j;
      }
    }
    used[minid] = true;
    for (int j = 0; j < n; j++) {
      if (d[j] > d[minid] + g[minid][j]) {
        d[j] = d[minid] + g[minid][j];
        p[j] = minid;
      }
    }
  }
  if (n == 2) {
    printf("NO\n");
    return;
  }
  vector<pair<int, int>> es;
  int cur = u;
  while (cur != v) {
    int pp = p[cur];
    if (g[pp][cur] != 0) {
      es.emplace_back(pp, cur);
    }
    cur = pp;
  }
  printf("YES\n%d %lld\n", (int)es.size(), d[u]);
  for (auto [x,y] : es) {
    printf("%d %d\n", x + 1, y + 1);
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int z;
  scanf("%d", &z);
  while (z-->0) {
    solve();
  }

  return 0;
}
