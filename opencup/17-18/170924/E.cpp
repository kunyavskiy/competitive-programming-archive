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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

struct Edge {
  int u, v, num;
};
vector <Edge> edges;

vector <vector<int>> cycles;

void dfs(int s, int eNum, const vector <vector<Edge>> &ed,
         vector <int> &used,
         vector <Edge> &stack) {
  if (used[s]) {
    if (used[s] == 2) { return;}
    vector <int> cycle;
    for (int i = int(stack.size()) - 1; i >= 0; --i) {
      cycle.push_back(stack[i].num);
      if (stack[i].u == s) {
        break;
      }
    }
    cycles.push_back(cycle);
    return;
  }
  used[s] = 1;
  for (const auto & e : ed[s]) {
    if (e.num == eNum) { continue; }
    stack.push_back(e);
    dfs(e.v, e.num, ed, used, stack);
    stack.pop_back();
  }
  used[s] = 2;
}

void genThirdCycle() {
  assert((int)cycles.size() == 2);
  vector <int> used(110000);
  for (auto & c : cycles) {
    for (int x : c) {
      used[x] += 1;
    }
  }
  bool ok = false;
  for (int x: used) {
    if (x == 2) {
      ok = true;
    }
  }
  if (!ok) {return;}
  vector <int> nc;
  for (int i =0 ; i < int(used.size()); ++i) {
    if (used[i] == 1) {
      nc.push_back(i);
    }
  }
  cycles.push_back(nc);
}

void dfs2(int s,
         int eNum,
         const vector <vector<Edge>> &ed,
          vector <bool> &in_cycle,
          int badENum,
         vector <int> &used) {
  if (used[s]) {
    return;
  }
  used[s] = 1;
  for (const auto & e : ed[s]) {
    if (e.num == eNum || e.num == badENum || in_cycle[e.num]) { continue; }
    dfs2(e.v, e.num, ed, in_cycle, badENum, used);
  }
}


void solve2(const vector <vector <Edge>> & ed,
            vector <bool> &on_cycle,
            vector <bool> &in_cycle,
            Edge forDel) {
  int n = int(ed.size());
  vector <int> used(n);

  vector <int> deg(n);
  for (int i = 0; i < n; ++i) {
    for (auto e: ed[i]) {
      if (!in_cycle[e.num] && e.num != forDel.num) {
        ++deg[i];
      }
    }
  }
  for (int i =0 ; i < n; ++i) {
    if (deg[i] > 2) {
      return;
    }
  }

  for (int i = 0; i < n; ++i) {
    if (on_cycle[i]) {
      if (deg[i] > 1) {
        for (auto  e: ed[i]) {
          if (!in_cycle[e.num]) {
            solve2(ed, on_cycle, in_cycle, e);
          }
        }
        return; }
      if (used[i]) {
        if (forDel.num == -1) {
          for (auto  e: ed[i]) {
            if (!in_cycle[e.num]) {
              solve2(ed, on_cycle, in_cycle, e);
            }
          }
          return;
        }
      }
      dfs2(i, -1, ed, in_cycle, forDel.num, used);
    }
  }
  printf("%d %d\n", forDel.u + 1, forDel.v + 1);
  exit(0);
}

void solve(const vector <vector <Edge>> & ed,
           const vector <int> & cycle) {
  int n = int(ed.size());
  vector <bool> on_cycle(n);
  vector <bool> in_cycle(110000);
  for (int x : cycle) {
    in_cycle[x] = true;
    Edge e = edges[x];
    on_cycle[e.u] = true;
    on_cycle[e.v] = true;
  }
  vector <int> deg(n);
  for (int i = 0; i < n; ++i) {
    for (auto e: ed[i]) {
      if (!in_cycle[e.num]) {
        ++deg[i];
      }
    }
  }
  for (int i = 0; i < n; ++i) {
    if (deg[i] == 3) {
      for (auto  e: ed[i]) {
        if (!in_cycle[e.num]) {
          solve2(ed, on_cycle, in_cycle, e);
        }
      }
      return;
    }
  }
  for (int x = 0; x < n; ++x) {
    if (deg[x] == 2 && on_cycle[x]) {
      for (auto  e: ed[x]) {
        if (!in_cycle[e.num]) {
          solve2(ed, on_cycle, in_cycle, e);
        }
      }
      return;
    }
  }
  solve2(ed, on_cycle, in_cycle, {-1, -1, -1});
}


int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);

  edges.resize(m);
  vector <vector<Edge>> ed(n);
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    ed[v].push_back({v, u, i});
    ed[u].push_back({u, v, i});
    edges[i] = {u, v, i};
  }

  vector <int> used(n);
  vector <Edge> stack;
  dfs(0, -1, ed, used, stack);

  eprintf("found %d cycles\n", (int)cycles.size());
  for (auto & c : cycles) {
    for (int v : c) {
      eprintf("%d ", v);
    }
    eprintf("\n");
  }

  genThirdCycle();

  for (auto & c : cycles) {
    solve(ed, c);
  }
  assert(0);

  return 0;
}
