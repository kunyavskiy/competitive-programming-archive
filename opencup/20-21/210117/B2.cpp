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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
    }
    vector<double> dp((1 << n));
    for (int mask = 1; mask < (1 << n); mask++) {
      vector<double> as, bs;
      double l = 0;
      double r = 1e9;
      for (int it = 0; it < 60; it++) {
        double mid = (l + r) / 2;
        double min_sum = 0, max_sum = 0;
        bool bad = false;
        for (int i = 0; i < n; i++) {
          if (mask & (1 << i)) {
            // v[i] + (dp[mask ^ (1 << i)] - v[i]) * p[i] \le mid
            double a = v[i];
            double b = dp[mask ^ (1 << i)] - v[i];
            double min_p = 0;
            double max_p = 1;
            if (abs(b) < 1e-9) {
              if (v[i] > mid) {
                bad = true;
              }
            } else if (b > 0) {
              max_p = min(max_p, (mid - a) / b);
            } else {
              min_p = max(min_p, (mid - a) / b);
            }
            if (min_p > max_p) {
              bad = true;
            } else {
              min_sum += min_p;
              max_sum += max_p;
            }
          }
        }
        if (!bad && min_sum <= 1 && 1 <= max_sum) {
          r = mid;
        } else {
          l = mid;
        }
      }
      dp[mask] = (l + r) / 2;
    }
    printf("%.18lf\n", dp.back());
  }

  return 0;
}
