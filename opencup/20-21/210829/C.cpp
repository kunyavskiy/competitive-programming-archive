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

void solve() {
  int n;
  scanf("%d", &n);
  vector<vector<int>> eid(n);
  vector<int> eu(n - 1);
  vector<int> ev(n - 1);
  vector<ll> b(n - 1);
  vector<ll> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
  }
  for (int j = 0; j < n - 1; j++) {
    scanf("%d%d%lld", &eu[j], &ev[j], &b[j]);
    --eu[j], --ev[j];
    eid[eu[j]].push_back(j);
    eid[ev[j]].push_back(j);
  }

  vector<tuple<int, int, ll>> ops;
  auto add_op = [&](int v, int u, int vid, int uid, ll W) {
    if (!W) return;
    ops.emplace_back(v, u, W);
    a[v] ^= W;
    a[u] ^= W;
    b[vid] += W;
    if (uid != -1) b[uid] -= W;
  };


  auto fix = [&](int v, int vid, int u, int uid) {
    add_op(v, u, vid, uid, a[v]);
    if (b[vid] % 2 != 0) return false;
    ll W = abs(b[vid]) / 2;
    if (b[vid] > 0) {
      add_op(u, v, uid, vid, W);
      add_op(u, v, uid, vid, W);
    } else {
      add_op(v, u, vid, uid, W);
      add_op(v, u, vid, uid, W);
    }
    return true;
  };

  auto dfs = [&](int v, int p, int peid, auto dfs) -> bool {
    int fsid = -1;
    int fs = -1;
    for (int uid : eid[v]) {
      int u = eu[uid] + ev[uid] - v;
      if (u == p) continue;
      if (!dfs(u, v, uid, dfs)) return false;
      if (fsid == -1) {
        fsid = uid;
        fs = u;
      } else {
        if (!fix(u, uid, fs, fsid)) return false;
        assert(a[u] == 0);
        assert(b[uid] == 0);
      }
    }
    if (fs != -1) {
      if (p != -1) {
        if (!fix(fs, fsid, p, peid)) return false;
      } else {
        add_op(v, fs, fsid, -1, a[fs]);
        if (b[fsid] % 2 != 0 || b[fsid] > 0) return false;
        ll W = -b[fsid] / 2;
        add_op(v, fs, fsid, -1, W);
        add_op(v, fs, fsid, -1, W);
      }
      assert(a[fs] == 0);
      assert(b[fsid] == 0);
    }
    return true;
  };
  if (!dfs(0, -1, -1, dfs) || a[0] != 0) {
    printf("NO\n");
  } else {
    printf("YES\n");
    printf("%d\n", (int)ops.size());
    for (auto [x, y, w]: ops) {
      printf("%d %d %lld\n", x + 1, y + 1, w);
    }
  }
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();

  return 0;
}
