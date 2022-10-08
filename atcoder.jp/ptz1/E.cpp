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
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

vector<vector<int>> g;

pair<int, int> dfs(int v, int p) {
  pair<int, int> res = {1, 1};
  bool first = true;
  bool rem = false;
  for (int u : g[v]) {
    if (u == p) continue;
    eprintf("%d -> %d\n", v, u);
    if (first) {
      res = dfs(u, v);
      first = false;
    } else {
      if (res.second == 1) {
        assert(res.first == 1);
        res.first = 0;
        rem = true;
      }
      auto in = dfs(u, v);
      res.first += in.first;
      res.second = false;
      if (!rem && in.second) {
        assert(in.first == 1);
        res.first -= in.first;
        rem = true;
      }
    }
  }
  eprintf("dfs(%d) = %d,%d\n", v, res.first, res.second);
  return res;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    g = vector<vector<int>>(n);

    for (int i = 0; i < n - 1; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      g[a].push_back(b);
      g[b].push_back(a);
    }

    int v = -1;
    for (int i = 0; i < n; i++) {
      if (g[i].size() >= 3) {
        v = i;
        break;
      }
    }
    if (v == -1) {
      printf("1\n");
    } else {
      pair<int, int> ans = dfs(v, -1);
      printf("%d\n", ans.first);
    }
  }

  return 0;
}
