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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

int det(vector<vector<int>> v) {
  int ans = 1;
  int n = v.size();
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (v[j][i] != 0) {
        v[i].swap(v[j]);
        if (i != j) {
          ans = MOD - ans;
        }
        break;
      }
    }
    if (v[i][i] == 0) {
      return 0;
    }
    int d = minv(v[i][i]);
    ans = mul(ans, v[i][i]);
    for (int j = i + 1; j < n; j++) {
      int coef = mul(v[j][i], d);
      for (int k = i; k < n; k++) {
        sub(v[j][k], mul(v[i][k], coef));
      }
      assert(v[j][i] == 0);
    }
  }
  return ans;
}

vector<vector<pair<int, bool>>> g;
vector<int> tin, tup;

void dfs(int v, int p) {
  static int timer;
  tin[v] = tup[v] = timer++;
  for (auto &[u, is_bridge] : g[v]) {
    if (u == p) continue;
    if (tin[u] != -1) {
      tup[v] = min(tup[v], tin[u]);
      continue;
    }
    dfs(u, v);
    tup[v] = min(tup[v], tup[u]);
    if (tup[u] > tin[v]) {
      is_bridge = true;
    }
  }
}

vector<vector<int>> comps;
vector<vector<int>> csons;
vector<bool> used;

void dfs2(int v, int c) {
  used[v] = true;
  comps[c].push_back(v);
  for (auto [u, is_bridge] : g[v]) {
    if (used[u]) continue;
    if (is_bridge) {
      int cid = comps.size();
      csons[v].push_back(cid);
      comps.emplace_back();
      dfs2(u, cid);
    } else {
      dfs2(u, c);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, m;
  scanf("%d%d%*d", &n, &m);
  g.resize(n); tin.resize(n, -1); tup.resize(n, -1);
  for (int i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a, --b;
    g[a].emplace_back(b, false);
    g[b].emplace_back(a, false);
  }
  for (int i = 0; i < n; i++) {
    sort(g[i].begin(), g[i].end());
  }

  dfs(0, -1);
  csons.resize(n);
  used.resize(n);
  comps.emplace_back();
  dfs2(0, 0);
#ifdef LOCAL
  eprintf("csons:\n");
  for (auto x : csons) {
    for (auto y : x) {
      eprintf("%d ", y);
    }
    eprintf("\n");
  }

  eprintf("comps:\n");
  for (auto x : comps) {
    for (auto y : x) {
      eprintf("%d ", y);
    }
    eprintf("\n");
  }
#endif

  vector<int> dp0(n);
  vector<int> dp1(n);

  for (int comp_id = (int)comps.size() - 1; comp_id >= 0; comp_id--) {
    const vector<int> &comp = comps[comp_id];
    for (int v : comp) {
      dp0[v] = 1;
      dp1[v] = 0;
      for (int cson : csons[v]) {
        int u = comps[cson][0];
        dp1[v] = mul(dp1[v], dp1[u]);
        sub(dp1[v], mul(dp0[v], dp0[u]));
        dp0[v] = mul(dp0[v], dp1[u]);
      }
    }

    if (comp.size() == 1) {
      continue;
    }

    int root = comp[0];

    vector<vector<int>> A(comp.size(), vector<int>(comp.size()));
    for (int i = 0; i < (int)comp.size(); i++) {
      int v = comp[i];
      A[i][i] = dp1[v];
      for (int j = 0; j < (int)comp.size(); j++) {
        int u = comp[j];
        if (binary_search(g[v].begin(), g[v].end(), make_pair(u, false))) {
          A[i][j] = dp0[v];
        }
      }
    }

    dp1[root] = det(A);

    A.erase(A.begin());
    for (auto &v : A) {
      v.erase(v.begin());
    }

    dp0[root] = mul(dp0[root], det(A));
  }

  printf("%d\n", dp1[0]);

  return 0;
}
