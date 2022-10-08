#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>

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
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
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


void PreCalc() {
}

struct ladder {
  int x, y1, y2;
};

void solve() {
  int n, h;
  scanf("%d%d", &n, &h);
  MaxFlow flow(n + 2);
  vector<int> cur(h + 1, -1);
  vector<ladder> v(n);
  for (ladder &l: v) {
    scanf("%d%d%d", &l.x, &l.y1, &l.y2);
  }
  sort(v.begin(), v.end(), [](const ladder& a, const ladder&b) {
    return a.x < b.x;
  });

  const ll INF = 1LL << 50;

  for (int i = 0; i < n; i++) {
    if (v[i].y1 == 0) {
      flow.addEdge(n, i, INF, INF);
    }
    if (v[i].y2 == h) {
      flow.addEdge(n + 1, i, INF, INF);
    }
    int last = -1;
    int lstart = -1;
    for (int j = v[i].y1;; j++) {
      if (j == v[i].y2 || cur[j] != last) {
        if (last != -1) {
          ll cost = j - lstart;
          flow.addEdge(last, i, cost, cost);
        }
        if (j == v[i].y2) break;
        last = cur[j];
        lstart = j;
      }
      cur[j] = i;
    }
  }

  ll ans = flow.getFlow(n, n + 1);
  if (ans >= INF) {
    ans = -1;
  }
  printf("%lld\n", ans);
}


int main() {
#ifdef LOCAL
//  freopen("c.in", "r", stdin);
//  freopen("c.out", "w", stdout);
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
