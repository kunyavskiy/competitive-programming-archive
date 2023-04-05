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
typedef double dbl;

const dbl PI = acos(-1.0);
const dbl PHI = (sqrt(5.0) - 1) / 2;
const dbl EPS = 1e-9;

dbl sqr(dbl x) {
  return x * x;
}

double solve(dbl v, dbl d, dbl w) {
  dbl h = w / 2;

  dbl aL = 0, aR = 1e9;
  for (int it1 = 0; it1 < 100; it1++) {
    dbl aM = (aL + aR) / 2;

    bool fl = 0;
    if (aM >= v * v / (2 * d)) {
      fl = 1;
    } else {
      /*auto f = [&](dbl ang) {
        dbl ax = -aM * cos(ang);
        dbl ay = aM * sin(ang);
        dbl t = (v - sqrt(v * v - 2 * s * ax)) / ax;

        dbl ch = ay / 2 * sqr(t);
        return ch;
      };
      double L = PI / 2, R = PI;
      double fL = f(R - (R - L) * PHI);
      double fR = f(L + (R - L) * PHI);
      for (int it2 = 0; it2 < 100; it2++) {
        if (fL > fR) {
          R = L + (R - L) * PHI;
          fR = fL;
          fL = f(R - (R - L) * PHI);
        } else {
          L = L - (R - L) * PHI;
          fL = fR;
          fR = f(L + (R - L) * PHI);
        }
      }
      fl = max(fL, fR) >= h;*/
      double a = aM;

      dbl L = 0, R = 1e9;
      for (int it2 = 0; it2 < 100; it2++) {
        dbl M = (L + R) / 2.0;

        dbl l = M;
        dbl t1 = sqrt(2 * sqrt(l * l + h * h) / a);
        dbl t2 = (d + l) / v;
        if (t1 <= t2) R = M;
        else L = M;
      }
      dbl l = R;
      dbl ax = a * l / sqrt(l * l + h * h);

      dbl t1 = sqrt(2 * sqrt(l * l + h * h) / a);
      dbl t2 = (d + l) / v;
      assert(fabs(t1 - t2) < 1e-6);

      dbl A = ax;
      dbl B = -v;
      dbl C = d;

      auto calc = [&](dbl x) {
        return A * x * x + B * x + C;
      };

      bool ok = 1;
      ok &= calc(0) >= -EPS;
      ok &= calc(t1) >= -EPS;
      dbl mid = -B / (2 * A);
      if (0 <= mid && mid <= t1) ok &= calc(mid) >= -EPS;

      if (ok) fl = 1;
    }

    if (fl) aR = aM;
    else aL = aM;
  }
  return aR;
}

int main() {
#ifdef LOCAL
  freopen("p2.in", "r", stdin);
  //freopen("p2.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int v, d, w;
    scanf("%d%d%d", &v, &d, &w);

    printf("%.17f\n", solve(v, d, w));
  }

  return 0;
}
