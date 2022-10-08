#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#include <cstring>
#include <queue>
#include <functional>
#include <algorithm>
#include <set>

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

void PreCalc() {
}

class highways {
public:

  struct edge { int u; int v; int c; };

  static const int MAXN = 11000;
  static const int MAXM = 40000;

  vector<int> g[MAXN];

  int color[MAXM];
  int comp[MAXN];
  bool used[MAXN];

  int a[MAXM];
  int b[MAXM];
  int n, m, colors;

  bool usedcol[MAXM];

  bool in[MAXM];

  void dfs(int v, int c) {
    if (used[v])
      return;
    used[v] = true;
    comp[v] = c;
    for (int i = 0; i < (int) g[v].size(); i++)
      if (in[g[v][i]])
        dfs(a[g[v][i]] + b[g[v][i]] - v, c);
  }

  void dfs() {
    memset(used, 0, sizeof(used));
    int cnt = 1;
    for (int i = 0; i < n; i++)
      if (!used[i])
        dfs(i, cnt++);
  }

  void precalc() {
    for (int i = 0; i < n; i++)
      g[i].clear();
    memset(usedcol, 0, sizeof(usedcol));
    for (int i = 0; i < m; i++)
      if (in[i]) {
        g[a[i]].push_back(i);
        g[b[i]].push_back(i);
        usedcol[color[i]] = true;
      }
  }


  int par[MAXM];
  int d[MAXM];

  void change(int v) {
    while (v != -1) {
      in[v] ^= 1;
      v = par[v];
    }
  }

  bool bfs() {
    vector<int> inv, outv;
    precalc();
    dfs();
    queue<int> q;
    for (int i = 0; i < m; i++) {
      d[i] = 1 << 25;
      par[i] = -1;
      if (in[i])
        inv.push_back(i);
      else {
        if (comp[a[i]] != comp[b[i]]) {
          q.push(i);
          d[i] = 0;
        }
        outv.push_back(i);
      }
    }

    int end = -1;

    for (; !q.empty();) {
      int v = q.front();
      q.pop();
      if (!in[v]) {
        if (!usedcol[color[v]]) {
          end = v;
          break;
        }
        for (int i = 0; i < (int) inv.size(); i++) {
          int to = inv[i];
          if (color[to] == color[v]) {
            if (d[to] > d[v] + 1) {
              q.push(to);
              d[to] = d[v] + 1;
              par[to] = v;
            }
          }
        }
      } else {
        in[v] = false;
        dfs();
        in[v] = true;

        for (int i = 0; i < (int) outv.size(); i++) {
          int to = outv[i];
          if (comp[a[to]] != comp[b[to]]) {
            if (d[to] > d[v] + 1) {
              q.push(to);
              d[to] = d[v] + 1;
              par[to] = v;
            }
          }
        }

      }
    }

    if (end == -1)
      return false;

    change(end);
    return true;
  }

  struct dsu {
    vector<int> p;
    dsu(int n) : p(n) {
      for (int i = 0; i < n; i++) p[i] = i;
    }
    int get(int x) {
      if (p[x] == x) return x;
      return p[x] = get(p[x]);
    }
    void join(int a, int b) {
      a = get(a);
      b = get(b);
      p[a] = b;
    }
  };

  int repair(int N, int M, edge *const edges, int *answer) {
    n = N;
    m = M;
    dsu ds(n);
    set<int> usedc;
    int gready = 0;
    for (int i = 0; i < m; i++) {
      a[i] = edges[i].u;
      b[i] = edges[i].v;
      color[i] = edges[i].c;
      if (ds.get(a[i]) != ds.get(b[i]) && !usedc.count(color[i])) {
        usedc.insert(color[i]);
        in[i] = true;
        ds.join(a[i], b[i]);
        gready++;
      }
      eprintf("%d %d %d\n", a[i], b[i], color[i]);
    }
    colors = *max_element(color, color + m) + 1;

    for (int i = gready;; i++) {
       //cerr << i<<endl;
      if (!bfs()) {
        int cnt = 0;
        for (int j = 0; j < m; j++)
          if (in[j])
            answer[cnt++] = j;
        return i;
      }
    }

    assert(false);
  }

};


char s[200][200];
int comp[200][200];

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) {
    scanf("%s", s[i]);
  }
  memset(comp, -1, sizeof(comp));
  function<void(int, int, char, int)> dfs = [&](int x, int y, char c, int comp_id) {
    if (x < 0 || y < 0 || x >= n || y >= m) return;
    if (s[x][y] != c) return;
    if (comp[x][y] != -1) return;
    comp[x][y] = comp_id;
    dfs(x + 1, y, c, comp_id);
    dfs(x, y + 1, c, comp_id);
    dfs(x - 1, y, c, comp_id);
    dfs(x, y - 1, c, comp_id);
  };
  int comp_id = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (comp[i][j] == -1) {
        dfs(i, j, s[i][j], comp_id++);
      }
    }
  }

  vector<highways::edge> es;

  int color = 0;

  struct item {
    int x;
    int y;
    char c;
  };
  vector<item> v;


  for (int i = 0; i + 1 < n; i++) {
    for (int j = 0; j + 1 < m; j++) {
      if (s[i][j] == s[i + 1][j + 1] && comp[i][j] != comp[i + 1][j + 1]) {
        es.push_back({comp[i][j], comp[i + 1][j + 1], color});
        v.push_back({i, j, '\\'});
      }
      if (s[i + 1][j] == s[i][j + 1] && comp[i + 1][j] != comp[i][j + 1]) {
        es.push_back({comp[i + 1][j], comp[i][j + 1], color});
        v.push_back({i, j, '/'});
      }
      color++;
    }
  }

  vector<int> answer(es.size());
  int cnt;
  if (color < comp_id - 2) {
    cnt = 0;
  } else {
    cnt = highways().repair(comp_id, v.size(), &es[0], &answer[0]);
  }

  if (cnt != comp_id - 2) {
    printf("IMPOSSIBLE\n");
    return;
  }
  printf("POSSIBLE\n");

  vector<string> ans(n - 1, string(m - 1, '.'));
  for (int i = 0; i < cnt; i++) {
    int id = answer[i];
    ans[v[id].x][v[id].y] = v[id].c;
  }

  for (int i = 0; i < n - 1; i++) {
    printf("%s\n", ans[i].c_str());
  }

}


int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
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
