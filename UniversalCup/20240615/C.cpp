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

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y)                                                              \
  cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z)                                                           \
  cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y   \
       << ", " << z << ")\n"
#define dbv(a)                                                                 \
  cerr << #a << " = ";                                                         \
  for (auto xxxx : a)                                                          \
    cerr << xxxx << " ";                                                       \
  cerr << endl

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
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    int n;
    scanf("%d",&n);
    vector<vector<int>> a(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        scanf("%d", &a[i][j]);
      }
    }

    std::function LU = [&](int x, int y) { return x <= n/2 && y <= n/2; };
    std::function LD = [&](int x, int y) { return x <= n/2 && y >= n/2; };
    std::function RU = [&](int x, int y) { return x >= n/2 && y <= n/2; };
    std::function RD  = [&](int x, int y) { return x >= n/2 && y >= n/2; };

    auto check = [&](vector<vector<std::function<bool(int, int)>>> s) {
      long long sum = 0;
      for (auto l: s) {
        int min = std::numeric_limits<int>::max();
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            bool all = true;
            for (auto c: l) {
              if (!c(i, j)) {
                all = false;
              }
            }
            if (all) {
              min = std::min(min, a[i][j]);
            }
          }
        }
        sum += min;
      }
      return sum;
    };

    long long ans = min({
        check({{LU, LD, RU, RD}}),

        check({{LU, LD}, {RU, RD}}),
        check({{LU, RU}, {LD, RD}}),


        check({{LU, RU}, {LD}, {RD}}),
        check({{LU, LD}, {RU}, {RD}}),


        check({{LD, RD}, {LU}, {RU}}),
        check({{RU, RD}, {LU}, {LD}}),


        check({{LU}, {RU}, {LD}, {RD}}),
    });

    printf("%lld\n", ans);
  }

  return 0;
}
