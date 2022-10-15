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

struct item {
  int cnt;
  int bad;
  int good;
};

const int INF = (int)1e9;

item merge(const item &a, const item &b, int d) {
  item res;
  res.cnt = a.cnt + b.cnt;
  res.good = min(a.good, b.good);
  res.bad = -INF;
  if (a.bad + b.good > d) res.bad = max(res.bad, a.bad);
  if (b.bad + a.good > d) res.bad = max(res.bad, b.bad);
  return res;
}

vector<vector<int>> g;
vector<int> ans;

item dfs(int v, int p, int d) {
  item res = {0, 0, INF};
  for (int u : g[v]) {
    if (u != p) {
      item x = dfs(u, v, d);
      x.bad += 1;
      x.good += 1;
      res = merge(res, x, d);
    }
  }
  if (res.bad == d || (res.bad > 0 && p == -1)) {
    ans.push_back(v);
    res.cnt += 1;
    res.good = 0;
    res.bad = -INF;
  }
  if (res.good > d) {
    res.bad = max(res.bad, 0);
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  g.resize(n);
  for (int i = 1; i < n; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }


  int l = 0;
  int r = n;
  while (r - l > 1) {
    int m = (l + r) / 2;
    item d = dfs(0, -1, m);
    if (d.cnt <= 2) {
      r = m;
    } else {
      l = m;
    }
  }

  ans.clear();
  dfs(0, -1, r);

  eprintf("l = %d\n", l);
  assert(ans.size() >= 1);
  if (ans.size() == 1) {
    eprintf("HERE!\n");
    for (int i = 0; i < n; i++) {
      if (i != ans[0]) {
        ans.push_back(i);
        break;
      }
    }
  }

  printf("%d %d\n", ans[0] + 1, ans[1] + 1);

  return 0;
}
