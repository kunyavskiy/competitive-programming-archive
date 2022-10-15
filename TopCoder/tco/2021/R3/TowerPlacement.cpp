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
    //eprintf("%cx%d || %cx%d = true\n", av ? ' ' : '!', a, bv ? ' ' : '!', b);
    addEdge(a, !av, b, bv);
    addEdge(b, !bv, a, av);
  }

  void addTrue(int a, int av) {
    //eprintf("%cx%d = true\n", av ? ' ' : '!', a);
    addEdge(a, !av, a, av);
  }


  bool solve() {
    int n = g.size() / 2;
    used = vector<bool>(2 * n);
    comp = vector<int>(2 * n, -1);


    for (int i = 0; i < 2 * n; i++) {
      dfs_ts(i);
    }
    reverse(ts.begin(), ts.end());
    for (int i = 0; i < 2 * n; i++) {
      dfs_comp(ts[i], i);
    }

    for (int i = 0; i < n; i++) {
      if (comp[2 * i] == comp[2 * i + 1]) {
        return false;
      }
    }
    return true;
  }
};


class Solver {
  vector<pair<int, int>> v;
  int r, c;
public:
  Solver(int r, int c) : r(r), c(c) {}
  void add(int x, int y) {
    v.emplace_back(x, y);
  }
  bool check() {
    sort(v.begin(), v.end());
    TwoSatSolver solver(v.size());
    for (int i = 0; i < (int)v.size(); i++) {
      if (v[i].first == 0 || v[i].first == r - 1) {
        solver.addTrue(i, false);
      }
      if (v[i].second == 0 || v[i].second == c - 1) {
        solver.addTrue(i, true);
      }
    }

    auto for_diff = [&](int dx, int dy, const std::function<void(int, int)> &cb) {
      int pt = 0;
      for (int i = 0; i < (int) v.size(); i++) {
        pair<int, int> s = {v[i].first + dx, v[i].second + dy};
        while (pt < (int) v.size() && v[pt] < s) pt++;
        if (pt < (int) v.size() && v[pt] == s) { cb(i, pt); }
      }
    };

    // T.T
    for_diff(-1, 0, [&](int a, int b) { solver.addOr(a, false, b, false); });
    // T..T
    for_diff(-2, 0, [&](int a, int b) { solver.addOr(a, false, b, false); });
    // T.T
    for_diff(0, -1, [&](int a, int b) { solver.addOr(a, true, b, true); });
    // T..T
    for_diff(0, -2, [&](int a, int b) { solver.addOr(a, true, b, true); });

    for (int dy = -1; dy <= 1; dy++) {
      for (int dx = -1; dx <= 1; dx++) {
        if (dx || dy) {
          for_diff(dx, dy, [&](int a, int b) { solver.addOr(a, false, b, true); });
        }
      }
    }

    return solver.solve();
  }
};

class TowerPlacement {
public:
  int solve(int R, int C, int seed, int X) {
    vector<pair<int, int>> a(50000);
    int state = seed;
    for (int i = 0; i <= 49999; i++) {
      state = (state * 1103515245LL + 12345) % (1LL << 31);
      a[i].first = (state / 1000) % R;
      state = (state * 1103515245LL + 12345) % (1LL << 31);
      a[i].second = (state / 1000) % C;
    }
    vector<bool> removed(a.size());
    vector<bool> enabled(a.size(), false);
    map<pair<int, int>, vector<int>> pos;
    for (int i = 0;i < (int)a.size(); i++) {
      pos[a[i]].push_back(i);
    }
    for (auto &x : pos) {
      reverse(x.second.begin(), x.second.end());
      enabled[x.second.back()] = true;
    }

    for (int it = 0;;it++) {
      vector<int> b;
      for (int i = 0; i < (int)a.size(); i++) {
        if (enabled[i]) {
          b.push_back(i);
        }
      }
      auto check = [&](int x) {
        Solver solve(R, C);
        for (int i = 0; i < x; i++) {
          solve.add(a[b[i]].first, a[b[i]].second);
        }
        return solve.check();
      };
      if (check(b.size())) return -1;
      int l = 0;
      int r = b.size();
      while (r - l > 1) {
        int m = (l + r) / 2;
        if (check(m)) {
          l = m;
        } else {
          r = m;
        }
      }
      //printf("l = %d, b[l] = %d\n", l, b[l]);
      if (it == X - 1) return b[l];
      enabled[b[l]] = false;
      auto &p = pos[a[b[l]]];
      p.pop_back();
      if (!p.empty()) {
        enabled[p.back()] = true;
      }
    }
  }
};









