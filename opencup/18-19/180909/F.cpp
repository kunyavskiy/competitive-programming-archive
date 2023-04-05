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

const int INF = (int)1.01e9;

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
//    eprintf("%d %d %lld\n", from, to, c);
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
    return res;
  }
};

class LRCirc {
  MaxFlow solver;
  vector<int> ids;
  vector<int> l;
  int n;
  long long totl;
public:
  LRCirc (int n) : solver(n + 2), n(n), totl(0) {
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

  bool solve() {
   long long res = solver.getFlow(n, n + 1);
//    eprintf("%lld %lld\n", res, totl);
    return res == totl;
  }
};


struct edge {
  int f, t, w;
};

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  //freopen("f.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {

    vector<edge> es;

    for (int i = 0; i < m; i++) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      u--; v--;
      es.push_back({u, v, w});
    }

    int l = 0;
    int r = INF;

    while (r - l > 1) {
      int mid = (l + r) / 2;

      LRCirc f(2 * n + 2);

      for (int i = 0; i < n; i++) {
        f.addEdge(2 * n, i, 0, INF);
        f.addEdge(i + n, 2 * n + 1, 0, INF);
        f.addEdge(i + n, i, 0, INF);
      }

      for (int i = 0; i < m; i++) {
        f.addEdge(es[i].f, es[i].t + n, 0, es[i].w);
      }

      f.addEdge(2 * n + 1, 2 * n, mid, INF);

      if (f.solve()) {
        l = mid;
      } else {
        r = mid;
      }
    }

    printf("%d\n", l);
  }

  return 0;
}
