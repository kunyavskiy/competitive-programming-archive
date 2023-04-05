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

vector<vector<int>> g;
vector<bool> z;

int size(int x, int p) {
  int res = 1;
  for (int y : g[x]) {
    if (y != p && !z[y]) {
      res += size(y, x);
    }
  }
  return res;
}

int centroid;

int find_centroid(int x, int p, int n) {
  int res = 1;
  bool ok = true;
  for (int y : g[x]) {
    if (y != p && !z[y]) {
      int s = find_centroid(y, x, n);
      if (s > n / 2) ok = false;
      res += s;
    }
  }
  if (res < n / 2) ok = false;
  if (ok) {
    centroid = x;
  }
  return res;
}

vector<vector<pair<int, int>>> up; // pairs (centroid, distance), from top
vector<int> cnt;

void add_dist(int x, int p, int c, int d) {
  up[x].push_back({c, d});
  cnt[c]++;
  for (int y : g[x]) {
    if (y != p && !z[y]) {
      add_dist(y, x, c, d + 1);
    }
  }
}

void build_centroid(int x, int p) {
  int n = size(x, p);
  find_centroid(x, p, n);

  x = centroid;

  add_dist(x, -1, x, 0);

  z[x] = true;

  for (int y : g[x]) {
    if (!z[y]) {
      build_centroid(y, x);
    }
  }
}

vector<vector<ll>> A1, C1, A2, C2;
int k;

//void update(int i, int d) { // updates sum for all centroids above
//  for (int j = 0; j < (int)up[i].size(); j++) {
//    auto p = up[i][j];
//    s[p.first][c[i]] += p.second * d;
//    q[p.first][c[i]] += d;
//    if (j < (int)up[i].size() - 1) {
//      auto pp = up[i][j + 1];
//      ss[pp.first][c[i]] += p.second * d;
//      qq[pp.first][c[i]] += d;
//    }
//  }
//}

void add(int i, int r) {
  for (int j = 0; j < (int) up[i].size(); j++) {
    auto p = up[i][j];
    int c = p.first;
    int d = p.second;
    int x = (r + 1 - d);
    int st = 0;
    if (x < 0) {
      int p = (-x + k - 1) / k;
      st = p;
      x += k * p;
    }
    C1[c][0] += st;
    if (x < (int) A1[c].size()) {
      A1[c][x]++;
    }
    if (j < (int) up[i].size() - 1) {
      auto cc = up[i][j + 1].first;
      C2[cc][0] += st;
      if (x < (int) A2[cc].size()) {
        A2[cc][x]++;
      }
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  std::ios::sync_with_stdio(false);

  int n, m;
  cin >> n >> m >> k;

  g.resize(n);
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    x--;
    y--;
    g[x].push_back(y);
    g[y].push_back(x);
  }
  z.resize(n);
  up.resize(n);
  cnt.resize(n);
  build_centroid(0, -1);
  A1.resize(n);
  A2.resize(n);
  C1.resize(n);
  C2.resize(n);

  for (int i = 0; i < n; i++) {
    A1[i].resize(cnt[i] + 1);
    C1[i].resize(cnt[i] + 1);
    A2[i].resize(cnt[i] + 1);
    C2[i].resize(cnt[i] + 1);
  }

  for (int i = 0; i < m; i++) {
    int v, r;
    cin >> v >> r;
    v--;
    add(v, r);
  }

  for (int i = 0; i < n; i++) {
    for (int j = k; j < (int)A1[i].size(); j++) {
      A1[i][j] += A1[i][j - k];
    }
    for (int j = k; j < (int)A2[i].size(); j++) {
      A2[i][j] += A2[i][j - k];
    }
    for (int j = 0; j < (int)C1[i].size(); j++) {
      if (j > 0) C1[i][j] += C1[i][j - 1];
      C1[i][j] += A1[i][j];
    }
    for (int j = 0; j < (int)C2[i].size(); j++) {
      if (j > 0) C2[i][j] += C2[i][j - 1];
      C2[i][j] += A2[i][j];
    }
  }

  ll ans = (ll)(1e18);
  for (int i = 0; i < n; i++) {
    ll res = 0;
    for (int j = 0; j < (int)up[i].size(); j++) {
      auto p = up[i][j];
      res += C1[p.first][p.second];
      if (j < (int)up[i].size() - 1) {
        auto pp = up[i][j + 1];
        res -= C2[pp.first][p.second];
      }
    }
//    cout << res << "\n";
    ans = min(ans, res);
  }
  cout << ans << "\n";

  return 0;
}
