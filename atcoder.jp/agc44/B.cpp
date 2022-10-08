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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> p(n * n);
    for (int& x : p) {
      scanf("%d", &x);
      --x;
    }

    vector<vector<int>> d(n, vector<int>(n));
    vector<vector<int>> c(n, vector<int>(n, 1));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        d[i][j] = min({i + 1, j + 1, n - i, n - j});
      }
    }

    ll ans = 0;
    queue<pair<int, int>> q;
    for (int id : p) {
      int row = id / n;
      int col = id % n;
      c[row][col] = 0;
      const pair<int, int> dv[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
      for (auto [dx, dy] : dv) {
        q.emplace(row + dx, col + dy);
      }
      while (!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        int dd;
        if (row < 0 || row >= n || col < 0 || col >= n) {
          dd = 0;
        } else {
          dd = d[row][col];
        }
        auto relax = [&](int row, int col, int dd) {
          if (row < 0 || row >= n || col < 0 || col >= n) {
            return;
          }
          dd += c[row][col];
          if (d[row][col] <= dd) return;
//          eprintf("! %d %d %d\n", row, col, dd);
          d[row][col] = dd;
          q.emplace(row, col);
        };
        for (auto [dx, dy] : dv) {
          relax(row + dx, col + dy, dd);
        }
      }
      ans += d[row][col];
//      eprintf("%d %d %d %d\n", id, row, col, d[row][col]);
    }
    printf("%lld\n", ans);
  }


  return 0;
}
