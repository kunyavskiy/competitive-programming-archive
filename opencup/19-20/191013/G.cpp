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

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  int n, m, s, t;
  while (scanf("%d%d%d%d", &n, &m, &s, &t) == 4) {
    s--; t--;
    vector<vector<int>> g(n);
    vector<vector<pair<int, int>>> e(n);
    for (int i = 0; i < m; i++) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      u--; v--;
      g[v].push_back(u);
      e[u].push_back({c, v});
    }
    for (int i = 0; i < n; i++) sort(e[i].begin(), e[i].end());

    vector<char> vis(n);
    queue<int> q;
    vis[t] = 1;
    q.push(t);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int to : g[v]) {
        if (!vis[to]) {
          vis[to] = 1;
          q.push(to);
        }
      }
    }

    vector<pair<int, int>> nxt(n);
    for (int i = 0; i < n; i++) {
      nxt[i] = {-1, i};
      for (auto o : e[i]) {
        if (vis[o.second]) {
          nxt[i] = o;
          break;
        }
      }
    }

    if (!vis[s]) {
      printf("IMPOSSIBLE\n");
    } else {
      vector<int> ans;
      vector<int> used(n);

      int v;
      for (v = s; !used[v]; v = nxt[v].second) {
        if (v == t) break;
        used[v] = 1;
        ans.push_back(nxt[v].first);
      }

      if (v == t) {
        for (int i = 0; i < (int)ans.size(); i++) printf("%d%c", ans[i], " \n"[i + 1 == (int)ans.size()]);
      } else {
        printf("TOO LONG\n");
      }
    }
  }

  return 0;
}
