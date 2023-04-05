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

char MEM[800'000'000];
int mem_ptr;

void* operator new(size_t s) {
  void *ret = &MEM[mem_ptr];
  mem_ptr += s;
  return ret;
}
void operator delete(void *, size_t) noexcept {}
void operator delete(void *) noexcept {}

class MinCostMaxFlow {

  typedef int flow_type;
  const flow_type FLOW_INF = 1 << 30;
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
    return es[id].w;
    cost_type res = es[id].w - phi[es[id].to] + phi[es[id ^ 1].to];
    //assert(es[id].c > 0 && res >= 0);
    return res;
  }

  flow_type dijkstra(int s, int t, flow_type limit, bool neg) {
    vector<cost_type> d(n, COST_INF);
    vector<int> pe(n, -1);
    d[s] = 0;

    //priority_queue<pair<cost_type, int>> q;
    queue<int> q;
    vector<char> inq(n);
    q.push(s);
    inq[s] = 1;

    while (!q.empty()) {
      auto id = q.front();
      q.pop();
      inq[id] = 0;

      for (int e = head[id]; e != -1; e = es[e].next) {
        if (es[e].c == 0) continue;
        int to = es[e].to;
        ll ce = d[id] + get_cost(e);
        if (d[to] > ce) {
          d[to] = ce;
          if (!inq[to]) {
            q.push(to);
            inq[to] = 1;
          }
          //std::push_heap(q.begin(), q.end());
          pe[to] = e;
        }
      }
    }

    if (pe[t] == -1) return 0;
//    for (int i = 0; i < n; i++) {
//      phi[i] += d[i];
//    }

    flow_type res = FLOW_INF;
    res = min(res, limit);
    int v = t;
    cost_type pathCost = 0;
    while (v != s) {
      res = min(res, es[pe[v]].c);
      pathCost += es[pe[v]].w;
      v = es[pe[v] ^ 1].to;
    }
    if (neg && pathCost >= 0) return 0;
    v = t;
    while (v != s) {
      pushFlow(pe[v], res);
      v = es[pe[v] ^ 1].to;
    }
    return res;
  };

public:
  explicit MinCostMaxFlow(int n) : n(n), head(n, -1), phi(n, 0), cost(0) {}

  void pushFlow(int eid, flow_type val) {
    es[eid].f += val, es[eid].c -= val;
    es[eid ^ 1].f -= val, es[eid ^ 1].c += val;
    cost += es[eid].w * val;
  }

  void setCapacity(int eid, flow_type cap) {
    es[eid].c = cap;
  }

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

  int getFlowOnEdge(int eid) {
    return es[eid].f;
  }

  pair<flow_type, cost_type> getFlow(int s, int t, flow_type limit, bool neg) {
    flow_type res = 0;

    while (true) {
      flow_type cur = dijkstra(s, t, limit == -1 ? FLOW_INF : limit - res, neg);
      res += cur;
      if (cur == 0 || res == limit) break;
    }

    return {res, cost};
  }
};


int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    MinCostMaxFlow s(n + m + 2);
    vector<int> eids(k);
    vector<int> a(k), b(k); vector<ll> w(k);
    int S = n + m;
    int T = n + m + 1;
    for (int i = 0; i < k; i++) {
      scanf("%d%d%lld", &a[i], &b[i], &w[i]);
      a[i]--, b[i]--;
      eids[i] = s.addEdge(a[i], n + b[i], 1, -w[i]);
    }
    for (int i = 0; i < n; i++) {
      s.addEdge(S, i, 1, 0);
    }
    for (int i = 0; i < m; i++) {
      s.addEdge(n + i, T, 1, 0);
    }
    auto cur_flow = s.getFlow(S, T, -1, true);
    TIMESTAMP("first flow");
    for (int i = 0; i < k; i++) {
      int mem_ptr_backup = mem_ptr;
      if (s.getFlowOnEdge(eids[i])) {
        auto sc = s;
        int bid = sc.addEdge(T, S, cur_flow.first, 0);
        sc.pushFlow(bid, cur_flow.first);
        sc.pushFlow(eids[i] ^ 1, 1);
        sc.setCapacity(eids[i], 0);
        auto r = sc.getFlow(a[i], n + b[i], 1, false);
        //eprintf("i = %d, Pushed {%d, %lld}\n", i, r.first, r.second);
        auto fix = r.first == 0 ? r : sc.getFlow(S, T, 1, true);
        //eprintf("i = %d, Pushed fix {%d, %lld}\n", i, r.first, r.second);
        printf("%lld\n", (-cur_flow.second) - (-fix.second));
      } else {
        printf("0\n");
      }
      mem_ptr = mem_ptr_backup;
    }
  }

  return 0;
}
