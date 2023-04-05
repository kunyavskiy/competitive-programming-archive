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

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
//  freopen("a.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<int>> e(n);
    for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      u--; v--;
      if (u > v) swap(u, v);
      e[v].push_back(u);
      e[u].push_back(v);
    }

    vector<int> p(n);
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
      p[i] = i;
      cnt[i] = 1;
    }
    vector<set<int>> st(n);
    for (int i = 0; i < n; i++) {
      for (int to : e[i]) {
        if (to > i) {
          st[i].insert(to);
        }
      }
    }

    function<int(int)> get = [&](int x) {
      if (x == p[x]) return x;
      return p[x] = get(p[x]);
    };
    function<void(int, int)> uni = [&](int u, int v) {
      u = get(u);
      v = get(v);
      if (u == v) return;
      if (cnt[u] < cnt[v]) swap(u, v);
      p[v] = u;
      cnt[u] += cnt[v];
      for (int to : st[v]) st[u].insert(to);
      st[v] = set<int>();
    };

    int ans = 1;

    for (int i = 0; i < n; i++) {
      for (int to : e[i]) {
        if (to < i) {
          uni(i, to);
        }
      }
      int x = get(i);
      auto it = st[x].find(i);
      if (it != st[x].end()) st[x].erase(it);
      ans = 1LL * ans * (n - st[x].size()) % MOD;
//      db2(i, st[x].size());
    }

    cout << ans << endl;
  }

  return 0;
}
