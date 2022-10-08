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

int a, b;

int dfs(int v, const vector<vector<int>> &g, vector<bool> &used) {
  if (used[v]) {
    return 0;
  }
  used[v] = true;
  int cnt = (v != a) && (v != b);
  for (int u : g[v]) {
    cnt += dfs(u, g, used);
  }
  return cnt;
}

ll count(const vector<vector<int>> &g, vector<bool> used) {
  ll ans = 0;
  int cnt = 0;
  for (int i = 0; i < (int)g.size(); i++) {
    if (!used[i]) {
      int r = dfs(i, g, used);
      eprintf("%d ", r);
      ans += cnt * 1LL * r;
      cnt += r;
    }
  }
  eprintf("\n");
  return ans;
}

void solve() {
  int n, m;
  scanf("%d%d%d%d", &n, &m, &a, &b);
  --a, --b;
  vector<vector<int>> g(n);
  for (int i = 0; i < m; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  vector<bool> used(n, false);
  used[a] = true;
  ll cnta = count(g, used); // a * b + a * c
  used = vector<bool>(n, false);
  used[b] = true;
  ll cntb = count(g, used); // a * c + b * c
  used = vector<bool>(n, false);
  used[a] = used[b] = true;
  ll cntab = count(g, used); // a * b + a * c + b * c

  vector<bool> useda = vector<bool>(n, false);
  useda[a] = true;
  dfs(b, g, useda);
  vector<bool> usedb = vector<bool>(n, false);
  usedb[b] = true;
  dfs(a, g, usedb);

  ll cnt_either = 0;
  for (int i = 0; i < n; i++) {
    if (useda[i] && usedb[i] && i != a && i != b) {
      cnt_either++;
    }
  }

  eprintf("%lld %lld %lld %lld\n", cntab, cnta, cntb, cnt_either);
  if (cnta == 0 || cntb == 0) {
    printf("0\n");
  } else {
    printf("%lld\n", cnta + cntb - cntab + cnt_either * (cnt_either - 1) / 2);
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++) {
    solve();
  }

  return 0;
}
