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


class HamiltonianTree {
  vector<vector<int>> g;
  vector<int> lf, rg;

  void get_graph(string s) {
    vector<int> st;
    int cnt = 1;
    st.push_back(0);
    g.emplace_back();
    for (char c : s) {
      if (c == 'D') {
        g.at(st.back()).push_back(cnt);
        g.emplace_back();
        st.push_back(cnt++);
      } else {
        st.pop_back();
      }
    }
    for (int i = 1; i < (int) g.size(); i++) {
      assert(g[i].size() == 0 || g[i].size() == 2);
    }
  }

  void gen_path(int v, int from, int to, vector<int> &path) {
    if (from == to) {
      assert(from == v);
      path.push_back(v);
      return;
    }
    if (to == v || (from != v && to == lf[v])) {
      int sz = path.size();
      gen_path(v, to, from, path);
      reverse(path.begin() + sz, path.end());
      return;
    }
    if (from == v) {
      path.push_back(v);
      if (to == lf[v]) {
        gen_path(g[v][1], g[v][1], lf[g[v][1]], path);
        gen_path(g[v][0], rg[g[v][0]], lf[g[v][0]], path);
      } else {
        assert(to == rg[v]);
        gen_path(g[v][0], g[v][0], rg[g[v][0]], path);
        gen_path(g[v][1], lf[g[v][1]], rg[g[v][1]], path);
      }
      return;
    }
    assert(from == lf[v]);
    assert(to == rg[v]);
    gen_path(g[v][0], from, g[v][0], path);
    path.push_back(v);
    gen_path(g[v][1], g[v][1], to, path);
  }

  vector<vector<int>> gen_cycles() {
    int n = g.size();
    lf = rg = vector<int>(g.size());
    for (int i = n - 1; i >= 0; i--) {
      if (g[i].empty()) {
        lf[i] = rg[i] = i;
      } else {
        lf[i] = lf[g[i][0]];
        rg[i] = rg[g[i].back()];
      }
    }
    vector<vector<int>> ans;
    for (int i = 0; i < (int)g[0].size(); i++) {
      vector<int> path;
      path.push_back(0);
      gen_path(g[0][i], g[0][i], rg[g[0][i]], path);
      for (int j = 1; j < (int)g[0].size() - 1; j++) {
        int cur = (i + j) % g[0].size();
        gen_path(g[0][cur], lf[g[0][cur]], rg[g[0][cur]], path);
      }
      int prev = (i + g[0].size() - 1) % g[0].size();
      gen_path(g[0][prev], lf[g[0][prev]], g[0][prev], path);
      assert((int)path.size() == n);
      ans.emplace_back(std::move(path));
    }
    return ans;
  }

public:
  vector<int> construct(string s, int seed, int jump_cost, int index) {
    get_graph(s);
    vector<int> a(g.size());
    a[0] = seed;
    for (int i = 1; i < (int) a.size(); i++) {
      a[i] = ((a[i - 1] * 1103515245LL + 12345LL) & ((1LL << 31) - 1));
    }

    auto cost2 = [&](int x, int y) {
      if (find(g[x].begin(), g[x].end(), y) != g[x].end()) return a[y] >> 21;
      if (find(g[y].begin(), g[y].end(), x) != g[y].end()) return a[x] >> 21;
      assert(g[x].size() == 0 && g[y].size() == 0);
      return jump_cost;
    };

    auto cost = [&](const vector<int>& a) {
      ll ans = cost2(a.back(), a[0]);
      for (int i = 1; i < (int)a.size(); i++) {
        ans += cost2(a[i - 1], a[i]);
      }
      return ans;
    };

    vector<vector<int>> cycles = gen_cycles();
    vector<pair<ll, vector<int>>> cycles2;
    for (auto & x: cycles) {
      for (int j = 0; j < 2; j++) {
        for (int i = 0; i < (int) x.size(); i++) {
          rotate(x.begin(), x.begin() + 1, x.end());
          cycles2.emplace_back(cost(x), x);
        }
        reverse(x.begin(), x.end());
      }
    }
    sort(cycles2.begin(), cycles2.end());
    cycles2.erase(unique(cycles2.begin(), cycles2.end()), cycles2.end());
    if (index > (int)cycles2.size()) {
      return vector<int>();
    } else {
      return cycles2[index - 1].second;
    }
  }
};










