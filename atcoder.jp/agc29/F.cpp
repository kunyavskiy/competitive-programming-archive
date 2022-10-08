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

class MaxFlow {

  typedef long long flow_type;
  const flow_type FLOW_INF = 1LL << 60;
public:

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

  explicit MaxFlow(int n) : n(n), head(n, -1) {}

  int addVertex() {
    int id = n++;
    head.push_back(-1);
    return id;
  }

  int addEdge(int from, int to, flow_type c, flow_type rc = 0) {
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


int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {

    MaxFlow flow(2 * n);
    vector<vector<int>> in_set(n);
    vector<vector<pair<int, int>>> id(n);

    bool have0 = false;

    for (int i = 0; i < n - 1; i++) {
      int c;
      scanf("%d", &c);
      for (int j = 0; j < c; j++) {
        int x;
        scanf("%d", &x);
        --x;
        in_set[x].push_back(i);
        if (x != 0) {
          id[i].emplace_back(x, flow.addEdge(i, x + (n - 1) - 1, 1));
        } else {
          id[i].emplace_back(0, -1);
          have0 = true;
        }
      }
    }
    for (int i = 0; i < n - 1; i++) {
      flow.addEdge(2 * n - 2, i, 1);
      flow.addEdge(i + (n - 1), 2 * n - 1, 1);
    }
    if (!have0 || flow.getFlow(2 * n - 2, 2 * n - 1) != n - 1) {
      printf("-1\n");
      continue;
    }
    vector<int> vin(n);
    vin[0] = 1;
    vector<int> active(n - 1);
    queue<int> q;
    for (int i : in_set[0]) {
      active[i] = true;
      q.push(i);
    }
    vector<pair<int, int>> ans(n - 1);
    for (int it = 0; it < n - 1; it++) {
      assert(!q.empty());
      int i = q.front();
      q.pop();
      int v = -1;
      int done = -1;
      for (auto x : id[i]) {
        if (x.second != -1 && flow.es[x.second].f) {
          v = x.first;
        } else if (vin[x.first]) {
          done = x.first;
        }
      }
      assert(v != -1);
      assert(done != -1);
      vin[v] = true;
      ans[i] = {v + 1, done + 1};
      for (int u : in_set[v]) {
        if (!active[u]) {
          q.push(u);
          active[u] = true;
        }
      }
    }
    for (auto x : ans) {
      printf("%d %d\n", x.first, x.second);
    }
  }

  return 0;
}
