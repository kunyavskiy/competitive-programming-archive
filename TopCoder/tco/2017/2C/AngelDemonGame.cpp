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
    cost_type res = es[id].w - phi[es[id].to] + phi[es[id ^ 1].to];
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
};


class AngelDemonGame {

public:
  string winner(vector<string> _g, int A, int D) {
    int n = (int) _g.size();
    MinCostMaxFlow flow(n);

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (_g[i][j] == 'Y') {
          flow.addEdge(i, j, 1, 0);
        } else {
          flow.addEdge(i, j, 1, 1);
        }
      }
    }

    auto x = flow.getFlow(0, n - 1, D + 1);

    if (x.first <= D) {
      return "Demon";
    } else if (x.second <= A) {
      return "Angel";
    } else {
      return "Unknown";
    }
  }
};










