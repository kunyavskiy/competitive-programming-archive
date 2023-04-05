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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


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

  typedef int flow_type;
  const flow_type FLOW_INF = 1LL << 30;

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
    while (bfs(s, t, 1)) {
      ptr = head;
      res += dfs(s, t, FLOW_INF, 1);
    }
    return res;
  }

  vector<int> getFree(int from, int to) {
    vector<int> res;
    for (int i = 0; i < n; i++) {
      if (d[i] != -1 && from <= i && i < to) {
        res.push_back(i);
      }
    }
    return res;
  }
};


int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    MaxFlow flow(2 * n + 2), flow2(2 * n + 2);
    int s = 2 * n;
    int t = s + 1;
    for (int i = 0; i < n; i++) {
      flow.addEdge(s, i, 1);
      flow.addEdge(i + n, t, 1);
      flow2.addEdge(s, i, 1);
      flow2.addEdge(i + n, t, 1);
    }

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      flow.addEdge(a, b + n, 1);
      flow2.addEdge(b, a + n, 1);
    }

    int ans = n - flow.getFlow(s, t) - 1;
    if (ans == 0) {
      printf("0\n\n");
      continue;
    }
    int ans2 = n - flow2.getFlow(s, t) - 1;
    assert(ans2 == ans);
    vector<int> v = flow.getFree(0, n);
    vector<int> v2 = flow2.getFree(0, n);
    v.insert(v.end(), v2.begin(), v2.end());

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    printf("%d\n", ans);
    for (int x : v) {
      printf("%d ", x + 1);
    }
    printf("\n");
  }

  return 0;
}
