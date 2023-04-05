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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<vector<int>> g;

pair<int, int> dfs(int x, int p, int k) {
  pair<int, int> res = {0, 1};
  for (int y : g[x]) {
    if (y != p) {
      auto pp = dfs(y, x, k);
      res.first += pp.first;
      res.second += pp.second;
    }
  }
  if (res.second >= k) {
    res.first++;
    res.second = 0;
  }
  return res;
}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c1.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }

  for (int k = 1; k <= n; k++) {
    cout << dfs(0, -1, k).first << "\n";
  }

  return 0;
}
