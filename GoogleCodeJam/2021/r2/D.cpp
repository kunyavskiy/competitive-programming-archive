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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

using namespace std;

typedef long long ll;
typedef long double ld;

void PreCalc() {
}

class MinCostMaxFlow {

  typedef int flow_type;
  const flow_type FLOW_INF = 1 << 30;
  typedef int cost_type;
  const cost_type COST_INF = 1 << 30;

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
    q.push({-d[s], s});

    while (!q.empty()) {
      auto x = q.top();
      q.pop();

      int id = x.second;
      if (x.first != -d[id]) continue;

      for (int e = head[id]; e != -1; e = es[e].next) {
        if (es[e].c == 0) continue;
        int to = es[e].to;
        if (d[to] > d[id] + get_cost(e)) {
          d[to] = d[id] + get_cost(e);
          q.push({-d[to], to});
          pe[to] = e;
        }
      }
    }

    int should_be_total_cost = d[t] + phi[t] - phi[s];

    for (int i = 0; i < n; i++) {
      phi[i] += d[i];
    }

    if (pe[t] == -1) return 0;

    flow_type res = FLOW_INF;
    if (limit > 0) res = min(res, limit);
    int v = t;
    cost_type total_cost = 0;
    while (v != s) {
      res = min(res, es[pe[v]].c);
      total_cost += es[pe[v]].w;
      v = es[pe[v] ^ 1].to;
    }
    assert(total_cost == should_be_total_cost);
    if (total_cost >= 0) return 0;
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

  void changePhi(int v, int value) {
    phi[v] += value;
  }

  pair<flow_type, cost_type> getFlow(int s, int t) {
    flow_type res = 0;

    while (true) {
      flow_type cur = dijkstra(s, t, -1);
      res += cur;
      if (cur == 0) break;
    }

    return {res, cost};
  }
};


void solve() {
  int r, c, F, S;
  scanf("%d%d%d%d", &r, &c, &F, &S);
  MinCostMaxFlow solver(r * c + 2);

  char from[20][20];
  char to[20][20];
  for (int i = 0; i < r; i++) {
    scanf(" %s", from[i]);
  }
  for (int i = 0; i < r; i++) {
    scanf(" %s", to[i]);
  }

  int s = r * c;
  int t = r * c + 1;

  solver.changePhi(s, F);
  solver.changePhi(t, -F);

  auto encode = [&](int i, int j) { return i * c + j; };

  int ans = 0;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      if (i + 1 != r) {
        solver.addEdge(encode(i, j), encode(i + 1, j), 1e9, S);
        solver.addEdge(encode(i+1, j), encode(i, j), 1e9, S);
      }
      if (j + 1 != c) {
        solver.addEdge(encode(i, j), encode(i, j + 1), 1e9, S);
        solver.addEdge(encode(i, j + 1), encode(i, j), 1e9, S);
      }
      if (from[i][j] == 'M' && to[i][j] == 'G') {
        ans += F;
        solver.addEdge(s, encode(i, j), 1, -F);
      }
      if (from[i][j] == 'G' && to[i][j] == 'M') {
        ans += F;
        solver.addEdge(encode(i, j), t, 1, -F);
      }
    }
  }
  eprintf("%d\n", ans);
  ans += solver.getFlow(s, t).second;
  printf("%d\n", ans);
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  PreCalc();
  TIMESTAMP(PreCalc);

  char buf[1000];
  int testNum;
  fgets(buf, sizeof buf, stdin);
  sscanf(buf, "%d", &testNum);

  for (int testId = 1; testId <= testNum; testId++) {
    if (testId <= 20 || testId >= testNum - 20 || testId % 10 == 0)
      TIMESTAMPf("Test %d", testId);
    printf("Case #%d: ", testId);
    solve();
  }

  TIMESTAMP(end);
  return 0;
}
