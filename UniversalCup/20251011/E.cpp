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
#include <numeric>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n), b(n);
    vector<int> c(m), d(m);
    for (int &x: a) scanf("%d", &x);
    for (int &x: b) scanf("%d", &x);
    for (int &x: c) scanf("%d", &x);
    for (int &x: d) scanf("%d", &x);

    auto encode=[&](int x, int y, int ty) { return (x * m + y) * 2 + ty;};
    auto decode=[&](int id) {
      int ty = id % 2;
      int x = id / (m * 2);
      int y = id / 2 % m;
      return make_tuple(x, y, ty);
    };

    priority_queue<pair<double, int>> pq;
    vector<vector<double>> ans[2];
    ans[0] = vector(n, vector<double>(m, 1e100));
    ans[1] = vector(n, vector<double>(m, 1e100));
    double result = 1e100;

    auto update = [&](int x, int y, int ty, double cost) {
      if (ans[ty][x][y] > cost) {
        ans[ty][x][y] = cost;
        pq.push(make_pair(-cost, encode(x, y, ty)));
      }
    };
    update(0, 0, 0, a[0]);
    update(0, 0, 1, c[0]);

    while (!pq.empty()) {
      auto [cost, id] = pq.top();
      cost *= -1;
      auto [x, y, ty] = decode(id);
      eprintf("%d %d %d %lf\n", x, y, ty, cost);
      pq.pop();
      if (ans[ty][x][y] != cost) continue;
      if (ty == 0) {
        if (x == n - 1 && y == m - 1) {
          result = min(result, cost + c.back());
        }
        if (y != m-1) {
          update(x, y + 1, ty, cost + c[y] + d[y]);
        }
        if (x != n-1) {
          int dy = 0;
          for (int yy = y; yy < m; yy++) {
            dy += c[yy];
            update(x+1, yy, !ty, cost + sqrt(dy * dy + b[x] * b[x]));
            dy += d[yy];
          }
        }
      } else {
        if (x == n - 1 && y == m - 1) {
          result = min(result, cost + a.back());
        }
        if (x != n-1) {
          update(x+1, y, ty, cost + a[x] + b[x]);
        }
        if (y != m-1) {
          int dx = 0;
          for (int xx = x; xx < n; xx++) {
            dx += a[xx];
            update(xx, y+1, !ty, cost + sqrt(dx * dx + d[y] * d[y]));
            dx += b[xx];
          }
        }
      }
    }
    printf("%.9lf\n", result);
  }

  return 0;
}
