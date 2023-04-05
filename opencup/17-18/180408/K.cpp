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

vector<vector<int>> g;
vector<int> p;
vector<bool> z;

void dfs(int x) {
  if (z[x]) return;
  z[x] = true;
  for (int y : g[x]) {
    dfs(y);
  }
  p.push_back(x);
}

#define MOD 1000000007

void add(int& x, int y) {
  x += y;
  while (x >= MOD) {
    x -= MOD;
  }
  while (x < 0) {
    x += MOD;
  }
}

void mult(int& x, int y) {
  x = (int)((ll)x * y % MOD);
  while (x >= MOD) {
    x -= MOD;
  }
  while (x < 0) {
    x += MOD;
  }
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d", &n, &m);
  g.resize(n);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;y--;
    g[x].push_back(y);
  }

  z.resize(n);
  dfs(0);
  vector<vector<int>> dd(n, vector<int>(n));
  for (int x : p) {
    dd[x][x] = 1;
    for (int y : g[x]) {
      for (int i = 0; i < n; i++) {
        add(dd[x][i], dd[y][i]);
      }
    }
  }

  vector<int> d(n);
  reverse(p.begin(), p.end());
  for (int v : p) {
    if (v == 0) {
      d[v] = 1;
      continue;
    }
    int s = dd[0][v];
    mult(s, dd[0][v]);
    mult(s, dd[0][v]);
    for (int x : p) {
      if (x == v) break;
      for (int y : g[x]) {
        int q = d[x];
        mult(q, dd[y][v]);
        mult(q, dd[y][v]);
        mult(q, dd[y][v]);
        add(s, -q);
      }
    }
    d[v] = s;
  }

  cout << d[n - 1] << endl;

  return 0;
}
