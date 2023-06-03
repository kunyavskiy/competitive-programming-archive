#include <bits/stdc++.h>

using namespace std;

// DSU

const int maxn = 2e3;

vector <int> s(maxn, 1), par(maxn);

int get_par(int v) {
  return (par[v] == v) ? v : (par[v] = get_par(par[v]));
}

bool same(int x, int y) {
  return get_par(x) == get_par(y);
}

void unite(int x, int y) {
  x = get_par(x); y = get_par(y);
  if (x == y) return;
  if (s[x] > s[y]) {
    s[x] += s[y];
    par[y] = x;
  } else {
    s[y] += s[x];
    par[x] = y;
  }
}

// Color

const int maxc = 2e3;


// Edge

struct edge {
  int v, u, c;
};

vector <edge> e;

vector < vector <int> > g;

bool intersect_iter(int n, int m, int& an, vector<bool>& in, vector<bool>& color, vector<int>& res) {
  for (int i = 0; i < n; ++i) {
    s[i] = 1;
    par[i] = i;
  }
  for (auto id : res) {
    unite(e[id].v, e[id].u);
  }
  vector<bool> g1(m, 0), g2(m, 0);
  for (int i = 0; i < m; ++i) {
    if (!in[i]) {
      if (!same(e[i].v, e[i].u)) {
        g1[i] = 1;
      }
      if (!color[e[i].c]) {
        g2[i] = 1;
      }
    }
    g[i].clear();
  }
  for (int i = 0; i < an; ++i) {
    for (int j = 0; j < n; ++j) {
      s[j] = 1;
      par[j] = j;
    }
    for (auto id : res) {
      if (id != res[i])
        unite(e[id].v, e[id].u);
    }
    for (int j = 0; j < m; ++j) {
      if (!in[j]) {
        if (!same(e[j].v, e[j].u)) {
          g[res[i]].push_back(j);
        }
        if (!color[e[j].c] || e[j].c == e[res[i]].c) {
          g[j].push_back(res[i]);
        }
      }
    }
  }
  vector<int> d(m, 1e9), p(m, -1);
  queue<int> q;
  for (int i = 0; i < m; ++i) {
    if (g1[i]) {
      d[i] = 0;
      q.push(i);
    }
  }
  int last = -1;
  while (!q.empty()) {
    int v = q.front();
    q.pop();
    if (g2[v]) {
      last = v;
      break;
    }
    for (auto u : g[v]) {
      if (d[v] + 1 < d[u]) {
        d[u] = d[v] + 1;
        p[u] = v;
        q.push(u);
      }
    }
  }
  if (last == -1) {
    return false;
  }
  while (last > -1) {
    if (in[last]) {
      in[last] = 0;
      color[e[last].c] = 0;
    } else {
      in[last] = 1;
      color[e[last].c] = 1;
    }
    last = p[last];
  }
  an++;
  res.clear();
  for (int i = 0; i < m; ++i) {
    if (in[i]) {
      res.push_back(i);
    }
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif
  int n, m; cin >> n >> m;
  e.resize(m);
  g.resize(m);
  for (int i = 0; i < m; ++i) {
    int v, u, c; cin >> v >> u >> c;
    e[i] = {v - 1, u - 1, c};
  }
  sort(e.begin(), e.end(), [](const edge& a, const edge& b) { return a.c < b.c;});
  vector<int> last(n + 2, -1);
  for (int i = 0; i < m; i++) {
    last[e[i].c] = i;
  }


  int an = 0;
  vector<bool> in(m, 0);
  vector<bool> color(n + 2);
  vector<int> res;
  for (int i = 0; ; i++) {
    if (last[i] == -1 || !intersect_iter(n, last[i] + 1, an, in, color, res)) {
      printf("%d\n", i);
      return 0;
    }
  }
}