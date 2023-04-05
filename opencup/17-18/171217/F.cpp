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

#ifdef LOCAL
#define INTERACTOR
#endif

const double eps = 1e-9;
typedef long long ll;
typedef long double ld;

double f0, f1;
#ifdef INTERACTOR

const double R = 1.5;
const double S = 1.0;
const double L = 0.6;
const int K = 10;
const double V = 0.5;
const int T = 100;
const int M = 20000;

struct Point {
  double x, y;

  void read() {
    scanf("%lf%lf", &x, &y);
  }

  Point operator * (double k) const {
    return Point({x * k, y * k});
  }

  Point operator - (const Point & p) const {
    return Point({x - p.x, y - p.y});
  }

  double polarAngle() const {
    return atan2(y, x);
  }
};
int n;
vector<Point> p;
Point p0;
double ang;
double v0, v1;

double uniform_random(double L, double R) {
  return rand() * 1.0 / RAND_MAX * (R - L) + L;
}

double make_noise(double x) {
  for (int i = 0; i < K; ++i) {
    x += uniform_random(-0.1, 0.1);
  }
  if (x > 1.0) x = 1.0;
  if (x < -1.0) x = -1.0;
  return x;
}
#endif

void getData() {
#ifdef INTERACTOR
  double d = getDist();

#else
  scanf("%lf %lf", &f0, &f1);
  if (fabs(f0 + 1) < eps) {
    exit(0);
  }
#endif
}

void go(double s0, double s1) {
  printf("%.10lf %.10lf\n", s0, s1);
  fflush(stdout);
#ifdef INTERACTOR
  v0 = make_noise(s0);
  v1 = make_noise(s1);
  for (int i = 0; i < T; ++i) {
    p0 = Point({cos(ang), sin(ang)}) * (V * (v0 + v1) / (2.0 * T));
    ang += (v1 - v0) * V / (2.0 * R * T);
  }
#endif
  getData();
}


int main() {
#ifdef INTERACTOR
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);

  scanf("%d", &n);
  p.resize(n);
  for (int i = 0; i < n; ++i) {
    p[i].read();
  }
  p0 = p[0];
  ang = (p[1] - p[0]).polarAngle() + uniform_random(-0.2, 0.2);

#endif

  getData();
  while (1) {
    if (f0 > 0.8 && f1 > 0.8) {
      go(1, 1);
    } else if (f0 < f1) {
      go(0, 1);
    } else {
      go(1, 0);
    }
  }

  return 0;
}
