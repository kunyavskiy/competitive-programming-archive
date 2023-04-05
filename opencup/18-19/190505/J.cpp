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
public:
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

  void addCap(int eid, int c) {
    es[eid].c += c;
  }

  flow_type getFlow(int eid) {
    return es[eid].f;
  }

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

  void multiplyFlow(flow_type coef) {
    for (auto& e : es) {
      e.f *= coef;
      e.c *= coef;
    }
  }
};


int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    MaxFlow flow(2 * n + 1);
    int s = 2 * n - 1;
    int t = 2 * n;
    int child_start = 0;
    int teacher_start = n - 1;
    vector<int> cid(n - 1);
    vector<int> tid(n);
    vector<int> eid(m);
    for (int i = 0; i < n - 1; i++) {
      cid[i] = flow.addEdge(s, child_start + i, 1);
    }
    for (int i = 0; i < n; i++) {
      tid[i] = flow.addEdge(teacher_start + i, t, 1);
    }

    vector<vector<pair<int, int>>> children(n);

    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      eid[i] = flow.addEdge(child_start + a, teacher_start + b, 1);
      children[b].emplace_back(a, i);
    }

    int first = flow.getFlow(s, t);
    if (first != n - 1) {
      printf("-1\n");
      continue;
    }

    vector<pair<int, int>> teacher(n - 1);
    vector<int> answer(m);
    for (int i = 0; i < m; i++) {
      if (flow.getFlow(eid[i]) == 1) {
        int t = flow.es[eid[i]].to - teacher_start;
        int s = flow.es[eid[i] ^ 1].to - child_start;
        teacher[s] = {t, i};
        answer[i] = n - 1;
      }
    }

    int not_used_teacher = -1;
    for (int i = 0; i < n; i++) {
      if (flow.getFlow(tid[i]) == 0) {
        assert(not_used_teacher == -1);
        not_used_teacher = i;
      }
    }


    vector<bool> used(n);

    function<int(int)> dfs = [&](int v) {
      used[v] = true;
      int got = 0;
      for (auto &[child, id] : children[v]) {
        if (!used[teacher[child].first]) {
          int from_child = dfs(teacher[child].first);
          answer[id] += from_child + 1;
          answer[teacher[child].second] -= from_child;
          got += from_child + 1;
        }
      }
      return got;
    };

    if (dfs(not_used_teacher) != n - 1) {
      printf("-1\n");
      continue;
    }

#ifdef LOCAL
    vector<int> fc(n - 1);
    vector<int> tt(n);
    for (int i = 0; i < n; i++) {
      for (auto [c, id] : children[i]) {
        fc[c] += answer[id];
        tt[i] += answer[id];
        assert(answer[id] >= 0);
      }
    }
    for (int x : fc) assert(x == n);
    for (int x : tt) assert(x == n - 1);
#endif

    for (int x : answer) {
      printf("%d\n", x);
    }

  }

  return 0;
}
