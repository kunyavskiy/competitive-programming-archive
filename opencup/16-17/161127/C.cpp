#include <bits/stdc++.h>
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#define TASKNAME "C"

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

const double pi = acos(-1.0);

struct Point {
  double x, y;
  Point() {}
  Point(double x, double y) : x(x), y(y) {}

  double sqrDistTo(const Point & p) const {
    return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
  }

  double distTo(const Point & p) const {
    return sqrt(sqrDistTo(p));
  }

  Point operator - (const Point & p) const {
    return Point(x - p.x, y - p.y);
  }

  double operator * (const Point & p) const {
    return x * p.y - y * p.x;
  }

  double operator % (const Point & p) const {
    return x * p.x + y * p.y;
  }

  double polarAngle(const Point & p) const {
    return (double)atan2((long double)(*this * p), (long double)(*this % p));
  }
};

double getLeft(char ch) {
  if (ch == 'C') {
    return pi / 2.0;
  } else if (ch == 'S') {
    return 2;
  } else if (ch == 'T') {
    return 1.5;
  } else {
    assert(0);
  }
}

double getTangent(char ch1, char ch2, int len) {
  if (ch1 == 'T') {
    assert(ch2 != 'T');
    Point p0(0.5, sqrt(3.0) / 2.0);
    if (ch2 == 'S') {
      return p0.distTo(Point(len, 1)) + 0.5;
    } else if (ch2 == 'C') {
      Point c = Point(len + 0.5, 0.5);
      double d = sqrt(p0.sqrDistTo(c) - 0.25);
      double alpha = pi/2 - atan(0.5 / d);
      double beta = fabs((p0 - c).polarAngle(Point(len + 0.5, 1.0) - c));
      eprintf("alpha %.10lf beta %.10lf\n", alpha, beta);
      return d + (beta - alpha) * 0.5;
    } else {
      assert(0);
    }
  } else {
    assert(len == 0);
    return 0.0;
  }
}

int main() {
#ifdef LOCAL
  assert(freopen(TASKNAME".in", "r", stdin));
  assert(freopen(TASKNAME".out", "w", stdout));
#endif

  int n;
  scanf("%d", &n);
  static char s[30];
  scanf("%s", s);

  double len = 0;
  len += n - 1;
  len += getLeft(s[0]);
  len += getLeft(s[n - 1]);
  int L = 0;
  int R = n - 1;
  while (L <= R && s[L] == 'T') { ++L; }
  while (L <= R && s[R] == 'T') { --R; }
  if (L <= R) {
    len += (R - L);
    len += getTangent(s[0], s[L], L);
    len += getTangent(s[n - 1], s[R], n - 1 - R);
  } else {
    len += n - 1;
  }
  printf("%.10lf\n", len);

  return 0;
}
