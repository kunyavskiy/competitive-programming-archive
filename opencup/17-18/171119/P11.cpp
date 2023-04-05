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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

double tangent(double c, double v, double x, double a) {
  double k = c / x;
  double b = c * log(x) + v - k * x;
  return k * a + b;
}

bool check(int n, double a, double b, double c, double v) {
  for (int i = 0; i < n; i++) {
    double l = a;
    double r = b;
    double val = c * log(a) + v;
    if (tangent(c, -v, b, a) < val) {
      return true;
    }
    for (int j = 0; j < 100; j++) {
      double m = (l + r) / 2;
      if (tangent(c, -v, m, a) < val) {
        l = m;
      } else {
        r = m;
      }
    }

    double K = c / l;
    double B = c * log(l) - v - K * l;

#ifdef LOCAL
    assert(abs(K * a + B - (c * log(a) + v)) < 1e-9);
#endif

    l = a;
    r = b;

    if (K * r + B < c * log(r) + v) {
      return true;
    }

    for (int j = 0; j < 100; j++) {
      double m = (l + r) / 2;
      if (K * m + B < c * log(m) + v) {
        l = m;
      } else {
        r = m;
      }
    }

    a = l;
  }
  return false;
}

void solve() {
  int n;
  double c, a, b;
  scanf("%d%lf%lf%lf", &n, &c, &a, &b);

  double l = 0;
  double r = 1e6;
  for (int i = 0; i < 100; i++) {
    double m = (l + r) / 2;
    if (check(n, a, b, c, m)) {
      r = m;
    } else {
      l = m;
    }
  }
  printf("%.18f\n", l);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int t;
  scanf("%d", &t);
  while (t-->0)
    solve();


  return 0;
}
