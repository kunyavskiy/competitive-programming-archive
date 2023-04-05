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
    for (flow_type i = FLOW_INF; i >= 1; i /= 2) {
      while (bfs(s, t, i)) {
        ptr = head;
        res += dfs(s, t, FLOW_INF, i);
      }
    }
    return res;
  }

  flow_type flowOnEdge(int id) {
    return es[id].f;
  }
};

class LRFlow {
  MaxFlow f;
  int S, T;
  vector<int> lf;
  vector<int> id;
  int tot;
public:
  LRFlow(int n) : f(n + 2), S(n), T(n + 1), tot(0) { }

  int addVertex() {
    return f.addVertex();
  }

  int addEdge(int a, int b, int l, int r) {
//    eprintf("%d %d %d %d\n", a, b, l, r);
    int res = id.size();
    id.push_back(f.addEdge(a, b, r - l));
    lf.push_back(l);
    if (l) {
      f.addEdge(S, b, l);
      f.addEdge(a, T, l);
      tot += l;
    }
    return res;
  }

  int flowOnEdge(int x) {
    return lf[x] + f.flowOnEdge(id[x]);
  }

  bool checkFlow(int s, int t) {
    f.addEdge(t, s, 1 << 30);
    return f.getFlow(S, T) == tot;
  }
};


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m, k;
  while (scanf("%d%d%d", &n, &m, &k) == 3) {
    map<pair<int, int>, int> singer_lang, song_lang;
    LRFlow f(n + m + 2);
    int s = n + m;
    int t = n + m + 1;
    for (int i = 0; i < n; i++) {
      f.addEdge(s, i, 1, 1 << 30);
    }
    for (int i = 0; i < m; i++) {
      f.addEdge(n + i, t, 1, 1 << 30);
    }
    vector<int> ids(k);
    for (int i = 0; i < k; i++) {
      int a, b, c;
      scanf("%d%d%d", &a, &b, &c);
      --a, --b;
      int lid, rid;
      if (singer_lang.find({a, c}) == singer_lang.end()) {
        lid = f.addVertex();
        singer_lang[{a, c}] = lid;
        f.addEdge(a, lid, 0, 1);
      } else {
        lid = singer_lang[{a, c}];
      }
      if (song_lang.find({c, b}) == song_lang.end()) {
        rid = f.addVertex();
        song_lang[{c, b}] = rid;
        f.addEdge(rid, n + b, 0, 1);
      } else {
        rid = song_lang[{c, b}];
      }

      ids[i] = f.addEdge(lid, rid, 0, 1);
    }
    if (!f.checkFlow(s, t)) {
      printf("-1\n");
    } else {
      vector<int> res;
      for (int i = 0; i < k; i++) {
        if (f.flowOnEdge(ids[i])) {
          res.push_back(i + 1);
        }
      }
      printf("%d\n", (int)res.size());
      for (int x : res) {
        printf("%d ", x);
      }
      printf("\n");
    }
//    break;
  }

  return 0;
}
