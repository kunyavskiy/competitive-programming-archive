#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

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

void dfs(const vector<vector<int>> &g, const vector<vector<int>> &w, vector<int>& c, int v, int p) {
  for (int i = 0; i < (int)g[v].size(); i++) {
    int u = g[v][i];
    int cc = w[v][i];
    if (u == p) continue;
    c[u] = c[v] ^ cc;
    dfs(g, w, c, u, v);
  }
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<int>> g(n), w1(n), w2(n);
    for (int i = 0; i < n - 1; i++) {
      int a, b, c1, c2;
      scanf("%d%d%d%d", &a, &b, &c1, &c2);
      --a, --b;
      g[a].push_back(b);
      w1[a].push_back(c1);
      w2[a].push_back(c2);
      g[b].push_back(a);
      w1[b].push_back(c1);
      w2[b].push_back(c2);
    }

    auto calc = [&](const vector<vector<int>> &w) {
      auto vc = vector<int>(n);
      dfs(g, w, vc, 0, -1);
      int tot_xor = accumulate(vc.begin(), vc.end(), 0, bit_xor<>());
      for (int &x : vc) {
        x ^= tot_xor;
      }
      return vc;
    };

    auto vc1 = calc(w1);
    auto vc2 = calc(w2);
    sort(vc1.begin(), vc1.end());
    sort(vc2.begin(), vc2.end());

    printf("%s\n", (vc1 == vc2) ? "YES" : "NO");
  }

  return 0;
}
