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

#define INF (1L << 60)
#define MAX 20

vector<ll> d;
vector<vector<int>> p;
vector<bool> z;
vector<int> depth;
vector<vector<int>> g;
vector<int> eto;
vector<ll> ew;

int lca(int u, int v) {
  if (depth[u] > depth[v]) {
    int t = u; u = v; v = t;
  }
  for (int i = MAX - 1; i >= 0; i--) {
    if (depth[p[v][i]] >= depth[u]) {
      v = p[v][i];
    }
  }
  if (u == v) return u;
  for (int i = MAX - 1; i >= 0; i--) {
    if (p[v][i] != p[u][i]) {
      v = p[v][i];
      u = p[u][i];
    }
  }
  return p[v][0];
}

vector<int> indeg;
vector<int> ine;
vector<int> ppp;

void dfs(int u) {
  if (z[u])
    return;
  z[u] = true;
  p[u][0] = -1;
  for (auto e : g[u]) {
    int v = eto[e];
    ll dd = ew[e];
    if (d[v] == d[u] - dd) {
      indeg[u]++;
      ine[u] = e;
      dfs(v);
      if (p[u][0] == -1) {
        p[u][0] = v;
      } else {
        p[u][0] = lca(p[u][0], v);
      }
    }
  }
  if (p[u][0] == -1) {
    p[u][0] = u;
    depth[u] = 0;
  } else {
    depth[u] = depth[p[u][0]] + 1;
  }
  for (int i = 1; i < MAX; i++) {
    p[u][i] = p[p[u][i - 1]][i - 1];
  }
  ppp.push_back(u);
}

vector<int> ss;

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  g.resize(n);
  eto.resize(2 * m);
  ew.resize(2 * m);
  for (int i = 0; i < m; i++) {
    int u, v, c;
    scanf("%d%d%d", &u, &v, &c);
    u--; v--;
//    cout << u << " " << v << " " << c << endl;
    g[u].push_back(2 * i);
    g[v].push_back(2 * i + 1);
    eto[2 * i] = v;
    eto[2 * i + 1] = u;
    ew[2 * i] = c;
    ew[2 * i + 1] = c;
  }

  d.assign(n, INF);
  d[0] = 0;
  set<pair<ll, int>> q;
  q.insert({d[0], 0});

  while (q.size() > 0) {
    int v = (*(q.begin())).second;
//    cout << v << " " << d[v] << endl;
    q.erase(q.begin());
    for (auto e : g[v]) {
      int u = eto[e];
      ll dd = ew[e];
      if (d[u] > d[v] + dd) {
        q.erase({d[u], u});
        d[u] = d[v] + dd;
//        cout << " " << u << " " << d[u] << endl;
        q.insert({d[u], u});
      }
    }
  }
//  for (int i = 0; i < n; i++) {
//    cout << d[i] << " ";
//  }
//  cout << endl;

  z.resize(n);
  p.assign(n, vector<int>(MAX));
  indeg.resize(n);
  ine.resize(n);
  depth.resize(n);
  for (int i = 0; i < n; i++) {
    dfs(i);
  }

//  for (int i = 0; i < n; i++) {
//    cout << p[i][0] << " ";
//  }
//  cout << endl;
//
  ss.resize(n);
//  dfs2(0);
  for (int i = (int)ppp.size() - 1; i >= 0; i--) {
    int j = ppp[i];
    ss[j]++;
    if (p[j][0] != j) {
      ss[p[j][0]] += ss[j];
    }
  }

//  for (int i = 0; i < n; i++) {
//    cout << ss[i] << " ";
//  }
//  cout << endl;

  vector<int> res(m);

  for (int i = 0; i < n; i++) {
    if (indeg[i] == 1) {
      res[ine[i] / 2] = ss[i];
    }
  }
  for (int i = 0; i < m; i++) {
    cout << res[i] << endl;
  }

  return 0;
}
