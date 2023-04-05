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

  typedef long long flow_type;
  const flow_type FLOW_INF = 1LL << 60;

  struct Edge {
    int to, next;
    flow_type f, c;
  };

  public:
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
    for (flow_type i = FLOW_INF; i >= 1; i /= 2) {
      while (bfs(s, t, i)) {
        ptr = head;
        res += dfs(s, t, FLOW_INF, i);
      }
    }
    return res;
  }
};

char buf[11];

int main() {
#ifdef LOCAL
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
#endif

  int n;
  scanf("%d", &n);

  map<string, int> names;

  int m = 0;

//  vector<int> ap;
//  vector<int> ver;
//
  map<pair<int, int>, int> vap;

  for (int i = 0; i < n; i++) {
    int k;
    scanf("%s%d", buf, &k);
    string s = buf;
    names[s] = i;
    for (int j = 0; j < k; j++) {
      int v;
      scanf("%d", &v);
      vap[{i, v}] = m;
      m++;
    }
  }


  int k;
  scanf("%d", &k);

  MaxFlow maxFlow(k + n + m + 2);

  vector<bool> used(m);

  for (int i = 0; i < k; i++) {

    maxFlow.addEdge(n + k + m, i, 1);

    int x;
    scanf("%d", &x);
    for (int j = 0; j < x; j++) {
      int v;
      scanf("%s%d", buf, &v);
      string s = buf;
      int q = vap[{names[s], v}];
      used[q] = true;
      maxFlow.addEdge(i, k + q, 1);
    }

  }
  
  for (int i = 0; i < m; i++) {
    if (!used[i]) {
      maxFlow.addEdge(n + k + m, k + i, 1);
    }
  }

  vector<int> ids(m);

  for (auto p : vap) {
    ids[p.second]=maxFlow.addEdge(k + p.second, k + m + p.first.first, 1);
  }

  for (int i = 0; i < n; i++) {
    maxFlow.addEdge(k + m + i, k + m + n + 1, 1);
  }

  int f = maxFlow.getFlow(k + m + n, k + m + n + 1);

  if (f < n) {
    cout << "No\n";
  } else {
    cout << "Yes\n";
    vector<int> vv(n);
    for (auto p : vap) {
      if (maxFlow.es[ids[p.second]].f) {
        vv[p.first.first] = p.first.second;
      }
    }

    for (int i = 0; i < n; i++) {
      cout << vv[i] << " ";
    }

  }

  return 0;
}
