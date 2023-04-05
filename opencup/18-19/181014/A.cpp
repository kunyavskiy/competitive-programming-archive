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

const int INF = 1e9;

namespace hld {
  const int N = 1 << 19;
  int par[N], heavy[N], h[N];
  int root[N], pos[N];
  int n;
  vector<vector<int> > e;
  vector<pair<int, int>> vct[N];

  int dfs(int v) {
    int sz = 1, mx = 0;
    for (int to : e[v]) {
      if (to == par[v]) continue;
      par[to] = v;
      h[to] = h[v] + 1;
      int cur = dfs(to);
      if (cur > mx) heavy[v] = to, mx = cur;
      sz += cur;
    }
    return sz;
  }

  void init(vector<vector<int> > _e) {
    e = _e;
    n = e.size();
    memset(heavy, -1, sizeof(heavy[0]) * n);
    par[0] = -1;
    h[0] = 0;
    dfs(0);
    for (int i = 0, cpos = 0; i < n; i++) {
      vct[i].clear();
      if (par[i] == -1 || heavy[par[i]] != i) {
        int mxh = 0;
        for (int j = i; j != -1; j = heavy[j]) {
          vct[i].push_back({h[j], 0});
          mxh = max(mxh, h[j]);
          root[j] = i;
          pos[j] = cpos++;
        }
        vct[i].push_back({vct[i].back().first + 1, 0});
        reverse(vct[i].begin(), vct[i].end());
      }
    }
  }
}
using namespace hld;

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  //freopen("a.out", "w", stdout);
#endif

  int n, C, Q;
  scanf("%d%d%d", &n, &C, &Q);
  vector<vector<int>> e(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    scanf("%d%d", &u, &v);
    u--; v--;
    e[u].push_back(v);
    e[v].push_back(u);
  }
  hld::init(e);

  //map<int, int> mp1;
  //map<int, int> mp2;
  vector<int> mp1(C + 1), mp2(n + 1);

  auto add = [&](int id, int delta) {
    if (id == 0) return;
    mp2[mp1[id]]--;
    mp1[id] += delta;
    mp2[mp1[id]]++;
  };
  for (int i = 1; i <= C; i++) {
    mp1[i] = 0;
    mp2[0]++;
  }

  while (Q--) {
    int v, c, m;
    scanf("%d%d%d", &v, &c, &m);
    v--;

    add(c, h[v] + 1);
    while (v != -1) {
      int r = root[v];
      while (vct[r].back().first <= h[v]) {
        auto o = vct[r].back();
        vct[r].pop_back();
        add(o.second, -(vct[r].back().first - o.first));
        if (vct[r].back().first > h[v] + 1) {
          add(o.second, +(vct[r].back().first - (h[v] + 1)));
          vct[r].push_back({h[v] + 1, o.second});
        }
      }
      vct[r].push_back({h[root[v]], c});
      v = par[root[v]];
    }
    int res = mp2[m];
    res -= mp1[c] == m;
    res += mp1[c] == m + 1;
    printf("%d\n", res);
  }


  return 0;
}
