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
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

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

vector<int> p;

int get(int x) {
  if (p[x] != x) p[x] = get(p[x]);
  return p[x];
}

void join(int x, int y) {
  if (x > y) {
    p[x] = y;
  } else {
    p[y] = x;
  }
}

vector<vector<pair<int, int>>> g;
vector<bool> z;
vector<vector<int>> up;
vector<vector<int>> mx;
vector<int> lev;

int MAX = 20;

void dfs(int x, int p) {
  z[x] = true;
  if (p == -1) lev[x] = 0; else lev[x] = lev[p] + 1;
  up[x][0] = p == -1 ? x : p;
  for (int k = 1; k < MAX; k++) {
    up[x][k] = up[up[x][k - 1]][k - 1];
    mx[x][k] = max(mx[x][k - 1], mx[up[x][k - 1]][k - 1]);
  }
  for (auto q : g[x]) {
    int y = q.first;
    int w = q.second;
    if (y == p) continue;
    mx[y][0] = w;
    dfs(y, x);
  }
}

int main() {
#ifdef LOCAL
  freopen("p11.in", "r", stdin);
  freopen("p11.out", "w", stdout);
#endif

  int n, k, s, m;
  scanf("%d%d%d%d", &n, &k, &s, &m);

  p.resize(n);
  for (int i = 0; i < n; i++) {
    p[i] = i;
  }

  vector<pair<int, int>> pp;

  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--;
    y--;
    assert(x < n && y < n);
    pp.push_back({x, y});
  }

  g.resize(k);

  int mm = 0;
  for (int i = 0; i < n; i++) {
    vector<pair<int, int>> pp2;
    for (auto p : pp) {
      int x = p.first;
      int y = p.second;
      x = get(x);
      y = get(y);
      if (x != y) {
        join(x, y);
        if (x < k && y < k) {
          g[x].push_back({y, i});
          g[y].push_back({x, i});
          mm++;
          for (int j = 0; j < s; j++) {
            assert((j + 1) * k + x < n && (j + 1) * k + y < n);
            pp2.push_back({(j + 1) * k + x, (j + 1) * k + y});
          }
        }
      }
    }
    pp = pp2;
  }

  cerr << "done 1\n";
  cerr << mm << "\n";

  z.resize(k);
  lev.resize(k);
  up.assign(k, vector<int>(MAX));
  mx.assign(k, vector<int>(MAX));

  for (int i = 0; i < k; i++) {
    if (!z[i]) {
      dfs(i, -1);
    }
  }

  cerr << "done 1\n";

  int q;
  scanf("%d", &q);
  for (int i = 0; i < q; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    if (get(x) != get(y)) {
      cout << "-1\n";
    } else {
      int res = 0;
      if (lev[x] < lev[y]) swap(x, y);
      for (int k = MAX - 1; k >= 0; k--) {
        if (lev[up[x][k]] >= lev[y]) {
          res = max(res, mx[x][k]);
          x = up[x][k];
        }
      }
      if (x != y) {
        for (int k = MAX - 1; k >= 0; k--) {
          if (up[x][k] != up[y][k]) {
            res = max(res, mx[x][k]);
            res = max(res, mx[y][k]);
            x = up[x][k];
            y = up[y][k];
          }
        }
        res = max(res, mx[x][0]);
        res = max(res, mx[y][0]);
      }
      cout << res << "\n";
    }

  }

  return 0;
}
