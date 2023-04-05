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
vector<int> d;
vector<bool> z;

bool dfs(int x, int p) {
  if (z[x]) return false;
  z[x] = true;
  int c4 = -1;
  int n1 = 0;
  for (int y : g[x]) {
    if (y == p) continue;
    if (d[y] == 4) {
      if (c4 == -1) {
        c4 = y;
      } else {
        return false;
      }
    } else if (d[y] == 1) {
      n1++;
    } else {
      return false;
    }
  }
  if (n1 == 3 && c4 == -1) {
    return true;
  } else if (n1 == 2 && c4 != -1) {
    return dfs(c4, x);
  } else {
    return false;
  }
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  g.resize(n);
  d.resize(n);
  z.resize(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    g[a].push_back(b);
    g[b].push_back(a);
    d[a]++;
    d[b]++;
  }
  int res = 0;
  for (int i = 0; i < n; i++) {
    if (!z[i] && d[i] == 3) {
      if (dfs(i, -1)) {
        res++;
      }
    }
  }
  cout << res << "\n";

  return 0;
}
