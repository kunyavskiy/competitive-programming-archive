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

class MaxFlow {

  typedef long long flow_type;
  const flow_type FLOW_INF = 1LL << 60;

  struct Edge {
    int to, next;
    flow_type f, c;
  };

  vector<Edge> es;
  int n;
  vector<int> head;
  vector<int> d;
  vector<int> ptr;
  vector<int> side;

  flow_type dfs(int s, int t, flow_type have, flow_type min_edge) {
    if (s == t) {
      return have;
    }
    flow_type res = 0;
    for (int &i = ptr[s]; i != -1; i = es[i].next) {
      int to = es[i].to;
      if (d[to] != d[s] + 1) continue;
      if (es[i].c < min_edge) continue;
      flow_type done = dfs(to, t, min(have, es[i].c), min_edge);
      pushFlow(i, done);
      have -= done;
      res += done;
      if (have == 0) break;
    }
    return res;
  }

  bool bfs(int s, int t, flow_type min_edge) {
    queue<int> q;
    d = vector<int>(n, -1);
    d[s] = 0;
    q.push(s);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      int e = head[v];
      while (e != -1) {
        if (es[e].c >= min_edge) {
          int to = es[e].to;
          if (d[to] == -1) {
            d[to] = d[v] + 1;
            q.push(to);
          }
        }
        e = es[e].next;
      }
    }
    return d[t] != -1;
  }

public:
  explicit MaxFlow(int n) : n(n), head(n, -1) {}

  int addVertex() {
    int id = n++;
    head.push_back(-1);
    return id;
  }

  int addEdge(int from, int to, flow_type c, flow_type rc = 0) {
//    eprintf("   %d %d %lld\n", from, to, c);
    int id = (int) es.size();
    es.push_back({to, head[from], 0, c});
    head[from] = id;
    es.push_back({from, head[to], 0, rc});
    head[to] = id ^ 1;
    return id;
  }

  void pushFlow(int eid, flow_type val) {
    es[eid].f += val, es[eid].c -= val;
    es[eid ^ 1].f -= val, es[eid ^ 1].c += val;
  }

  flow_type getFlow(int s, int t) {
    flow_type res = 0;
    for (flow_type i = FLOW_INF; i >= 1; i /= 2) {
      while (bfs(s, t, i)) {
        ptr = head;
        res += dfs(s, t, FLOW_INF, i);
      }
    }
    side = vector<int>(n);
    for (int i = 0; i < n; i++) {
      side[i] = d[i] == -1;
    }
    return res;
  }

  bool isCut(int eid) {
    return side[es[eid].to] == 1 && side[es[eid ^ 1].to] == 0;
  }

  flow_type getEdgeFlow(int eid) {
    return es[eid].f;
  }
};

vector<int> a, b, any;
vector<vector<int>> g;
vector<vector<int>> gt;
vector<int> f;

void dfs(int v, vector<vector<int>> &g, vector<bool> &used) {
  used[v] = true;
  for (int id : g[v]) {
    int to = a[id] + b[id] - v;
    if (!used[to]) {
      dfs(to, g, used);
    }
  }
}

vector<bool> used2;
vector<bool> in_ans;

bool dfs2(int u, int v) {
  if (u == v) return true;
  if (used2[u]) return false;
  for (int id : g[u]) {
    if (!any[id]) continue;
    if (in_ans[id]) continue;
    if (dfs2(b[id], v)) {
      f[id]++;
      return true;
    }
  }
  return false;
}


class LRFlow {
  MaxFlow solver;
  vector<int> ids;
  vector<int> l;
  int n;
  long long totl;
public:
  LRFlow (int n) : solver(n + 2), n(n), totl(0) {
  }

  int addEdge(int a, int b, int l, int r) {
//    eprintf("%d %d %d %d\n", a, b, l, r);
    totl += l;
    solver.addEdge(n, b, l);
    solver.addEdge(a, n + 1, l);
    this->l.push_back(l);
    ids.push_back(solver.addEdge(a, b, r - l));
    return (int)ids.size() - 1;
  }

  long long getEdgeFlow(int id) {
    return l[id] + solver.getEdgeFlow(ids[id]);
  }

  bool solve(int s, int t) {
    solver.addEdge(t, s, 1e9);
    long long res = solver.getFlow(n, n + 1);
//    eprintf("%lld %lld\n", res, totl);
    return res == totl;
  }
};

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m, s, t;
  scanf("%d%d%d%d", &n, &m, &s, &t);
  --s, --t;

  g.resize(n);
  gt.resize(n);
  a.resize(m);
  b.resize(m);
  any.resize(m);

  for (int i = 0; i < m; i++) {
    scanf("%d%d%d", &a[i], &b[i], &any[i]);
    --a[i], --b[i];
    if (any[i]) {
      g[a[i]].push_back(i);
      gt[b[i]].push_back(i);
    }
  }

  vector<bool> useds(n), usedt(n);

  dfs(s, g, useds);
  dfs(t, gt, usedt);

  MaxFlow flow(n);
  vector<int> in_ans_id(m, -1);
  for (int i = 0; i < m; i++) {
//    if (!useds[a[i]] || !usedt[b[i]]) continue;
    if (any[i]) {
      in_ans_id[i] = flow.addEdge(a[i], b[i], 1);
    } else {
      in_ans_id[i] = flow.addEdge(a[i], b[i], 1e9);
    }
  }

  long long ans = flow.getFlow(s, t);
  assert(ans <= m);
  in_ans = vector<bool> (m);
  int cnt = 0;
  for (int i = 0; i < m; i++) {
    if (!any[i] || in_ans_id[i] == -1) continue;
    if (flow.isCut(in_ans_id[i])) {
      in_ans[i] = true;
      cnt++;
    }
  }

  assert(cnt == ans);

//  f = vector<int>(m);
//
//  for (int i = 0; i < m; i++) {
//    if (any[i]) {
//      used2 = vector<bool>(n);
//      f[i]++;
//      if (!dfs2(b[i], a[i])) {
//        used2 = vector<bool>(n);
//        assert(dfs2(s, a[i]));
//
//        used2 = vector<bool>(n);
//        assert(dfs2(b[i], t));
//      }
//    }
//  }

  LRFlow flow2(n);

  for (int i = 0; i < m; i++) {
    if (!any[i]) {
      in_ans_id[i] = -1;
    } else if (in_ans[i]) {
      in_ans_id[i] = flow2.addEdge(a[i], b[i], 2000, 2000);
    } else {
      in_ans_id[i] = flow2.addEdge(a[i], b[i], 1, (int)1e8);
    }
  }

  assert(flow2.solve(s, t));

  printf("%d\n", (int)ans);
  for (int i = 0; i < m; i++) {
    long long f = in_ans_id[i] == -1 ? 0 : flow2.getEdgeFlow(in_ans_id[i]);
    printf("%lld %lld\n", f, in_ans[i] ? f : (long long)1e9);
  }



  return 0;
}
