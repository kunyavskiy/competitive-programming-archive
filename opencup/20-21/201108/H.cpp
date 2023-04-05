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

vector<vector<pair<int, int>>> g;
vector<bool> have[3];
int m[3];
double ans;

array<int, 3> dfs(int v, int p) {
  array<int, 3> res{};
  for (int i = 0; i < 3; i++) {
    if (have[i][v]) {
      res[i]++;
    }
  }
  for (auto [x, w] : g[v]) {
    if (x == p) continue;
    auto inner = dfs(x, v);
    double p1 = 1, p2 = 1;
    for (int i = 0; i < 3; i++) {
      res[i] += inner[i];
      double pr = inner[i] * 1.0 / m[i];
      p1 *= pr;
      p2 *= 1.0 - pr;
    }
    ans += (1 - p1 - p2) * w;
  }
  return res;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    g = vector<vector<pair<int, int>>>(n);
    for (int i = 0; i < n-1; i++) {
      int x, y, w;
      scanf("%d%d%d", &x, &y, &w);
      --x, --y;
      g[x].emplace_back(y, w);
      g[y].emplace_back(x, w);
    }
    for (int i = 0; i < 3; i++) {
      have[i] = vector<bool>(n);
      scanf("%d", &m[i]);
      for (int j = 0; j < m[i]; j++) {
        int a;
        scanf("%d", &a);
        --a;
        have[i][a] = true;
      }
    }
    ans = 0;
    dfs(0, -1);
    printf("%.18f\n", ans);
  }

  return 0;
}
