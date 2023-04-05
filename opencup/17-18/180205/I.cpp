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

vector<vector<int>> es;
vector<set<int>> cols;
vector<int> used;
int usedv = 0;

void dfs(int v, const set<int> &as_set, const set<int> &bs_set, int curcol) {
  if (used[v] >= usedv) {
    return;
  }
  assert(as_set.count(v));
  used[v] = usedv;
  cols[v].insert(curcol);
  for (int to : es[v]) {
    if (bs_set.count(to)) {
      dfs(to, bs_set, as_set, curcol);
    }
  }
}

int edge_exists(int b, int to) {
  for (int c1 : cols[b])
    if (cols[to].count(c1)) {
      return true;
    }
  return false;
}

void dfs2(int b, const set<int> &bs_bad, int curcol) {
  if (cols[b].size() >= 2) return;
  cols[b].insert(curcol);
  for (int to : es[b]) {
    if (!bs_bad.count(to)) continue;

    if (!edge_exists(b, to)) {
      dfs2(to, bs_bad, curcol);
    }
  }
}

int lastcol;

void solve(const vector<vector<int>> &layers) {
  if (layers.size() == 1) {
    int v = layers[0][0];
    cols[v].insert(lastcol++);
    cols[v].insert(lastcol++);
    return;
  }
  for (int lid = (int)layers.size() - 2; lid > 0; lid--) {
    vector<int> as = layers[lid];
    const vector<int> &bs = layers[lid + 1];
    set<int> bs_set(bs.begin(), bs.end());

    as.erase(remove_if(as.begin(), as.end(), [&bs_set](int a) {
      for (int to : es[a])
        if (bs_set.count(to)) return false;
      return true;
    }), as.end());
    set<int> as_set(as.begin(), as.end());

    set<int> bs_good;
    set<int> bs_bad;
    for (int b : bs) {
      bool good = false;
      for (int to : es[b])
        if (as_set.count(to)) good = true;
      if (good) bs_good.insert(b);
      else bs_bad.insert(b);
    }

    usedv++;
    for (int ast : as) {
      if (used[ast] < usedv) {
        dfs(ast, as_set, bs_good, lastcol);
        lastcol++;
      }
    }
    for (int b : bs_bad) {
      for (int to : es[b])
        if (as_set.count(to)) {
          assert(cols[to].size() == 1);
          cols[b].insert(*cols[to].begin());
        }
    }

    usedv++;
    for (int bst : bs_bad) {
      if (used[bst] < usedv) {
        dfs2(bst, bs_bad, lastcol);
        lastcol++;
      }
    }
  }

  const vector<int> &as = layers[0];
  assert(as.size() == 1);

  int col1 = lastcol++;
  int col2 = lastcol++;
  cols[*as.begin()].insert(col1);
  cols[*as.begin()].insert(col2);

  set<int> bs0(layers[1].begin(), layers[1].end());
  set<int> bs(layers[1].begin(), layers[1].end());
  deque<int> q;
  deque<int> qcol;
  int v = *bs.begin();
  q.push_back(v);
  qcol.push_back(col1);
  bs.erase(v);
  cols[v].insert(col1);

  while (!q.empty()) {
    int v = q.front(); q.pop_front();
    int vcol = qcol.front(); qcol.pop_front();
    for (int u : es[v]) {
      if (bs0.count(u) && !edge_exists(v, u) && cols[u].size() < 2) {
        cols[u].insert(vcol);
        q.push_back(u);
        qcol.push_back(vcol);
        bs.erase(u);
      }
    }
    for (auto it = bs.begin(); it != bs.end();) {
      auto nit = it;
      nit++;
      int u = *it;
      if (cols[u].size() < 2) {
        cols[u].insert(col1 + col2 - vcol);
        q.push_back(u);
        qcol.push_back(col1 + col2 - vcol);
        bs.erase(u);
      }
      it = nit;
    }
  }
}

bool check() {
  const int n = (int)cols.size();
  for (int i = 0; i < n; i++) {
    while (cols[i].size() < 2) {
      cols[i].insert(lastcol);
      lastcol++;
    }
    if (cols[i].size() > 2) return false;
  }
  map<int, vector<int>> byColor;
  for (int i = 0; i < n; i++) {
    for (int c : cols[i])
      byColor[c].push_back(i);
  }

  set<pair<int, int>> needEs, wasEs;
  for (int a = 0; a < n; a++)
    for (int b : es[a])
      if (a < b)
        needEs.emplace(a, b);
  for (const auto &cvs : byColor) {
    for (int a : cvs.second)
      for (int b : cvs.second)
        if (a < b) {
          if (!needEs.count(make_pair(a, b))) {
            return false;
          }
          wasEs.emplace(a, b);
        }
  }
  return needEs.size() == wasEs.size();
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    es.clear();
    es.resize(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b), a--, b--;
      es[a].push_back(b);
      es[b].push_back(a);
    }
    cols.clear();
    cols.resize(n);
    lastcol = 0;

    used.clear();
    used.resize(n);

    vector<int> d(n, -1);
    for (int st = 0; st < n; st++) {
      if (d[st] < 0) {
        vector<vector<int>> layers(1);
        deque<int> q;
        q.push_back(st);
        d[st] = 0;
        layers[d[st]].push_back(st);

        while (!q.empty()) {
          int v = q.front();
          q.pop_front();
          for (int b : es[v]) {
            if (d[b] == -1) {
              d[b] = d[v] + 1;
              layers.resize(max((int) layers.size(), d[b] + 1));
              layers[d[b]].push_back(b);
              q.push_back(b);
            }
          }
        }
        solve(layers);
      }
    }
    if (!check()) {
      printf("No\n");
    } else {
      printf("Yes\n");
      for (int i = 0; i < n; i++) {
        auto it = cols[i].begin();
        printf("%d ", *it++);
        printf("%d\n", *it++);
      }
    }
  }
  return 0;
}
