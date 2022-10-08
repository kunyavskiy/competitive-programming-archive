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

using vi = vector<int>;
using vb = vector<bool>;
#define sz(x) (int)((x).size())

class Solver2 { // Min-cost circulation
  struct Edge {
    int to, ne;
    ll w, w0, c;
  };
  vector<Edge> es;
  vi firs;
  ll curRes;

public:
  Solver2(int n) : es(), firs(n, -1), curRes(0) {}
  // from, to, capacity (max.flow), cost
  int adde(int a, int b, ll w, ll c) {
    Edge e;
    e.to = b; e.ne = firs[a];
    e.w = e.w0 = w; e.c = c;
    es.push_back(e);
    firs[a] = sz(es) - 1;

    e.to = a; e.ne = firs[b];
    e.w = e.w0 = 0; e.c = -c;
    es.push_back(e);
    firs[b] = sz(es) - 1;
    return sz(es) - 2;
  }
  ll solve() {
    const int n = sz(firs);

    for (;;) {
      vector<ll> d(n, 0);
      vector<int> fre(n, -1);
      vi chd(n, -1);

      int base = -1;
      queue<int> q;
      for (int step = 0; step < n; step++) { /*BOXNEXT*/
        for (int i = 0; i < sz(es); i++) if (es[i].w > 0) {
            int b = es[i].to;
            int a = es[i ^ 1].to; /*BOXNEXT*/
            if (d[b] <= d[a] + es[i].c) continue;
            d[b] = d[a] + es[i].c;
            fre[b] = i;
            if (step == n - 1)
              base = b;
          }
      }
      if (base < 0) break;

      vi seq;
      vb was(n, false);/*BOXNEXT*/
      for (int x = base;; x = es[fre[x] ^ 1].to) {
        if (!was[x]) {
          seq.push_back(x);
          was[x] = true;
        } else {
          seq.erase(
            seq.begin(),
            find(seq.begin(), seq.end(),
                 x
                 ));
          break;
        }
      }
      for (int i = 0; i < sz(seq); i++) {
        int v = seq[i];
        int eid = fre[v];
        assert(es[eid].w > 0);
        es[eid].w--;
        es[eid ^ 1].w++;
        curRes += es[eid].c;
      }
    }
    return curRes;
  }

  bool any(int eid) { return es[eid].w != es[eid].w0; }
  ll flow(int eid) { return es[eid].w0 - es[eid].w; }
};

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    Solver2 solver(n + 2);
    solver.adde(n + 1, n, 1e15, 0);
    vector<int> a(n);
    vector<int> in(n), out(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      in[i] = solver.adde(n, i, 1, 0);
      out[i] = solver.adde(i, n + 1, 1, 0);
    }
    vector<int> eid(m);
    vector<int> x(m);
    vector<int> y(m);
    vector<vector<int>> rest(n);
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &x[i], &y[i]);
      --x[i], --y[i];
      rest[x[i]].push_back(y[i]);
      eid[i] = solver.adde(x[i], y[i], 1e15, a[y[i]] - a[x[i]]);
    }
    ll should_be = solver.solve();
    eprintf("%lld\n", should_be);
    vector<int> fixed;
    vector<vector<int>> es(n);
    for (int i = 0; i < n; i++) {
      if (!solver.any(in[i]) && !solver.any(out[i])) {
        fixed.push_back(i);
//        eprintf("%d is fixed\n", i);
      }
//      eprintf("S -> %d of %lld\n", i, solver.flow(in[i]));
//      eprintf("%d -> T of %lld\n", i, solver.flow(out[i]));
    }
    for (int i = 0; i < m; i++) {
//      eprintf("%d -> %d of %lld\n", x[i], y[i], solver.flow(eid[i]));
      if (solver.any(eid[i])) {
//        eprintf("%d should be equal to %d\n", x[i], y[i]);
        es[x[i]].push_back(y[i]);
        es[y[i]].push_back(x[i]);
      }
    }
    vector<bool> used(n);
    ll score = 0;
    for (int i = 0; i < m; i++) {
      if (binary_search(fixed.begin(), fixed.end(), x[i]) && a[y[i]] < a[x[i]]) {
        score += abs(a[y[i]] - a[x[i]]);
        a[y[i]] = a[x[i]];
      }
      if (binary_search(fixed.begin(), fixed.end(), y[i]) && a[y[i]] < a[x[i]]) {
        score += abs(a[y[i]] - a[x[i]]);
        a[x[i]] = a[y[i]];
      }
    }
    vector<int> comp;
    auto dfs = [&](int v, auto dfs) -> void {
      if (used[v]) return;
      comp.push_back(v);
      used[v] = true;
      for (int u : es[v])
        dfs(u, dfs);
    };
    for (int i : fixed) {
      comp.clear();
      dfs(i, dfs);
      for (int j: comp) {
        score += abs(a[i] - a[j]);
        a[j] = a[i];
      }
    }
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        comp.clear();
        dfs(i, dfs);
        int val = numeric_limits<int>::max();
        sort(comp.begin(), comp.end());
        for (int j : comp) {
          for (int k : rest[j]) {
            if (!binary_search(comp.begin(), comp.end(), k))
              val = min(val, a[k]);
          }
          if (solver.any(in[j])) {
            val = min(val, a[j]);
          }
        }
        for (int j : comp) {
          score += abs(a[j] - val);
          a[j] = val;
        }
      }
    }
    eprintf("score = %lld\n", score);
    for (int i = 0; i < n; i++) {
      printf("%d ", a[i]);
    }
    printf("\n");
  }

  return 0;
}
