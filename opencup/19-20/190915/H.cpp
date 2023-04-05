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
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      --a, --b;
      g[a].push_back(b);
      g[b].push_back(a);
    }

    vector<double> ans(n, 1e9);
    ans[n - 1] = 0;
    priority_queue<pair<double, int>> q;
    q.emplace(0, n - 1);
    vector<multiset<double>> nexts(n);
    auto add = [&](int pos, double add_val) {
      auto& s = nexts[pos];
      s.insert(add_val);
      while (s.size() > 20) s.erase(--s.end());
      double value = 0;
      double best_value = 1e9;
      double prob = 1;
      int bad = 1;
      for (double x : s) {
        value += 0.75 * prob * (x + bad);
        bad++;
        prob *= 0.25;
        best_value = min(best_value, value + prob * (*s.begin() + bad + 1));
      }
      ans[pos] = best_value;
      q.emplace(-ans[pos], pos);
    };
    vector<bool> used(n, false);
    while (!q.empty()) {
      int v = q.top().second;
      q.pop();
      if (used[v]) continue;
      used[v] = true;
      for (int u : g[v]) {
        if (!used[u]) {
          add(u, ans[v]);
        }
      }
    }

    printf("%.18lf\n", ans[0]);
  }

  return 0;
}
