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
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    int n;
    scanf("%d", &n);
    vector<vector<pair<int, int>>> g(n);
    ll ans = 0;
    for (int i = 0; i < n - 1; i++) {
      int a, b, w;
      scanf("%d%d%d", &a, &b, &w);
      --a, --b;
      g[a].emplace_back(b, w);
      g[b].emplace_back(a, w);
      ans += 2 * w;
    }

    auto bfs = [&](int s) {
      vector<ll> d(n, -1);
      queue<int> q;
      d[s] = 0;
      q.push(s);

      while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (auto [u, w] : g[v]) {
          if (d[u] == -1) {
            d[u] = d[v] + w;
            q.push(u);
          }
        }
      }
      return d;
    };

    auto x = bfs(0);
    int id = max_element(x.begin(), x.end()) - x.begin();
    x = bfs(id);

    ans -= *max_element(x.begin(), x.end());
    printf("%lld\n", ans);

  }

  return 0;
}
