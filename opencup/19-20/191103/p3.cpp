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
#include <iomanip>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef double ld;

/*struct point {
  double x, y, z;

  point operator - () const {
    return {-x, -y, -z};
  };

  point operator -(point a) const {
    return {x - a.x, y - a.y, z - a.z};
  }

  point operator +(point a) const {
    return {x + a.x, y + a.y, z + a.z};
  }

  point operator * (double a) const {
    return {x * a, y * a, z * a};
  }
};
*/

struct point {
  double x, y, z;

  ld dist2() const {
    return x * x + y * y + z * z;
  }

  ld dist() const {
    return sqrt(dist2());
  }
};

point operator+(const point &a, const point &b) {
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

point operator-(const point &a, const point &b) {
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

point operator*(const point &a, double t) {
  return {a.x * t, a.y * t, a.z * t};
}

ld det(ld a, ld b, ld c, ld d) {
  return a * d - b * c;
}

ld det(ld a11, ld a12, ld a13, ld a21, ld a22, ld a23, ld a31, ld a32, ld a33) {
  return a11 * det(a22, a23, a32, a33) - a12 * det(a21, a23, a31, a33) + a13 * det(a21, a22, a31, a32);
}

ld det(const point &a, const point &b, const point &c) {
  return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

point vp(const point &a, const point &b) {
  return {det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), det(a.x, a.y, b.x, b.y)};
}

ld sp(const point &a, const point &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}


double angle(point a, point b) {
  return atan2(vp(a, b).dist(), sp(a, b));
}

//#define TEST

int main() {
#ifdef LOCAL
  freopen("p3.in", "r", stdin);
  freopen("p3.out", "w", stdout);
#endif

  int n, m, k;
#ifdef TEST
  srand(1234);
  auto rnd = []() {
    return rand() % 2001 - 1000;
  };
  n = m = 100;
  k = m / 2;
  vector<point> path(n + 1);
  for (int i = 0; i < n + 1; i++) {
    path[i].x = rnd();
    path[i].y = rnd();
    path[i].z = 0;
  }

  vector<point> pr(m), lg(m);
  for (int i = 0; i < m; i++) {
    pr[i].x = rnd();
    pr[i].y = rnd();
    pr[i].z = rand() % 1000 + 1;
    lg[i].x = rnd();
    lg[i].y = rnd();
    lg[i].z = rand() % 1000 + 1;
  }
#else
  scanf("%d%d%d", &n, &m, &k);

  vector<point> path(n + 1);
  for (int i = 0; i < n + 1; i++) {
    scanf("%lf%lf", &path[i].x, &path[i].y);
    path[i].z = 0;
  }

  vector<point> pr(m), lg(m);
  for (int i = 0; i < m; i++) {
    scanf("%lf%lf%lf", &pr[i].x, &pr[i].y, &pr[i].z);
    scanf("%lf%lf%lf", &lg[i].x, &lg[i].y, &lg[i].z);
  }
#endif
  vector<vector<double>> ccl[2];
  for (int tt = 0; tt < 2; tt++) {
    ccl[tt] = vector<vector<double>>(n, vector<double>(m));
    for (int i = 0; i < n; i++) {
      const point &a = path[i];
      const point &b = path[i + 1];

      for (int j = 0; j < m; j++) {
        double l = 0;
        double r = 1;
        for (int t = 0; t < 100; t++) {
          double m1 = (l * 2 + r) / 3;
          double m2 = (l + r * 2) / 3;
          point p1 = a + (b - a) * m1;
          point p2 = a + (b - a) * m2;
          double v1 = angle(p1 - pr[j], lg[j]);
          double v2 = angle(p2 - pr[j], lg[j]);
          if (v1 < v2) {
            r = m2;
          } else {
            l = m1;
          }
        }
        ccl[tt][i][j] = l;
      }
    }
    for (int i = 0; i < m; i++) {
      lg[i] = point{} -lg[i];
    }
  }

  function<bool(double)> good = [&](double phi) {
    bool rev = false;
    int min_cover = k;
    int max_cover = m;
    if (phi > M_PI / 2) {
      rev = true;
      for (int i = 0; i < m; i++) {
        lg[i] = point{} - lg[i];
      }
      phi = M_PI - phi;
      min_cover = 0;
      max_cover = m - k;
    }

    bool ok = true;
    for (int i = 0; i < n && ok; i++) {
      const point &a = path[i];
      const point &b = path[i + 1];
      int cur = 0;
      vector<pair<double, int>> events;

      for (int j = 0; j < m; j++) {
        double cl = ccl[rev][i][j];
        if (angle(a + (b - a) * cl - pr[j], lg[j]) > phi) {
          continue;
        }
        double l = cl;
        double r = 1;
        for (int t = 0; t < 35; t++) {
          double m = (l + r) / 2;
          point p1 = a + (b - a) * m;
          double v = angle(p1 - pr[j], lg[j]);
          if (v < phi) {
            l = m;
          } else {
            r = m;
          }
        }
        double R = r;
        l = 0;
        r = cl;
        for (int t = 0; t < 35; t++) {
          double m = (l + r) / 2;
          point p1 = a + (b - a) * m;
          double v = angle(p1 - pr[j], lg[j]);
          if (v < phi) {
            r = m;
          } else {
            l = m;
          }
        }
        double L = l;

        if (L < 1e-9) {
          cur++;
        } else {
          events.emplace_back(L, 1);
        }
        if (R < 1 - 1e-9) {
          events.emplace_back(R, -1);
        }
      }
      sort(events.begin(), events.end());
      if (cur < min_cover || cur > max_cover) ok = false;
      for (auto e: events) {
        cur += e.second;
        if (cur < min_cover || cur > max_cover) ok = false;
      }
    }

    if (rev) {
      for (int i = 0; i < m; i++) {
        lg[i] = point{}-lg[i];
      }
    }
    return ok;
  };

//  good(M_PI / 2);

  double lfi = 0;
  double rfi = M_PI;
  for (int t = 0; t < 35; t++) {
    double fi = (lfi + rfi) / 2;
    if (good(fi)) {
      rfi = fi;
    } else {
      lfi = fi;
    }
  }
  cout << setprecision(20) << rfi * 180 / M_PI << endl;

  return 0;
}
