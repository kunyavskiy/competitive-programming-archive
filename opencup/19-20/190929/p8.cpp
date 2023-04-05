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

double read() {
  double x;
  scanf("%lf", &x);
  return x;
}

struct Acc {
  double a, mul, add;

  Acc(double a0, double a90, double a180, double a270) {
    add = (a0 + a180) / 2.0;
    a = -atan2(a90 - add, a0 - add);
    if (a > M_PI / 2) a -= M_PI;
    if (a < -M_PI / 2) a += M_PI;
    mul = (a0 - add) / cos(a);
#ifdef LOCAL
    assert(abs(cos(a) * mul + add - a0) < 1e-5);
    assert(abs(cos(a + M_PI / 2) * mul + add - a90) < 1e-5);
    assert(abs(cos(a + M_PI) * mul + add - a180) < 1e-5);
    assert(abs(cos(a + 3 * M_PI / 2) * mul + add - a270) < 1e-5);
#endif
  }
};

double sacos(double x) {
  if (x > 1) x = 1;
  if (x < -1) x = -1;
  return acos(x);
}


int main() {
#ifdef LOCAL
  freopen("p8.in", "r", stdin);
  freopen("p8.out", "w", stdout);
#endif

  vector<double> A(4), B(4);
  for (int i = 0; i < 4; i++) {
    A[i] = read();
    B[i] = read();
  }
  Acc a(A[3], A[0], A[1], A[2]), b(B[2], B[3], B[0], B[1]);
  a.a += M_PI / 2;
  b.a += M_PI;

#ifdef LOCAL
  eprintf("%lf %lf\n", a.a / M_PI * 180, b.a/ M_PI * 180);

  for (int i = 0; i < 4; i++) {
    eprintf("%lf %lf\n", cos(a.a + M_PI / 2 * i) * a.mul + a.add, A[i]);
    assert(abs(cos(a.a + M_PI / 2 * i) * a.mul + a.add - A[i]) < 1e-5);
    eprintf("%lf %lf\n", cos(b.a + M_PI / 2 * i) * b.mul + b.add, B[i]);
    assert(abs(cos(b.a + M_PI / 2 * i) * b.mul + b.add - B[i]) < 1e-5);
  }
#endif


  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    double av = read();
    double bv = read();

    double ca = sacos((av - a.add) / a.mul);
    double bres1 = cos( -a.a + ca + b.a) * b.mul + b.add - bv;
    double bres2 = cos(-a.a - ca + b.a) * b.mul + b.add - bv;
    if (abs(bres1) < abs(bres2)) {
      ca = -a.a + ca;
    } else {
      ca = -a.a - ca;
    }
    while (ca < 0) ca += 2 * M_PI;
    while (ca >= 2 * M_PI) ca -= 2 * M_PI;
    printf("%.18lf\n", ca / M_PI * 180);
  }

  return 0;
}
