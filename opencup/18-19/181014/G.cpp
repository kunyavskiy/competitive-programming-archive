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

ll d[250005][3][10][10];

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n, k;
  scanf("%d%d", &n, &k);
  k = min(k, n);
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  ll INF = (ll)1e18;

  for (int i = 0; i <= n; i++) {
    for (int j = 0; j < 3; j++) {
      for (int x = 0; x <= k; x++) {
        for (int y = 0; y <= k; y++) {
          d[i][j][x][y] = INF;
        }
      }
    }
  }

  d[0][1][0][0] = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 3; j++) {
      for (int x = 0; x <= k; x++) {
        for (int y = 0; y <= k; y++) {
          if (d[i][j][x][y] == INF) continue;
          if (x < k && j > 0) {
            d[i + 1][j - 1][x + 1][y] = min(d[i + 1][j - 1][x + 1][y], d[i][j][x][y] + a[i]);
          }
          if (y < k) {
            d[i + 1][2][x][y + 1] = min(d[i + 1][2][x][y + 1], d[i][j][x][y]);
          }
          d[i + 1][2][x][y] = min(d[i + 1][2][x][y], d[i][j][x][y] + a[i]);
          if (j > 0) {
            d[i + 1][j - 1][x][y] = min(d[i + 1][j - 1][x][y], d[i][j][x][y]);
          }
        }
      }
    }
  }
  ll res = INF;
  for (int j = 1; j < 3; j++) {
    for (int x = 0; x <= k; x++) {
      res = min(res, d[n][j][x][x]);
    }
  }
  cout << res;

  return 0;
}
