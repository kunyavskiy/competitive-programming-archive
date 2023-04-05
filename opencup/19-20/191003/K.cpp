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
#include <numeric>

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

typedef long long flow_type;
const flow_type FLOW_INF = 1LL << 60;

class MaxFlow {


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

  int getFlowOnEdge(int eid) {
    return es[eid].f;
  }
};

class LRFlow {
  MaxFlow flow;
  vector<int> eids;
  vector<flow_type> lf;
  int n;
public:
  explicit LRFlow(int n) : flow(n + 2), n(n) {}
  int addEdge(int from, int to, flow_type l, flow_type r) {
    eprintf("%d -> %d [%lld..%lld)\n", from, to, l, r);
    eids.push_back(flow.addEdge(from, to, r - l));
    lf.push_back(l);
    flow.addEdge(n, to, l);
    flow.addEdge(from, n + 1, l);
    return eids.size() - 1;
  }

  bool getFlow(int s, int t) {
    flow.addEdge(t, s, FLOW_INF);
    flow_type total_flow = accumulate(lf.begin(), lf.end(), 0LL);
    return flow.getFlow(n, n + 1) == total_flow;
  }

  flow_type getFlowOnEdge(int eid) {
    return lf[eid] + flow.getFlowOnEdge(eids[eid]);
  }
};


struct lecture {
  int l, r, ty;
};

void mark(vector<int> &ans, const vector<lecture>& v, const vector<int> &ids, int shift, int cnt) {
  vector<int> s;
  for (int i = 0; i < cnt; i++) {
    s.push_back(i + shift);
  }
  vector<pair<int, int>> ev;
  for (int id : ids) {
    const lecture& l = v[id];
    ev.emplace_back(l.l, id + 1);
    ev.emplace_back(l.r, -(id + 1));
  }
  sort(ev.begin(), ev.end());
  for (auto [pos, id] : ev) {
    if (id > 0) {
      id--;
      assert(!s.empty());
      ans[id] = s.back();
      s.pop_back();
    } else {
      id = -id;
      --id;
      s.push_back(ans[id]);
    }
  }
}

void solve_test() {
  int n, m, x, y;
  scanf("%d%d%d%d", &n, &m, &x, &y);
  vector<lecture> v(n + m);
  vector<int> ts;
  for (int i = 0; i < n; i++) {
    scanf("%d%d", &v[i].l, &v[i].r);
    v[i].ty = 0;
    ts.push_back(v[i].l);
    ts.push_back(v[i].r);
  }
  for (int i = n; i < n + m; i++) {
    scanf("%d%d", &v[i].l, &v[i].r);
    v[i].ty = 1;
    ts.push_back(v[i].l);
    ts.push_back(v[i].r);
  }
  n += m;
  ts.push_back(0);
  ts.push_back(1e9);
  sort(ts.begin(), ts.end());
  ts.erase(unique(ts.begin(), ts.end()), ts.end());
  LRFlow flow(ts.size());
  vector<int> eids(n);

  for (lecture &l : v) {
    l.l = lower_bound(ts.begin(), ts.end(), l.l) - ts.begin();
    l.r = lower_bound(ts.begin(), ts.end(), l.r) - ts.begin();
  }

  for (int i = 0; i < n; i++) {
    eids[i] = flow.addEdge(v[i].l, v[i].r, !v[i].ty, 1);
  }

  int sink = ts.size() - 1;

  flow.addEdge(0, 1, x, x);
  flow.addEdge(sink - 1, sink, x, x);

  for (int i = 1; i < sink - 1; i++) {
    int cnt[2];
    cnt[0] = cnt[1] = 0;
    for (const lecture& l : v) {
      if (l.l <= i && i < l.r) {
        cnt[l.ty]++;
      }
    }
    int min_done = max(0, cnt[1] - y);
    int max_free = x - min_done - cnt[0];
    eprintf("i = %d, min_done = %d, max_free = %d\n", i, min_done, max_free);
    if (max_free < 0) {
      printf("NO\n");
      return;
    }
    flow.addEdge(i, i + 1, 0, max_free);
  }

  if (!flow.getFlow(0, sink)) {
    printf("NO\n");
    return;
  }

  vector<int> part[2];
  for (int i = 0; i < n; i++) {
    if (flow.getFlowOnEdge(eids[i])) {
      part[0].push_back(i);
    } else {
      part[1].push_back(i);
    }
  }

  vector<int> ans(n);
  mark(ans, v, part[0], 1, x);
  mark(ans, v, part[1], x + 1, y);

  printf("YES\n");
  for (int i : ans) {
    printf("%d ", i);
  }
  printf("\n");
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) solve_test();

  return 0;
}
