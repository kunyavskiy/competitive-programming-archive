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

ll sqr(ll x) {
  return x * x;
}

const double INF = 1e18;

int main() {
#ifdef LOCAL
  freopen("p2.in", "r", stdin);
//  freopen("p2.out", "w", stdout);
#endif

  int n, m, h;
  while (cin >> n >> m >> h) {
    vector<pair<int, int>> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i].first >> a[i].second;
    for (int i = 0; i < m; i++) cin >> b[i].first >> b[i].second;

    auto dist = [&](int i, int j) {
      ll res = sqr(a[i].first - b[j].first) + sqr(a[i].second - b[j].second) + sqr(h);
      return sqrt(res);
    };

    double ans = INF;
    vector<pair<int, int>> vans;

    for (int s = 0; s < m; s++) {
      vector<vector<double>> dp(n + 1, vector<double>(m + 1, INF));
      vector<vector<pair<int, int>>> pr(n + 1, vector<pair<int, int>>(m + 1, make_pair(-1, -1)));
      pr[0][0] = make_pair(0, 0);
      dp[0][0] = 0;

      auto upd = [&](int ni, int nj, int i, int j) {
        if (ni <= n && nj <= m) {
          double cur = dp[i][j];
          cur += dist(ni % n, nj % m);
          if (dp[ni][nj] > cur) {
            dp[ni][nj] = cur;
            pr[ni][nj] = {i, j};
          }
        }
      };

      for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= m; j++) {
          upd(i, j + 1, i, j);
          upd(i + 1, j, i, j);
          upd(i + 1, j + 1, i, j);
        }
      }

      if (ans > dp[n][m]) {
        ans = dp[n][m];
        int ci = n, cj = m;
        vans.clear();
        while (ci || cj) {
          vans.push_back({ci % n, (cj + s) % m});
          auto o = pr[ci][cj];
          ci = o.first;
          cj = o.second;
        }
        reverse(vans.begin(), vans.end());
      }

      rotate(b.begin(), b.begin() + 1, b.end());
    }
    printf("%.17f %d\n", ans, (int)vans.size());
    for (auto o : vans) printf("%d %d\n", o.first + 1, o.second + 1);
  }

  return 0;
}
