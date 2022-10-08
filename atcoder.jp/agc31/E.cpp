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

class MinCostMaxFlow {
public:
  typedef long long flow_type;
  typedef long long cost_type;
  const flow_type FLOW_INF = 1LL << 60;
  const cost_type COST_INF = 1LL << 60;
private:
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

class MinCostLRFlow {
  MinCostMaxFlow flow;
  MinCostMaxFlow::flow_type need;
public:

  int n;
  MinCostLRFlow(int n) : flow(n + 2), need(0), n(n) {}

  MinCostMaxFlow::cost_type getFlow(int s, int t) {
    flow.addEdge(t, s, 10000, 0);
    auto res = flow.getFlow(n, n + 1);
    if (res.first != need) {
      return -1;
    }
    return res.second;
  }

  void addEdge(int from, int to, int l, int r, MinCostMaxFlow::cost_type cost) {
    assert(0 <= from && from < n);
    assert(0 <= to && to < n);
    assert(0 <= l && l <= r);
    eprintf("[%d, %d] from %d to %d, cost = %lld\n", from, to, l, r, cost);
    if (l < r) {
      flow.addEdge(from, to, r - l, cost);
    }
    if (l) {
      flow.addEdge(n, to, l, cost);
      flow.addEdge(from, n + 1, l, 0);
      need += l;
    }
  }
};

struct point {
  int x, y;
  ll w;
};

struct restriction {
  char ty;
  int a, b;
};

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<point> ps(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d%lld", &ps[i].x, &ps[i].y, &ps[i].w);
    }
    int m;
    scanf("%d", &m);
    vector<restriction> rs(m);
    for (int i = 0; i < m; i++) {
      scanf(" %c%d%d", &rs[i].ty, &rs[i].a, &rs[i].b);
    }

    vector<int> xs, ys;
    ll sum = 0;
    for (const auto& p : ps) {
      xs.push_back(p.x);
      ys.push_back(p.y);
      sum += p.w;
    }

    for (const auto& r : rs) {
      if (r.ty == 'U' || r.ty == 'D') {
        ys.push_back(r.a);
      } else {
        xs.push_back(r.a);
      }
    }

    xs.push_back(0);
    ys.push_back(0);
    xs.push_back(101);
    ys.push_back(101);

    sort(xs.begin(), xs.end()), xs.erase(unique(xs.begin(), xs.end()), xs.end());
    sort(ys.begin(), ys.end()), ys.erase(unique(ys.begin(), ys.end()), ys.end());

    ll ans = 0;
    for (int remove = 0; remove <= n; remove++) {
      eprintf("remove = %d\n", remove);
      MinCostLRFlow flow(2 + 2 * (int)xs.size() + 2 * (int)ys.size());
      int x_start = 0;
      int y_start = x_start + (int)xs.size();
      int x_sum_start = y_start + (int)ys.size();
      int y_sum_start = x_sum_start + (int)xs.size();
      int s = y_sum_start + (int)ys.size();
      int t = s + 1;
      assert(t == flow.n - 1);
      for (const auto &p : ps) {
        int x = lower_bound(xs.begin(), xs.end(), p.x) - xs.begin();
        int y = lower_bound(ys.begin(), ys.end(), p.y) - ys.begin();
        flow.addEdge(x, y + y_start, 0, 1, p.w);
      }

      bool fail = false;

      flow.addEdge(s, y_sum_start - 1, remove, remove, 0);
      for (int i = 0; i < (int)xs.size(); i++) {
        flow.addEdge(x_sum_start + i, x_start + i, 0, n, 0);
        if (i != 0) {
          int lf = 0;
          int rg = n;

          int cnt = 0;
          for (const auto &p : ps) {
            if (p.x <= xs[i - 1]) {
              cnt++;
            }
          }

          for (const auto& r : rs) {
            if (r.ty == 'L' && r.a >= xs[i - 1]) {
              lf = max(lf, cnt - r.b);
            } else if (r.ty == 'R' && r.a <= xs[i]) {
              rg = min(rg, r.b + cnt - (n - remove));
            }
          }

          if (lf > rg) {
            fail = true;
          } else {
            flow.addEdge(i + x_sum_start, i - 1 + x_sum_start, lf, rg, 0);
          }
        }
      }

      for (int i = 0; i < (int)ys.size(); i++) {
        flow.addEdge(y_start + i, y_sum_start + i, 0, n, 0);
        if (i != 0) {
          int lf = 0;
          int rg = n;
          int cnt = 0;
          for (const auto &p : ps) {
            if (p.y <= ys[i - 1]) {
              cnt++;
            }
          }

          for (const auto& r : rs) {
            if (r.ty == 'D' && r.a >= ys[i - 1]) {
              lf = max(lf, cnt - r.b);
            } else if (r.ty == 'U' && r.a <= ys[i]) {
              rg = min(rg, r.b + cnt - (n - remove));
            }
          }
          if (lf > rg) {
            fail = true;
          } else {
            flow.addEdge(i + y_sum_start - 1, i + y_sum_start, lf, rg, 0);
          }
        }
      }
      flow.addEdge(y_sum_start + (int)ys.size() - 1, t, 0, n, 0);

      if (!fail) {
        ll res = flow.getFlow(s, t);
        eprintf("res = %lld\n", res);
        if (res != -1) {
          ans = max(ans, sum - res);
        }
      }
    }
    printf("%lld\n", ans);

  }

  return 0;
}
