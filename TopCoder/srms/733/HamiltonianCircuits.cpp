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

#define eprintf(...) fprintf(stderr,__VA_ARGS__)

using namespace std;

typedef long long ll;
typedef long double ld;


struct degree_list {
  const vector<vector<int>> &g;
  vector<int> degin;
  vector<int> degout;
  vector<bool> in;
  int n;

  degree_list(vector<vector<int>> &g) : g(g) {
    n = g.size();
    degin = vector<int>(n);
    degout = vector<int>(n);
    in = vector<bool>(n);
  }

  void add_vertex(int x) {
    if (in[x]) return;
    in[x] = true;
    for (int i = 0; i < n; i++)
      if (g[i][x]) {
        degin[i]++;
      } else {
        degout[i]++;
      }
  }

  void del_vertex(int x) {
    if (!in[x]) return;
    in[x] = false;
    for (int i = 0; i < n; i++)
      if (g[i][x]) {
        degin[i]--;
      } else {
        degout[i]--;
      }
  }
};


class HamiltonianCircuits {
public:
  vector<int> findCircuit(int n, int seed, int a, int b, int c, vector <int> d, vector <int> e) {
    int value = seed;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      g[i][i] = 0;
      for (int j = i + 1; j < n; j++) {
        if (value % 1000 <= 250) {
          g[i][j] = 1;
          g[j][i] = 0;
        } else {
          g[i][j] = 0;
          g[j][i] = 1;
        }
        value = (a * 1LL * value + b) % c;
      }
    }
    for (int k = 0 ; k < (int)d.size(); k++) {
      g[d[k]][e[k]] = 1;
      g[e[k]][d[k]] = 0;
    }

    vector<int> ans;
    degree_list cycle(g);
    degree_list left(g);
    degree_list right(g);

    {
      int u, v;
      u = v = -1;
      for (int i = 0; i < n && u == -1; i++) {
        for (int j = 0; j < n && u == -1; j++) {
          if (g[0][i] && g[i][j] && g[j][0]) {
            v = i;
            u = j;
          }
        }
      }

      if (u == -1) {
        return vector<int>();
      }
      ans.push_back(0);
      ans.push_back(v);
      ans.push_back(u);
      cycle.add_vertex(0);
      cycle.add_vertex(v);
      cycle.add_vertex(u);
    }

    for (int i = 0; i < n; i++){
      if (!cycle.in[i] && cycle.degin[i] == 0) {
        right.add_vertex(i);
      }
      if (!cycle.in[i] && cycle.degout[i] == 0) {
        left.add_vertex(i);
      }
    }

    auto addv = [&](int v){
      cycle.add_vertex(v);
      left.del_vertex(v);
      right.del_vertex(v);
      for (int j = 0; j < n; j++){
        if (g[j][v])
          right.del_vertex(j);
        else
          left.del_vertex(j);
      }
    };

    while ((int)ans.size() != n) {
      for (int i = 0; i + 1 < (int) ans.size(); i++) {
        assert(g[ans[i]][ans[i + 1]]);
      }
      assert(g[ans.back()][ans[0]]);

      int v = -1;
      for (int i = 0; i < n; i++)
        if (!cycle.in[i] && !left.in[i] && !right.in[i]) {
          v = i;
          break;
        }
      if (v != -1) {
        assert(!cycle.in[v]);
        ans.push_back(ans[0]);
        for (int i = 0; i < (int) ans.size(); i++) {
          assert(i < (int) ans.size() - 1);
          if (g[ans[i]][v] && g[v][ans[i + 1]]) {
            ans.insert(ans.begin() + i + 1, v);
            ans.pop_back();
            addv(v);
            v = -1;
            break;
          }
        }
        continue;
      }
      int u = -1;
      for (int i = 0; i < n; i++)
        if (right.in[i] && left.degin[i]) {
          for (int j = 0; j < n; j++)
            if (g[i][j] && left.in[j]) {
              u = i;
              v = j;
              break;
            }
          break;
        }
      if (u == -1) {
        return vector<int>();
      }
      ans.push_back(u);
      ans.push_back(v);
      addv(u);
      addv(v);
    }

    return ans;
  }
};










