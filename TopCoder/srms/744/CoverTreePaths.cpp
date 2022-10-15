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


class CoverTreePaths {
  vector<int> d, c;
  vector<vector<int>> g;
  vector<vector<pair<int, int>>> ms;
  ll ans = 0;

  void merge(vector<pair<int, int>>& a, vector<pair<int, int>> &b) {
    if (a.size() < b.size()) {
      a.swap(b);
    }
    vector<pair<int, int>> c;
    while (!b.empty() && !a.empty()) {
      if (a.back().second < b.back().second) {
        c.emplace_back({a.back().first + b.back().first})
      }
    }
    while (!c.empty()) {
      a.push_back(c.back());
      c.pop_back();
    }
  }

  ll solve(int v, int cur) {
    cur = max(cur, d[v]);
    for (int u : g[v]) {
      solve(u, cur);
      merge(ms[v], ms[u]);
    }

  }

public:
  ll minimumCost(int n, vector<int> p, vector<int> d, vector<int> c, vector<int> params) {
    p.insert(p.begin(), -1);
    while ((int) p.size() < n) {
      p.push_back((p.back() * 1LL * params[0] + params[1]) % p.size());
    }
    while ((int) d.size() < n) {
      d.push_back(1 + (d.back() * 1LL * params[2] + params[3]) % params[4]);
    }
    while ((int) c.size() < n) {
      c.push_back(1 + (c.back() * 1LL * params[5] + params[6]) % params[7]);
    }

    this->d = d;
    this->c = c;
    g.resize(n);
    ms.resize(n);
    for (int i = 1; i < n; i++) {
      g[p[i]].push_back(i);
    }

    solve(0, 0);
    return ans;
  }
};










