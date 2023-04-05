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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl

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

class TwoSatSolver {
  vector<vector<bool>> g;
  vector<int> ts;
  vector<int> comp;
  vector<bool> used;
  int n;

  void addEdge(int a, int av, int b, int bv) {
    g[2 * a + av][2 * b + bv] = true;
  }

  void dfs_ts(int v) {
    if (used[v]) return;
    used[v] = true;

    for (int u = 0; u < n; u++) {
      if (g[v][u])
        dfs_ts(u);
    }
    ts.push_back(v);
  }

  void dfs_comp(int v, int c) {
    if (comp[v] != -1) {
      return;
    }
    comp[v] = c;
    for (int u = 0; u < n; u++) {
      if (g[u][v])
        dfs_comp(u, c);
    }
  }

public:

  TwoSatSolver(int n) : n(2 * n){
    g.resize(2 * n, vector<bool>(2 * n));
  }

  int getN() {
    return (int) g.size() / 2;
  }

  void addOr(int a, int av, int b, int bv) {
//    eprintf("%cx%d || %cx%d = true\n", av ? ' ' : '!', a, bv ? ' ' : '!', b);
    addEdge(a, !av, b, bv);
    addEdge(b, !bv, a, av);
  }

  void addTrue(int a, int av) {
//    eprintf("%cx%d = true\n", av ? ' ' : '!', a);
    addEdge(a, !av, a, av);
  }


  vector<bool> solve() {
    int n = g.size() / 2;
    used = vector<bool>(2 * n);
    comp = vector<int>(2 * n, -1);

    vector<bool> res(n);

    for (int i = 0; i < 2 * n; i++) {
      dfs_ts(i);
    }
    reverse(ts.begin(), ts.end());
    for (int i = 0; i < 2 * n; i++) {
      dfs_comp(ts[i], i);
    }

    for (int i = 0; i < n; i++) {
      if (comp[2 * i] == comp[2 * i + 1]) {
        return vector<bool>();
      }
      res[i] = comp[2 * i + 1] > comp[2 * i];
    }
    return res;
  }
};

int h, w;
vector<string> a;

bool good(int i, int j) {
  if (i < 0 || i >= h || j < 0 || j >= w) return false;
  return a[i][j] != '#';
}

void dfs(int i, int j, int k, vector<char> &z) {
  if (!good(i, j))
    return;
//  cerr << i << " " << j << " " << k << "\n";
  int x = ((i * w) + j) * 2 + k;
  if (z[x]) return;
  z[x] = true;
  if (k == 0) {
    dfs(i - 1, j, k, z);
    dfs(i + 1, j, k, z);
    if (!good(i - 1, j) || !good(i + 1, j)) dfs(i, j, 1, z);
  } else {
    dfs(i, j - 1, k, z);
    dfs(i, j + 1, k, z);
    if (!good(i, j - 1) || !good(i, j + 1)) dfs(i, j, 0, z);
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  scanf("%d%d", &h, &w);
  a.resize(h);
  static char s[100];
  for (int i = 0; i < h; i++) {
    scanf("%s", s);
    a[i] = s;
  }
  int N = h * w * 2;
  vector<vector<char>> b(N, vector<char>(N));
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      for (int k = 0; k < 2; k++) {
        int x = ((i * w) + j) * 2 + k;
//        cerr << ". " <<  i << " " << j << " " << k << "\n";
        dfs(i, j, k, b[x]);
      }
    }
  }

  vector<int> sx;
  vector<int> sy;
  int startx = 0;
  int starty = 0;
  int startid = 0;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (a[i][j] == 'O') {
        startx = i;
        starty = j;
        startid = sx.size();
      }
      if (a[i][j] == '*' || a[i][j] == 'O') {
        sx.push_back(i);
        sy.push_back(j);
      }
    }
  }
  int n = sx.size();

  TIMESTAMP(prepare);

  TwoSatSolver sol(n);
  for (int i = 0; i < n; i++) {
    for (int ki = 0; ki < 2; ki++) {
      int x = (sx[i] * w + sy[i]) * 2 + ki;
      for (int kk = 0; kk < 2; kk++) {
        int xx = (startx * w + starty) * 2 + kk;
        if (!b[xx][x]) {
          sol.addOr(i, !ki, startid, !kk);
        }
      }
      for (int j = i + 1; j < n; j++) {
        for (int kj = 0; kj < 2; kj++) {
          int y = (sx[j] * w + sy[j]) * 2 + kj;
          if (!b[x][y] && !b[y][x]) {
            sol.addOr(i, !ki, j, !kj);
          }
        }
      }
    }
  }
  if (!sol.solve().empty()) {
    cout << "YES";
    return 0;
  }

  cout << "NO";

  return 0;
}
