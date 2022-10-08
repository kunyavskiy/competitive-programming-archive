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

class Solver {
  vector<vector<int>> g;
  vector<int> mt;
  vector<bool> used;

  int dfs(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int i = 0; i < (int)g[v].size(); i++) {
      if (g[v][i]) {
        if (mt[i] == -1 || dfs(mt[i])) {
          mt[i] = v;
          return true;
        }
      }
    }
    return false;
  }
public:
  Solver(int n) : g(n, vector<int>(n)) {

  }

  void add_edge(int u, int v) {
    g[u][v] = true;
  }

  bool solve() {
    int n = g.size();
    mt = vector<int>(n, -1);
    for (int i = 0; i < n; i++) {
      used = vector<bool>(n, false);
      if (!dfs(i)) {
        return false;
      }
    }


    return true;
  }
};

bool check(vector<int> a, vector<int> b, int m, int L) {
  int n = a.size();

  Solver s(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (abs(a[i] - b[j]) <= m || abs(a[i] - b[j]) >= L - m) {
        s.add_edge(i, j);
      }
    }
  }
//  eprintf("m = %d\n", m);
  return s.solve();
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n, L;
  while (scanf("%d%d", &n, &L) == 2) {
    vector<int> a(n);
    vector<int> b(n);
    for (int &x : a) scanf("%d", &x);
    for (int &x : b) scanf("%d", &x);

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());

    int lf = -1;
    int rg = L / 2;

    while (rg - lf > 1) {
      int m = (lf + rg) / 2;
      if (check(a, b, m, L)) {
        rg = m;
      } else {
        lf = m;
      }
    }
    printf("%d\n", rg);
//    break;
  }

  return 0;
}
