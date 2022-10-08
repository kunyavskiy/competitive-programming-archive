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

struct pt {
  double x, y;
  pt operator-(const pt&a) {
    return {x - a.x, y - a.y};
  }
  double dist() {
    return sqrt(x * x + y * y);
  }
};

double my_tan(double x) {
  if (x > M_PI / 2 - 0.0001) {
    double y = M_PI / 2- x;
    return 1.0 / y - y / 3 - y * y *y / 45;
  }
  return tan(x);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
//  freopen("d.out", "w", stdout);
#endif

  int n, L;
  while (scanf("%d%d", &n, &L) == 2) {
    vector<pt> p(n);
    vector<double> ang(n);
    vector<int> t(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &t[i]);
    }
    sort(t.begin(), t.end());
    for (int i = 0; i < n; i++) {
      ang[i] = M_PI * t[i] / L;
      p[i].x = cos(2 * M_PI * t[i] / L);
      p[i].y = sin(2 * M_PI * t[i] / L);
    }

    double ans_x = 0;
    double ans_y = 0;

    for (int i = 0; i < n; i++) {
      double weight = 0;
      double cur = 0;
      vector<double> cur2(n);
      vector<double> t(n);
      for (int j = n - 1; j >= 1; j--) {
        double b = ang[j] - ang[0];
        if (b < 0) b += M_PI;
        b /= 2;
        cur2[j] = cur;
        t[j] = my_tan(b);
        cur += 1.0 / t[j];
      }
      for (int j = 1; j < n; j++) {
        weight -= t[j] * cur2[j];
      }
      weight += (n - 1) * 1.0 * (n - 2) / 2;
//      eprintf("%lf\n", weight);
      weight /= n - 2;
      weight /= n - 1;
      ans_x += p[0].x * weight * 3 / n;
      ans_y += p[0].y * weight * 3 / n;
      rotate(p.begin(), p.begin() + 1, p.end());
      rotate(ang.begin(), ang.begin() + 1, ang.end());
//      break;
    }

    printf("%.18lf %.18lf\n", ans_x, ans_y);
    break;
  }

  return 0;
}
