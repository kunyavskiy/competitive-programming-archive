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
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  int n,k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<vector<int>> v(n, vector<int>(n));
    for (auto &x : v) {
      for (auto &y : x) {
        scanf("%d", &y);
        --y;
      }
    }
    vector<vector<pair<int, int>>> p(k);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        p[v[i][j]].emplace_back(i, j);
      }
    }

    if (std::any_of(p.begin(), p.end(), [](const vector<pair<int, int>>&x) { return x.empty();})) {
      printf("-1\n");
      continue;
    }

    vector<vector<int>> dp(n, vector<int>(n, -1));

    for (auto [x, y] : p.back()) {
      dp[x][y] = 0;
    }

    for (int i = k - 2; i >= 0; i--) {
      for (auto [x1, y1] : p[i]) {
        dp[x1][y1] = numeric_limits<int>::max() / 2;
        for (auto [x2, y2] : p[i+1]) {
          dp[x1][y1] = min(dp[x1][y1], dp[x2][y2] + abs(x1 - x2) + abs(y1 - y2));
        }
      }
    }

    int ans = numeric_limits<int>::max();
    for (auto [x, y] : p[0]) {
      ans = min(ans, dp[x][y]);
    }
    printf("%d\n", ans);
  }

  return 0;
}
