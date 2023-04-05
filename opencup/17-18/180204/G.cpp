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

const int LOGN = 18;

struct Edge {
  int u, v, w;
};

struct Tree {
  vector <vector<Edge>> ed;
  vector <int> inT, outT;
  vector <vector<int>> up;
  vector <vector<int>> up_max;
  int timer;

  Tree(int n) : ed(n), inT(n, -1), outT(n, -1), up(LOGN, vector<int>(n, -1)), up_max(LOGN, vector<int>(n, -1)), timer(0) {
  }

  void addEdge(const Edge & e) {
    ed[e.u].push_back(e);
    ed[e.v].push_back(Edge({e.v, e.u, e.w}));
  }

  void dfs(int s, int par = -1, int parW = -1) {
    up[0][s] = par == -1 ? s : par;
    up_max[0][s] = parW;

    for (int i = 1; i < LOGN; ++i) {
      up[i][s] = up[i - 1][up[i - 1][s]];
      up_max[i][s] = max(up_max[i - 1][s], up_max[i - 1][up[i - 1][s]]);
    }

    inT[s] = timer++;
    for (auto & e : ed[s]) {
      if (e.v == par) { continue; }
      dfs(e.v, s, e.w);
    }
    outT[s] = timer++;
  }

  bool is_ancestor(int p, int v) const {
    return inT[p] <= inT[v] && outT[v] <= outT[p];
  }

  int getLCA(int u, int v) const {
    if (is_ancestor(u, v)) {
      return u;
    }
    for (int i = LOGN - 1; i >= 0; --i) {
      int u2 = up[i][u];
      if (!is_ancestor(u2, v)) {
        u = u2;
      }
    }
    assert(is_ancestor(up[0][u], v));
    return up[0][u];
  }

  int getMax(int p, int v) const {
    int res = -1;
    for (int i = LOGN - 1; i >= 0; --i) {
      int v2 = up[i][v];
      if (is_ancestor(p, v2)) {
        res = max(res, up_max[i][v]);
        v = v2;
      }
    }
    assert(p == v);
    return res;
  }
};

struct Dsu {
  int n;
  vector <int> up;
  vector <int> rank;

  Dsu(int n) : n(n), up(n), rank(n) {
    for (int i = 0; i < n; ++i) {
      up[i] = i;
      rank[i] = 0;
    }
  }

  bool join(int x, int y) {
    x = get(x);
    y = get(y);
    if (x == y) { return false;}
    if (rank[x] < rank[y]) { swap(x, y); }
    up[y] = x;
    if (rank[x] == rank[y]) ++rank[x];
    return true;
  }

  int get(int x) {
    if (up[x] == x) {
      return x;
    } else {
      return up[x] = get(up[x]);
    }
  }
};

vector <Edge> build_mst(const vector <vector<Edge>> & ed, Dsu & dsu) {
  int n = int(ed.size());
  vector <Edge> edges;
  for (auto & vec : ed) {
    for (auto & e : vec) {
      assert(0 <= e.u && e.u < n);
      assert(0 <= e.v && e.v < n);
      if (e.u < e.v) {
        edges.push_back(e);
      }
    }
  }
  sort(edges.begin(), edges.end(), [](const Edge & e1, const Edge & e2){ return e1.w < e2.w;});
  vector <Edge> ans;
  for (auto & e : edges) {
    if (dsu.join(e.u, e.v)) {
      ans.push_back(e);
    }
  }
  return ans;
}

Tree build_tree(int n, const vector <Edge> &mst) {
  Tree tree(n);
  for (auto & e : mst) {
    tree.addEdge(e);
  }
  tree.dfs(0);
  return tree;
}

vector<Edge> buildSubTree(vector <int> v, const Tree & tree) {
  sort(v.begin(), v.end(), [&tree](int x, int y) { return tree.inT[x] < tree.inT[y];});
  vector <int> v2 = v;
  for (int i = 1; i < int(v.size()); ++i) {
    v2.push_back(tree.getLCA(v[i - 1], v[i]));
  }
  sort(v2.begin(), v2.end(), [&tree](int x, int y) { return tree.inT[x] < tree.inT[y];});
  v2.erase(unique(v2.begin(), v2.end()), v2.end());
  vector <int> stack;
  assert(!v2.empty());
  stack.push_back(v2[0]);
  vector<Edge> res;
  for (int i = 1; i < int(v2.size()); ++i) {
    while (!stack.empty() && !tree.is_ancestor(stack.back(), v2[i])) {
      stack.pop_back();
    }
    assert(!stack.empty());
    res.push_back(Edge({stack.back(), v2[i], tree.getMax(stack.back(), v2[i])}));
    stack.push_back(v2[i]);
  }
  return res;
}

int addV(map<int,int> & mapping, int v) {
  if (mapping.count(v)) {
    return mapping[v];
  }
  int x = (int)mapping.size();
  return mapping[v] = x;
}

vector<vector<Edge>> compress(const vector<Edge> & edges, map<int,int> & mapping) {
  mapping.clear();
  for (auto & e : edges) {
    addV(mapping, e.u);
    addV(mapping, e.v);
  }
  vector <vector<Edge>> ed(mapping.size());
  for (auto & e : edges) {
    int u2 = addV(mapping, e.u);
    int v2 = addV(mapping, e.v);
    int w2 = e.w;
    ed[u2].push_back(Edge({u2, v2, w2}));
    ed[v2].push_back(Edge({v2, u2, w2}));
  }
  return ed;
}

bool solve() {
  int n, m;
  if (scanf("%d%d", &n, &m) != 2) { return false; }

  vector <vector<Edge>> ed(n);
  for (int i = 0; i < m; ++i) {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    --u, --v;
    ed[u].push_back(Edge({u, v, w}));
    ed[v].push_back(Edge({v, u, w}));
  }

  Dsu dsu0(n);
  vector <Edge> mst = build_mst(ed, dsu0);
  ll mstW = 0;
  for (auto & e : mst) {
    mstW += e.w;
  }
  Tree tree = build_tree(n, mst);
  for (int i = 0; i < n; ++i) {
    vector <int> neigh;
    neigh.push_back(i);
    for (auto & e : ed[i]) {
      assert(e.u == i);
      neigh.push_back(e.v);
    }
    vector <Edge> g2 = buildSubTree(neigh, tree);
    ll curW = mstW;
    for (auto & e : g2) {
      curW -= e.w;
    }
    map <int, int> mapping;
    vector <vector<Edge>> ed2 = compress(g2, mapping);
    Dsu dsu(ed2.size());
    for (auto & e : ed[i]) {
      curW += e.w;
      assert(dsu.join(mapping[e.u], mapping[e.v]));
    }
    vector <Edge> mst2 = build_mst(ed2, dsu);
    for (auto & e : mst2) {
      curW += e.w;
    }

    printf("%lld\n", curW);
  }

  return true;
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  while (solve());

  return 0;
}
