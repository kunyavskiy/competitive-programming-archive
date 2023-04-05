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
      double min_mid = 0, max_mid = 1e10;
      double min_sum_mid = 0, min_sum_const = 0;
      double max_sum_mid = 0, max_sum_const = 0;
      for (int i = 0; i < n; i++) {
        if (mask & (1 << i)) {
          // v[i] + (dp[mask ^ (1 << i)] - v[i]) * p[i] \le mid
          double a = v[i];
          double b = dp[mask ^ (1 << i)] - v[i];
          double min_p = 0;
          double max_p = 1;
          if (b >= -1e-9) {
            max_mid = min(max_mid, a);
          } else {
            min_mid = max(min_mid, a + b);
          }
        }
      }
      dp[mask] = (l + r) / 2;
    }
    printf("%.18lf\n", dp.back());
  }

  return 0;
}
