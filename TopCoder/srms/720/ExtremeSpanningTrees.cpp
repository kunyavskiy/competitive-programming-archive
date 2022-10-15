#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;

class MinCostMaxFlow {

  typedef long long flow_type;
  const flow_type FLOW_INF = 1LL << 60;
  typedef long long cost_type;
  const cost_type COST_INF = 1LL << 60;

  struct Edge {
    int to, next;
    flow_type f, c;
    cost_type w;
  };

  int n;
  vector<int> head;
  vector<cost_type> phi;
  vector<Edge> es;
  cost_type cost;

  cost_type get_cost(int id) {
    cost_type res = es[id].w + phi[es[id].to] - phi[es[id ^ 1].to];
    assert(es[id].c > 0 && res >= 0);
    return res;
  }

  void pushFlow(int eid, flow_type val) {
    es[eid].f += val, es[eid].c -= val;
    es[eid ^ 1].f -= val, es[eid ^ 1].c += val;
    cost += es[eid].w * val;
  }


  flow_type dijkstra(int s, int t, flow_type limit) {
    vector<cost_type > d(n, COST_INF);
    vector<int> pe(n, -1);
    d[s] = 0;

    priority_queue<pair<cost_type, int>> q;
    q.push({d[s], s});

    while (!q.empty()) {
      auto x = q.top();
      q.pop();

      int id = x.second;
      if (x.first != d[id]) continue;

      for (int e = head[id]; e != -1; e = es[e].next) {
        if (es[e].c == 0) continue;
        int to = es[e].to;
        if (d[to] > d[id] + get_cost(e)) {
          d[to] = d[id] + get_cost(e);
          q.push({d[to], to});
          pe[to] = e;
        }
      }
    }

    for (int i = 0; i < n; i++) {
      phi[i] += d[i];
    }

    if (pe[t] == -1) return 0;

    flow_type res = FLOW_INF;
    if (limit > 0) res = min(res, limit);
    int v = t;
    while (v != s) {
      res = min(res, es[pe[v]].c);
      v = es[pe[v] ^ 1].to;
    }
    v = t;
    while (v != s) {
      pushFlow(pe[v], res);
      v = es[pe[v] ^ 1].to;
    }
    return res;
  };

public:
  explicit MinCostMaxFlow(int n) : n(n), head(n, -1), phi(n, 0), cost(0) {}

  int addVertex() {
    int id = n++;
    head.push_back(-1);
    phi.push_back(0);
    return id;
  }

  int addEdge(int from, int to, flow_type c, cost_type w) {
    int id = (int) es.size();
    es.push_back({to, head[from], 0, c, w});
    head[from] = id;
    es.push_back({from, head[to], 0, 0, -w});
    head[to] = id ^ 1;
    return id;
  }

  pair<flow_type, cost_type> getFlow(int s, int t, flow_type k = -1) {
    flow_type res = 0;

    while (true) {
      flow_type cur = dijkstra(s, t, k - res);
      res += cur;
      if (cur == 0 || res == k) break;
    }

    return {res, cost};
  }

  void forcePhi(int v, cost_type val) {
      phi[v] = val;
  }
};



class ExtremeSpanningTrees {
  vector<vector<int>> g;
  vector<int> a, b, w;

  void buildTree(vector<int> m) {
      int n = m.size() + 1;
      g = vector<vector<int>>(n);
      for (int id : m) {
        g[a[id]].push_back(id);
        g[b[id]].push_back(id);
      }
  }

  bool dfs(int u, int v, int p, int side, int id, MinCostMaxFlow &flow) {
    if (u == v) {
      return true;
    }
    for (int i : g[u]) {
      int to = a[i] + b[i] - u;
      if (to == p) continue;
      if (dfs(to, v, u, side, id, flow)) {
        if (side == 1) {
          flow.addEdge(i, id, 1, w[id] - w[i]);
        } else {
          flow.addEdge(id, i, 1, w[i] - w[id]);
        }
        return true;
      }
    }
    return false;
  }



public:
  ll minTime(vector<int> a, vector<int> b, vector<int> w, vector<int> m1, vector<int> m2) {
    int m = a.size();
    MinCostMaxFlow flow = MinCostMaxFlow(m + 2);
    this->a = a;
    this->b = b;
    this->w = w;
    buildTree(m1);
    for (int i = 0; i < (int)a.size(); i++) {
      dfs(a[i], b[i], -1, 1, i, flow);
    }
    buildTree(m2);
    for (int i = 0; i < (int)a.size(); i++) {
      dfs(a[i], b[i], -1, -1, i, flow);
    }

    for (int i : m1) {
      flow.addEdge(m, i, 1, 0);
    }
    for (int i : m2) {
      flow.addEdge(i, m + 1, 1, 0);
    }

    for (int i = 0; i < m; i++) {
      flow.forcePhi(i, -w[i]);
    }

    return -flow.getFlow(m, m + 1).second;
  }
};










