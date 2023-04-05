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


pair<double, double> solve(double b, double t, double x0, double v0) {
  const double g = 9.81;
  // g * t / b + c1 + c2 * e^{-bt}

  double C2 = -(v0 - g/b) / b;
  double C1 = x0 - C2;
#ifdef LOCAL
  assert(fabs(C1 + C2 - x0) < 1e-9);
  assert(fabs((-b * C2 + g / b) - v0) < 1e-9);
#endif
  return {g * t / b + C1  + C2 * exp(-b * t), g / b + C2 * -b * exp(-b * t)};
}

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

  double m, b1, b2, t1, h;
  while (scanf("%lf%lf%lf%lf%lff\n",&m, &b1, &b2, &t1, &h) == 5) {
    b1 /= m;
    b2 /= m;

    int q;
    scanf("%d", &q);

    auto get_h = [&](double t) {
      auto [x, v] = solve(b1, min(t, t1), 0, 0);
      if (t > t1) {
        std::tie(x, v) = solve(b2, t - t1, x, v);
      }
      return x;
    };

    for (int i = 0; i < q; i++) {
      double t;
      scanf("%lf", &t);
      printf("%.18lf\n", get_h(t));
    }
    double l = t1;
    double r = 1e10;
    for (int it = 0; it < 60; it++) {
      double m = (l + r) / 2;
      if (get_h(m) < h) {
        l = m;
      } else {
        r = m;
      }
    }
    printf("%.18lf\n", (l + r) / 2);
  }

  return 0;
}
