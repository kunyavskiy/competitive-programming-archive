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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

vector<vector<int>> g;
vector<int> up;
vector<int> in;
vector<int> z;
vector<int> color;

vector<vector<pair<int, int>>> comp;
vector<pair<int, int>> st;

vector<pair<int, int>> edges;
vector<int> flow;
vector<int> capacity;
vector<vector<int>> gg;

int tt = 0;

void dfs(int x, int p) {
  in[x] = tt++;
  up[x] = in[x];
  z[x] = 1;
//  cout << x << "\n";
  for (int y : g[x]) {
    if (y == p) continue;
    if (z[y]) {
      if (z[y] == 1) {
        st.push_back({x, y});
        up[x] = min(up[x], in[y]);
      }
    } else {
      int sp = (int) st.size();
      st.push_back({x, y});
      dfs(y, x);
      if (up[y] >= in[x] || p == -1) {
        vector<pair<int, int>> cc;
        while ((int) st.size() > sp) {
          cc.push_back(st[(int) st.size() - 1]);
          st.pop_back();
        }
//        for (auto& e : cc) {
//          cout << e.first << "-" << e.second << " ";
//        }
//        cout << "\n";
        if (cc.size() > 0) {
          comp.push_back(cc);
        }
      }
      up[x] = min(up[x], up[y]);
    }
  }
  z[x] = 2;
}

void add_edge(int x, int y) {
  edges.push_back({x, y});
  capacity.push_back(1);
  flow.push_back(0);
  edges.push_back({y, x});
  capacity.push_back(0);
  flow.push_back(0);
}

bool push(int s, int t) {
  if (s == t) return true;
  if (z[s]) return false;
  z[s] = 1;
  for (int i : gg[s]) {
    if (flow[i] < capacity[i] && push(edges[i].second, t)) {
      flow[i]++;
      flow[i ^ 1]--;
      return true;
    }
  }
  return false;
}

vector<int> ee;

bool find_path(int s, int t) {
  if (s == t) return true;
  if (z[s]) return false;
  z[s] = 1;
  for (int i : gg[s]) {
    if (flow[i] > 0 && find_path(edges[i].second, t)) {
      ee.push_back(s);
      flow[i]--;
      flow[i ^ 1]++;
      return true;
    }
  }
  return false;
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  g.resize(n);
  up.resize(n);
  in.resize(n);
  z.resize(n);
  color.resize(n);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  for (int i = 0; i < n; i++) {
    scanf("%d", &color[i]);
  }
  for (int i = 0; i < n; i++) {
    if (!z[i]) dfs(i, -1);
  }

  for (auto &c : comp) {
    set<int> has;
    for (auto &e : c) {
      has.insert(color[e.first]);
      has.insert(color[e.second]);
    }
    if (has.size() == 3) {
      pair<int, int> e1;
      for (auto &e : c) {
        if (color[e.first] != color[e.second]) {
          e1 = e;
          break;
        }
      }
      int v2 = -1;
      for (auto &e : c) {
        if ((color[e.first] != color[e1.first] && color[e.first] != color[e1.second])) {
          v2 = e.first;
          break;
        } else if (color[e.second] != color[e1.first] && color[e.second] != color[e1.second]) {
          v2 = e.second;
          break;
        }
      }
      assert(v2 >= 0);
//      cout << e1.first << "-" << e1.second << " " << e2.first << "-"<< e2.second <<"\n";

      for (auto &e : c) {
        if (e != e1) {
          add_edge(2 * e.first + 1, 2 * e.second);
          add_edge(2 * e.second + 1, 2 * e.first);
        }
      }

      for (int i = 0; i < n; i++) {
        add_edge(2 * i, 2 * i + 1);
      }
      add_edge(2 * n, 2 * e1.first);
      add_edge(2 * n, 2 * e1.second);
      add_edge(2 * v2, 2 * n + 1);
      add_edge(2 * v2, 2 * n + 1);

      gg.resize(2 * n + 2);
      for (int i = 0; i < (int) edges.size(); i++) {
        gg[edges[i].first].push_back(i);
      }

      for (int q = 0; q < 2; q++) {
        z.clear();
        z.resize(gg.size());
        if (!push(2 * n, 2 * n + 1)) {
          assert(false);
        }
      }

      vector<int> ans;
      for (int q = 0; q < 2; q++) {
        z.clear();
        z.resize(gg.size());
        ee.clear();
        find_path(2 * n, 2 * n + 1);
        reverse(ee.begin(), ee.end());
        vector<int> temp;
        for (int i = 1; i < (int)ee.size(); i += 2) {
          temp.push_back(ee[i] / 2);
        }
        if (q == 1) {
          reverse(temp.begin(), temp.end());\
          ans.pop_back();
        }
        ans.insert(ans.end(), temp.begin(), temp.end());
      }

      cout << "YES\n";
      cout << ans.size() << "\n";
      for (int i : ans) {
        cout << (i + 1) << " ";
      }
      cout << "\n";

      return 0;
    }
  }
  cout << "NO\n";



//  for (auto& c : comp) {
//    for (auto& e : c) {
//      cout << e.first << "-" << e.second << " ";
//    }
//    cout << "\n";
//  }

  return 0;
}
