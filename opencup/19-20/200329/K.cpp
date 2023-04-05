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
#include <random>

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
typedef double dbl;


const int INF = 1e9;
const double PI = acos(-1.0);

struct pt {
  double x[3];

  pt() {}
  pt(dbl x0, dbl x1, dbl x2) {
    x[0] = x0;
    x[1] = x1;
    x[2] = x2;
  }

  void read() {
    scanf("%lf%lf%lf", &x[0], &x[1], &x[2]);
  }

  void print() {
    db3(x[0], x[1], x[2]);
  }

  pt operator- (const pt &p) const {
    pt res;
    for (int i= 0; i< 3; i++) res.x[i] = x[i] - p.x[i];
    return res;
  }

  pt operator+ (const pt &p) const {
    pt res;
    for (int i= 0; i< 3; i++) res.x[i] = x[i] + p.x[i];
    return res;
  }

  pt operator* (dbl d) const {
    pt res;
    for (int i= 0; i< 3; i++) res.x[i] = x[i] * d;
    return res;
  }

  dbl operator% (const pt &p) const {
    dbl res = 0;
    for (int i = 0; i < 3; i++) res += x[i] * p.x[i];
    return res;
  }

  pt operator* (const pt &p) const {
    pt res;
    res.x[0] = x[1] * p.x[2] - x[2] * p.x[1];
    res.x[1] = -(x[0] * p.x[2] - x[2] * p.x[0]);
    res.x[2] = x[0] * p.x[1] - x[1] * p.x[0];
    return res;
  }

  dbl d2() const {
    return *this % *this;
  }

  dbl d() const {
    return sqrt(d2());
  }

  pt norm() const {
    return *this * (1.0 / d());
  }
};

const int ITERS = 111;
const dbl PHI = (sqrt(5.0) - 1) / 2;

dbl tern(dbl L, dbl R, function<dbl(dbl)> f) {
  dbl fL = f(R - (R - L) * PHI);
  dbl fR = f(L + (R - L) * PHI);
  for (int it = 0; it < ITERS; it++) {
    if (fL > fR) {
      fR = fL;
      R = L + (R - L) * PHI;
      fL = f(R - (R - L) * PHI);
    } else {
      fL = fR;
      L = R - (R - L) * PHI;
      fR = f(L + (R - L) * PHI);
    }
  }
  return max(fL, fR);
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
#endif


  int T;
  scanf("%d", &T);
  while (T--) {
    pt sun;
    sun.read();

    pt star;
    star.read();
    dbl rad;
    scanf("%lf", &rad);

    double max_ang = asin(rad / (star - sun).d());

    auto can_see = [&](const  pt &p) {
      pt dir1 = star - sun;
      pt dir2 = p - sun;

      double ang = atan2((dir1 * dir2).d(), dir1 % dir2);
      return abs(ang) < max_ang;
    };

    dbl A, B, C, D;
    scanf("%lf%lf%lf%lf", &A, &B, &C, &D);
    double Z = A * A + B * B + C * C;
    Z = sqrt(Z);
    A /= Z;
    B /= Z;
    C /= Z;
    D /= Z;
    pt norm(A, B, C);
    norm = norm * (1.0 / norm.d());

    auto dist = [&](const pt &p) {
      return A * p.x[0] + B * p.x[1] + C * p.x[2] + D;
    };
    auto sign = [&](double d) {
      if (d > 0) return  1;
      if (d < 0) return -1;
      return 0;
    };
    auto proj = [&](const pt &from, const pt &to) {
      double t1 = from % norm;
      double t2 = to % norm;
      pt res = to - norm * (t2 - t1);

      return res;
    };

    auto start_sign = sign(dist(sun));

    auto find_max = [&](pt start, pt v, function<bool(pt)> ok) {
      dbl vlen = sqrt(v.d2());
      assert(vlen > 1e-9);
      v = v * (1 / vlen);


      dbl L = 0, R = 1e14;
      for (int it = 0; it < 100; it++) {
        dbl M = (L + R) / 2;
        pt p = start + v * M;
        if (ok(p)) L = M;
        else R = M;
      }
      return start + v * L;
    };
    auto center = find_max(sun, star - sun, [&](pt p) {
      return sign(dist(p)) == start_sign;
    });

    pt v1 = proj(center, sun) - center;
    assert((v1 % norm) < 1e-9);

    if (v1.d2() < 1e-9) {
      v1 = norm * pt(12345, -33335, 44445);
    }
//    pt v2 = v1 * norm;

    /*for (dbl t = 0; t < 1; t += 0.001) {
      pt d = (v1 * -t - v2 * (1.0 - t));
      d = d * (1 / d.d());
      assert(abs(d % norm) < 1e-9);
      eprintf("%lf\n", (find_max(center, d, can_see) - center).d());
    }*/

    auto p1 = find_max(center, v1, can_see);
    auto p2 = find_max(center, v1 * -1, can_see);

    eprintf("%lf %lf\n", (p1 - center).d(), (p2 - center).d());

    dbl res = PI * (p1 - center).d() * (p2 - center).d();
    printf("%.17f\n", res);
  }

  return 0;
}
