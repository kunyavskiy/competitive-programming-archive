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

vector<int> p;
vector<int> c;

void init(int n) {
  c.clear();
  c.resize(n, 0);
  p.resize(n, 0);
  for (int i = 0; i < n; i++) {
    p[i] = i;
  }
}

int get(int v) {
  if (v == p[v]) return v;
  return p[v] = get(p[v]);
}

void solve(int n, int m) {
  int a, b;
  scanf("%d%d", &a, &b);
  --a, --b;
  vector<pair<int, int>> es;
  es.push_back({2 * b, 2 * a + 1});
  es.push_back({2 * b, 2 * a + 1});

  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    es.push_back({2 * u, 2 * v + 1});
  }

  vector<vector<int>> g(2 * n);
  init(2 * n);

  for (int i = 0; i < m + 2; i++) {
    int f = es[i].first;
    int t = es[i].second;
    f = get(f);
    t = get(t);
    if (c[f] + c[t] <= 1) {
      p[f] = t;
      if (f == t || c[f] + c[t] == 1) {
        c[t] = 1;
      }
      g[es[i].first].push_back(i);
      g[es[i].second].push_back(i);
//      eprintf("+ %d %d %d\n", i, es[i].first, es[i].second);
    }
  }

  vector<bool> used(es.size());
  vector<bool> usedv(2 * n);
  vector<int> deg(2 * n);
  vector<int> ans(2 * n);

  set<pair<int, int>> s;
  for (int i = 0; i < (int)g.size(); i++) {
    deg[i] = g[i].size();
    s.insert({deg[i], i});
  }

  while (!s.empty()) {
    int v = s.begin()->second;
    if (deg[v] == 0) {
      printf("NO\n");
      return;
    }
    s.erase(s.begin());
    int id = -1;
    for (int u : g[v]) {
      if (!used[u]) {
        id = u;
      }
    }
//    eprintf("used id = %d for %d\n", id, v);
    assert(id != -1);
    used[id] = true;
    int other = es[id].first + es[id].second - v;
    s.erase({deg[other], other});
    deg[other]--;
    if (!usedv[other]) {
      s.insert({deg[other], other});
    }
    ans[v] = id;
    usedv[v] = true;
  }

  printf("YES\n");
  for (int i = 0; i < n; i++) {
    if (i != a) {
      printf("%d ", ans[2 * i + 1] - 1);
    }
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    if (i != b) {
      printf("%d ", ans[2 * i] - 1);
    }
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
//    eprintf("=====\n");
    solve(n, m);
  }

  return 0;
}
