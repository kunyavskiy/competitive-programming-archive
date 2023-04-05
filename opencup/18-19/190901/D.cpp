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

const int INF = (int)1.01e9;

struct Edge {
  int to, cap, flow;
};

struct Graph {
  int n;
  vector<vector<int> > e;
  vector<Edge> edges;
  vector<int> d, c;
  int S, T;

  Graph() {}
  Graph(int _n) {
    n = _n;
    e.resize(n);
  }

  void addEdge(int from, int to, int cap) {
    e[from].push_back(edges.size());
    edges.push_back(Edge({to, cap, 0}));
    e[to].push_back(edges.size());
    edges.push_back(Edge({from, 0, 0}));
  }

  bool bfs() {
    d.assign(n, INF);
    c.assign(n, 0);
    vector<int> q(n);
    int qL = 0, qR = 0;
    d[S] = 0;
    q[qR++] = S;
    while (qL < qR) {
      int v = q[qL++];
      for (int i = 0; i < (int)e[v].size(); i++) {
        Edge cur = edges[e[v][i]];
        if (d[cur.to] > d[v] + 1 && cur.flow < cur.cap) {
          d[cur.to] = d[v] + 1;
          q[qR++] = cur.to;
        }
      }
    }
    return d[T] != INF;
  }

  int dfs(int v, int flow) {
    if (v == T) return flow;
    if (flow == 0) return 0;
    for (int &i = c[v]; i < (int)e[v].size(); i++) {
      Edge cur = edges[e[v][i]];
      if (d[cur.to] != d[v] + 1) continue;
      int pushed = dfs(cur.to, min(flow, cur.cap - cur.flow));
      if (pushed > 0) {
        edges[e[v][i]].flow += pushed;
        edges[e[v][i] ^ 1].flow -= pushed;
        return pushed;
      }
    }
    return 0;
  }

  ll flow() {
    ll flow = 0;
    while (bfs()) {
      while (int pushed = dfs(S, INF)) {
        flow += pushed;
      }
    }
    return flow;
  }

  void clear_flow() {
    for (auto &ed : edges) {
      ed.flow = 0;
    }
  }

  vector<int> min_cut() {
    bfs();
    vector<int> res(n);
    for (int i = 0; i < n; i++) res[i] = d[i] == INF;
    return res;
  }
};

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif

  int T;
  cin >> T;
  for (int test = 1; test <= T; test++) {
    int n, m;
    cin >> n >> m;
    string s;
    getline(cin, s);
    vector<string> a(3 + 4 * n);
    for (int i = 0; i < (int)a.size(); i++) {
      getline(cin, a[i]);
    }
//    for (auto s : a) db(s);

    auto ok_cell = [&](int x, int y) {
      return 0 <= x && x < n && 0 <= y && y < m;
    };
    auto get_cell = [&](int i, int j) {
      return make_pair(2 + 2 * (j % 2) + 4 * i, 4 + 6 * j);
    };
    auto has_edge = [&](int i, int j, int ni, int nj) {
      if (!(ok_cell(i, j) && ok_cell(ni, nj))) return false;
      auto p = get_cell(i, j);
      auto q = get_cell(ni, nj);
      return a[(p.first + q.first) / 2][(p.second + q.second) / 2] == ' ';
    };
    auto get_num = [&](int i, int j) {
      return i * m + j;
    };

//    for (auto v : a) {
//      db(v);
//    }

    vector<int> vct;
    vector<pair<int, int>> ed;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        auto pos = get_cell(i, j);
//        db3(pos.first, pos.second, a[pos.first][pos.second]);
        if (a[pos.first][pos.second] == '*') {
          vct.push_back(get_num(i, j));
        }

        vector<pair<int, int>> neib;
        neib.push_back({i + 1, j});
        neib.push_back({i, j + 1});
        if (j % 2 == 0) neib.push_back({i - 1, j + 1});
        if (j % 2 == 1) neib.push_back({i + 1, j + 1});

        for (auto np : neib) {
          if (has_edge(i, j, np.first, np.second)) {
            ed.push_back({get_num(i, j), get_num(np.first, np.second)});
          }
        }
      }
    }

    vector<char> good(n * m);
    for (int x : vct) good[x] = 1;

    vector<vector<int>> ee(n * m);
    for (auto o : ed) {
      ee[o.first].push_back(o.second);
      ee[o.second].push_back(o.first);
    }
    ll ans = 0;
    vector<int> used(n * m, -1);
    for (int s = 0; s < n * m; s++) {
      if (!good[s]) continue;
      if (used[s] != -1) continue;
      used[s] = s;
      vector<int> nvct;
      nvct.push_back(s);
      for (int j = 0; j < (int)nvct.size(); j++) {
        int v = nvct[j];
        for (auto to : ee[v]) {
          if (used[to] == -1) {
            used[to] = s;
            nvct.push_back(to);
          }
        }
      }
      sort(nvct.begin(), nvct.end());
//      dbv(nvct);


      int k = nvct.size();
      Graph gr(k);
      for (auto o : ed) {
        if (used[o.first] != s) continue;

        o.first = lower_bound(nvct.begin(), nvct.end(), o.first) - nvct.begin();
        o.second = lower_bound(nvct.begin(), nvct.end(), o.second) - nvct.begin();

        gr.addEdge(o.first, o.second, 1);
        gr.addEdge(o.second, o.first, 1);
//        db2(o.first, o.second);
      }
      vector<vector<pair<int, int>>> e(k, vector<pair<int, int>>());
      vector<int> pr(k, 0);
      for (int i = 1; i < k; i++) {
        gr.clear_flow();
        gr.S = i;
        gr.T = pr[i];
        int flow = gr.flow();
//        db(flow);
        vector<int> cut = gr.min_cut();
        for (int j = i + 1; j < k; j++) {
          if (cut[j] == cut[i] && pr[j] == pr[i]) {
            pr[j] = i;
          }
        }
        e[i].push_back({pr[i], flow});
        e[pr[i]].push_back({i, flow});
      }

      function<void(int, int, int)> dfs = [&](int v, int pr, int flow) {
//        db2(v, flow);
        if (flow != INF) {
          ans += flow;
        }
        for (auto o : e[v]) {
          if (o.first == pr) continue;
          dfs(o.first, v, min(flow, o.second));
        }
      };
      for (int i = 0; i < k; i++) {
        dfs(i, -1, INF);
      }
    }

    printf("Case #%d: %lld\n", test, ans / 2);
  }

  return 0;
}
