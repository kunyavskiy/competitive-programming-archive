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
  int max, cnt;
  item() : max(-1e9), cnt(0) {}
  explicit item(int val) {
    max = val;
    cnt = 1;
  }
  item(int max, int cnt) : max(max), cnt(cnt) {}

  item operator+(const item& r) {
    if (max == r.max) {
      return {max, cnt + r.cnt};
    }
    if (max > r.max) {
      return *this;
    }
    return r;
  }

  item operator*(const item& r) {
    return {max + r.max, cnt * r.cnt};
  }
};

int k;
item res;

struct mergable {
  vector<item> v;
  int d;

  item get(int pos) {
    if (pos >= (int)v.size()) return item();
    return v[v.size() - pos - 1] * item{d, 1};
  }

  void update(int pos, item a) {
    assert(pos < (int)v.size());
    v[v.size() - pos - 1] = v[v.size() - pos - 1] + a * item{-d, 1};
  }

  void extend(int w) {
    d += w;
    v.push_back({-d, 1});
  }

  void merge(mergable &r) {
    if (r.v.size() > v.size()) {
      r.v.swap(v);
      swap(d, r.d);
    }
    for (int i = 1; i < (int)r.v.size() && i < k; i++) {
      res = res + r.get(i) * get(k - i);
    }
    for (int i = 1; i < (int)r.v.size(); i++) {
      update(i, r.get(i));
    }
  }
};

struct Tree {
  vector<vector<pair<int, int>>> g;
  void init(int n) {
    g.resize(n);
  }

  void add(int u, int v, int w) {
    g[u].push_back({v, w});
    eprintf("%d %d %d\n", u, v, w);
  }

  vector<mergable> ans;

  item dfs(int v) {
    ans[v].extend(0);
    for (auto u : g[v]) {
      dfs(u.first);
      ans[u.first].extend(u.second);
      ans[v].merge(ans[u.first]);
    }
    res = res + ans[v].get(k);
    /*
    eprintf("%d: ", v);
    for (int i = 0; i < (int)ans[v].v.size(); i++) {
      eprintf("(%d, %d) ", ans[v].get(i).max, ans[v].get(i).cnt);
    }
    eprintf("\n");
     */
    return res;
  }

  item solve() {
    ans.resize(g.size());
    return dfs(0);
  }

};

const int MAXN = 31000;

vector<pair<int, int>> g[MAXN];
vector<int> d;
vector<bool> used;
Tree tree;

void dijkstra(int n) {
  d = vector<int>(n, 1e9);
  d[0] = 0;
  set<pair<int, int>> s;
  s.insert({0, 0});

  for (int i = 0; i < n; i++) {
    assert(!s.empty());
    int v = s.begin()->second;
    s.erase(s.begin());
    for (int j = 0; j < (int) g[v].size(); j++) {
      int to, cost;
      tie(to, cost) = g[v][j];
      if (d[to] > d[v] + cost) {
        s.erase({d[to], to});
        d[to] = d[v] + cost;
        s.insert({d[to], to});
      }
    }
  }
}

void dfs(int v) {
  used[v] = true;
  for (auto e : g[v]) {
    int to, w;
    tie(to, w) = e;
    if (d[v] + w == d[to] && !used[to]) {
      tree.add(v, to, w);
      dfs(to);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d%d", &n, &m, &k);
  k--;
  for (int i = 0; i < m; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    --a, --b;
    g[a].push_back({b, c});
    g[b].push_back({a, c});
  }

  for (int i = 0; i < n; i++) {
    sort(g[i].begin(), g[i].end());
  }

  dijkstra(n);
  used = vector<bool>(n);
  tree.init(n);
  dfs(0);

  tree.solve();
  printf("%d %d\n", res.max, res.cnt);
  return 0;
}

/*
0 1 1
1 2 2
2 3 1
1 4 1
4 5 1
3: (0, 1)
2: (0, 2) (1, 1)
5: (0, 1)
4: (0, 2) (1, 1)
1: (0, 3) (2, 2) (3, 1)
0: (0, 2) (1, 3) (3, 2) (4, 1)
 */