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

vector<vector<int>> g;
vector<int> tin;
vector<int> tup;
int timer;
vector<pair<int, int>> es_stack;

void dfs(int v, int p) {
  tin[v] = tup[v] = ++timer;
  eprintf("in[%d] = %d\n", v, tin[v]);
  for (int u : g[v]) {
    if (u == p) continue;
    if (tin[u] > tin[v]) { continue; }
    es_stack.emplace_back(v, u);
    if (tin[u] != -1) {
      tup[v] = min(tup[v], tin[u]);
      continue;
    }
    dfs(u, v);
    tup[v] = min(tup[v], tup[u]);
    if (tup[u] >= tin[v]) {
      vector<int> vs;
      vs.push_back(u);
      vs.push_back(v);
      while (es_stack.back() != pair<int, int>{v, u}) {
        vs.push_back(es_stack.back().first);
        vs.push_back(es_stack.back().second);
        es_stack.pop_back();
      }
      es_stack.pop_back();
      sort(vs.begin(), vs.end());
      vs.erase(unique(vs.begin(), vs.end()), vs.end());
      g.push_back(vs);
    }
  }
  eprintf("up[%d] = %d\n", v, tup[v]);
}

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

int calc(int v, int p, const vector<vector<int>> &g, int n, int& ans) {
  int cur = 1;
  for (int u : g[v]) {
    if (u == p) continue;
    int r = calc(u, v, g, n, ans);
    add(r, 1);
    cur = mul(cur, r);
  }
  if (v < n) {
    sub(cur, 1);
    add(ans, cur);
  }
  return cur;
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    g = vector<vector<int>>(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }
    tin = tup = vector<int>(n, -1);
    timer = 0;
    dfs(0, -1);
    for (int i = 0; i < n; i++) {
      g[i].clear();
    }
    for (int i = n; i < (int)g.size(); i++) {
      for (int v : g[i]) {
        eprintf("%d ", v);
        g[v].push_back(i);
      }
      eprintf("\n");
    }

    int ans = n + 1;
    calc(0, -1, g, n, ans);
    printf("%d\n", ans);
  }

  return 0;
}
