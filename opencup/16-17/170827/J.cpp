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
//    eprintf("%d -> %d %lld\n", from, to, c);
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

struct item {
  int l, r, c;
};


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  vector<item> v(n);
  vector<int> pos;
  long long total = 0;
  for (auto& x : v) {
    scanf("%d%d%d", &x.l, &x.r, &x.c);
    pos.push_back(x.l);
    pos.push_back(x.r);
    total += x.c;
  }
  sort(pos.begin(), pos.end());
  pos.erase(unique(pos.begin(), pos.end()), pos.end());

  MaxFlow flow(n + pos.size() + 1);
  int s = n + pos.size() - 1;
  int t = s + 1;

  for (int i = 0; i < n; i++) {
    flow.addEdge(s, i, v[i].c);
    for (int j = 0; j + 1 < (int)pos.size(); j++) {
      if (v[i].l <= pos[j] && pos[j + 1] <= v[i].r) {
        flow.addEdge(i, n + j, pos[j + 1] - pos[j]);
      }
    }
  }
  for (int j = 0; j + 1 < (int)pos.size(); j++) {
    flow.addEdge(n + j, t, (pos[j + 1] - pos[j]) * 1LL * m);
  }

  if (flow.getFlow(s, t) == total) {
    printf("YES\n");
  } else {
    printf("NO\n");
  }


  return 0;
}
