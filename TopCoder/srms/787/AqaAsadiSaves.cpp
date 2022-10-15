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


class AqaAsadiSaves {
  vector<int> size;
  vector<int> tin, tup;
  vector<bool> used;
  vector<int> comp;
  int timer;
  vector<bool> is_bridge;
  vector<ll> score;
  vector<vector<pair<int, int>>> g;

  void dfss(int v, int peid, int root) {
    size[v] = 1;
    tin[v] = tup[v] = timer++;
    used[v] = true;
    comp[v] = root;
    for (auto u_ : g[v]) {
      int u = u_.first;
      int id = u_.second;
      if (id == peid) continue;
      if (used[u]) {
        tup[v] = min(tup[v], tin[u]);
        continue;
      }
      dfss(u, id, root);
      size[v] += size[u];
      tup[v] = min(tup[v], tup[u]);
      if (tup[u] > tin[v]) {
        is_bridge[id] = true;
      }
    }
  }

  int dfs(int v, int lim) {
    used[v] = true;
    int res = 0;
    for (auto x : g[v]) {
      int u = x.first;
      int id = x.second;
      if (used[u]) continue;
      int r = dfs(u, lim);
      if (is_bridge[id] && score[id] > lim) {
        if (r == 0) r = 1;
        if (r == 2) r = 3;
      }
      res = min(3, res + r);
    }
    return res;
  }

public:
  ll minDamage(int n, int m, vector<int> A, vector<int> B, int Seed, int X, int Y) {
    for (int i = A.size(); i < m; i++) {
      A.push_back(Seed);
      Seed = (Seed * 1LL * X + Y) % n;
    }
    for (int i = B.size(); i < m; i++) {
      B.push_back(Seed);
      Seed = (Seed * 1LL * X + Y) % n;
    }

    g.resize(n);
    tin.resize(n);
    tup.resize(n);
    used.resize(n);
    size.resize(n);
    comp.resize(n);
    is_bridge.resize(m);
    for (int i = 0; i < m; i++) {
      g[A[i]].push_back({B[i], i});
      g[B[i]].push_back({A[i], i});
    }

    vector<int> roots;
    for (int i = 0; i < n; i++) {
      if (!used[i]) {
        roots.push_back(i);
        dfss(i, -1, i);
      }
    }

    vector<ll> bridge_scores;
    bridge_scores.push_back(0);
    score.resize(m);
    for (int i = 0; i < m; i++) {
      if (is_bridge[i]) {
        int v;
        if (tin[A[i]] < tin[B[i]]) {
          v = B[i];
        } else {
          v = A[i];
        }
        bridge_scores.push_back(score[i] = size[v] * 1LL * (size[comp[v]] - size[v]));
      }
    }
    sort(bridge_scores.begin(), bridge_scores.end());
    bridge_scores.erase(unique(bridge_scores.begin(), bridge_scores.end()), bridge_scores.end());

    auto check = [&](int m) {
      fill(used.begin(), used.end(), false);
      int have = 0;
      for (int v : roots) {
        int r = dfs(v, m);
        if (r > 0 && have > 0) return false;
        have += r;
      }
      return have <= 2;
    };

    int l = -1;
    int r = bridge_scores.size() - 1;
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (check(bridge_scores[m])) {
        r = m;
      } else {
        l = m;
      }
    }

    return bridge_scores[r];
  }
};










