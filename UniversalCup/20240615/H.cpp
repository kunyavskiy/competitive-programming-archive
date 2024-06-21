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
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    auto check = [&](double l) {
      vector<double> ans(n + 1, 1e100);
      ans[0] = 0;
      double s = 0;
      int last = -1;
      for (auto x : a) {
        s += x - l;
        if (s >= 0) {
          last = std::lower_bound(ans.begin(), ans.end(), s) - ans.begin();
          ans[last] = s;
        } else {
          last = -1;
        }
      }
      return last >= k;
    };

    double l = 0;
    double r = 10000;
    for (int i = 0; i < 60; i++) {
      double mid = (l + r) / 2;
      if (check(mid)) {
        l = mid;
      } else {
        r = mid;
      }
    }
    printf("%.10lf\n", (l + r) / 2);
  }

  return 0;
}
