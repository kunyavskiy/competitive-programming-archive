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
  freopen("p7.in", "r", stdin);
  freopen("p7.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &x[i], &y[i]);
    }
    for (int i = n - 1; i >= 0; i--) {
      x[i] -= x[0];
      y[i] -= y[0];
    }

    ld min_tg = -1e100;
    for (int i = 1; i < n - 1; i++) {
      __int128_t A0 = x[i], B0 = __int128_t(x[i]) * x[i], C0 = y[i];
      __int128_t A1 = x[n - 1], B1 = __int128_t(x[n - 1]) * x[n - 1], C1 = y[n - 1];

      __int128_t d = A0 * B1 - A1 * B0;
      ld a = (ld) (C0 * B1 - C1 * B0) / d;
      ld b = (ld) (A0 * C1 - C0 * A1) / d;
#ifdef LOCAL
//      eprintf("%lf %lf %lf\n", (double)A0, (double)B0, (double)C0);
//      eprintf("%lf %lf %lf\n", (double)A1, (double)B1, (double)C1);
//      eprintf("%lf %lf\n", (double)a, (double)b);
//      eprintf("%lf %lf\n", double(A0 * a + B0 * b), (double)C0);
//      eprintf("%lf %lf\n", double(A1 * a + B1 * b), (double)C1);
      assert(fabs(A0 * a + B0 * b - C0) < 1e-6);
      assert(fabs(A1 * a + B1 * b - C1) < 1e-6);
#endif
      min_tg = max(min_tg, a);
    }

    auto check = [&](double tg_ang) {
      if (tg_ang < min_tg - 1e-9) {
        return 1e100;
      }
      double cos2_ans = 1.0 / (1 + tg_ang * tg_ang);
      double v2 = 5.0 * double(x[n - 1]) * x[n - 1] / cos2_ans / (x[n - 1] * tg_ang - y[n - 1]);
      if (v2 < 0) {
        return 1e100;
      }
      return sqrt(v2);
    };

    double ans = 1e100;
    ans = min(ans, check(min_tg));
    double d = sqrt(ld(x[n - 1]) * x[n - 1] + ld(y[n - 1]) * y[n - 1]);
    ans = min(ans, check((y[n - 1] + d) / x[n - 1]));
    ans = min(ans, check((y[n - 1] - d) / x[n - 1]));
    printf("%.18lf\n", ans);
  }

  return 0;
}
