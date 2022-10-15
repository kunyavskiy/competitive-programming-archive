#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <bitset>
#include <ctime>
#include <cassert>
#define pb push_back
#define mp make_pair      
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
 
typedef long long ll;
typedef long double ld;


class TwoSatSolver {
  vector<vector<int>> g;
  vector<vector<int>> gt;
  vector<int> ts;
  vector<int> comp;
  vector<bool> used;

  void addEdge(int a, int av, int b, int bv) {
    g[2 * a + av].push_back(2 * b + bv);
    gt[2 * b + bv].push_back(2 * a + av);
  }

  void dfs_ts(int v) {
    if (used[v]) return;
    used[v] = true;
    for (int u : g[v]) {
      dfs_ts(u);
    }
    ts.push_back(v);
  }

  void dfs_comp(int v, int c) {
    if (comp[v] != -1) {
      return;
    }
    comp[v] = c;
    for (int u : gt[v]) {
      dfs_comp(u, c);
    }
  }

public:

  TwoSatSolver(int n) {
    g.resize(2 * n);
    gt.resize(2 * n);
  }

  int getN() {
    return (int)g.size() / 2;
  }

  int addVertex() {
    int n = (int) g.size() / 2;
    g.push_back(vector<int>());
    g.push_back(vector<int>());
    gt.push_back(vector<int>());
    gt.push_back(vector<int>());
    return n;
  }

  void addOr(int a, int av, int b, int bv) {
    eprintf("%cx%d || %cx%d = true\n", av ? ' ' : '!', a, bv ? ' ' : '!', b);
    addEdge(a, !av, b, bv);
    addEdge(b, !bv, a, av);
  }

  void addTrue(int a, int av) {
    eprintf("%cx%d = true\n", av ? ' ' : '!', a);
    addEdge(a, !av, a, av);
  }


  vector<bool> solve() {
    int n = g.size() / 2;
    used = vector<bool>(2 * n);
    comp = vector<int>(2 * n, -1);

    vector<bool> res(n);

    for (int i = 0; i < 2 * n; i++) {
      dfs_ts(i);
    }
    reverse(ts.begin(), ts.end());
    for (int i = 0; i < 2 * n; i++) {
      dfs_comp(ts[i], i);
    }

    for (int i = 0; i < n; i++) {
      if (comp[2 * i] == comp[2 * i + 1]) {
        return vector<bool>();
      }
      res[i] = comp[2 * i + 1] > comp[2 * i];
    }
    return res;
  }
};



class HiddenRabbits {
  vector<int> p;
  vector<vector<int>> sons;

  bool is_parent(int a, int b) {
    while (b != -1) {
      if (b == a) return true;
      b = p[b];
    }
    return false;
  }

  int pre_parent(int a, int b) {
    while (b != 0) {
      if (p[b] == a) return b;
      b = p[b];
    }
    return -1;
  }


public:
  vector<int> whereAreTheRabbits(vector<int> _p, int m, vector<int> r, vector<int> a, vector<int> b, vector<int> x) {
    int n = (int)_p.size() + 1;
    p = vector<int>(n, -1);
    sons.resize(n);
    for (int i = 1; i < n; i++) {
      p[i] = _p[i - 1];
      sons[p[i]].push_back(i);
    }

    SatSolver solver(n * m);

    for (int i = 0; i < m; i++) {
      solver.addTrue(i * n, 1);
    }

    for (int i = 0; i < (int)r.size(); i++) {
      if (r[i] == x[i]) {
        if (r[i] != 0) {
          solver.addOr(a[i] * n + x[i], 1, b[i] * n + x[i], 1);
        }
        for (int v : sons[r[i]]) {
          solver.addOr(a[i] * n + v, 0, b[i] * n + v, 0);
        }
      } else {
        if (is_parent(x[i], r[i])) {
          int prep = pre_parent(x[i], r[i]);
          solver.addTrue(a[i] * n + prep, 0);
          solver.addTrue(b[i] * n + prep, 0);
          solver.addOr(a[i] * n + x[i], 1, b[i] * n + x[i], 1);
          for (int v : sons[x[i]]) {
            if (v != prep) {
              solver.addOr(a[i] * n + v, 0, b[i] * n + v, 0);
            }
          }
        } else {
          solver.addTrue(a[i] * n + x[i], 1);
          solver.addTrue(b[i] * n + x[i], 1);
          for (int v : sons[x[i]]) {
            solver.addOr(a[i] * n + v, 0, b[i] * n + v, 0);
          }
        }
      }
    }

//    eprintf("=====\n");

    for (int i = 0; i < m; i++) {
      for (int j = 1; j < n; j++) {
        solver.addOr(i * n + j, 0, i * n + p[j], 1);
      }
      for (int j = 0; j < n; j++) {
        for (int v1 = 0; v1 < (int)sons[j].size(); v1++)
          for (int v2 = 1; v2 < (int)sons[j].size(); v2++) {
            solver.addOr(i * n + sons[j][v1], 0, i * n + sons[j][v2], 0);
          }
      }
    }


    vector<bool> res = solver.solve();
    if (res.empty()) {
      return vector<int>();
    }

    vector<int> ans(m);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (res[i * n + j] == true) {
          ans[i] = j;
        }
      }
    }
    return ans;
  }
};










