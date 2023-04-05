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

struct Point {
  int x, y;
};

ld calc(vector<Point> points) {
  int n = int(points.size());
  auto min_it = min_element(points.begin(), points.end(), [](const Point &p1, const Point &p2) {
    if (p1.x != p2.x) {
      return p1.x < p2.x;
    }
    return p1.y < p2.y;
  });

  rotate(points.begin(), min_it, points.end());

  long long tot_s = 0;

  for (int i = 0; i < n; ++i) {
    const auto &p1 = points[i];
    const auto &p2 = points[(i + 1) % n];
    tot_s += ll(p1.x) * p2.y - ll(p2.x) * p1.y;
  }
  eprintf("tot_s %lld\n", tot_s);
  if (tot_s < 0) {
    tot_s *= -1;
  } else {
//    assert(0);
  }


  vector<int> xs;
  for (const auto &p : points) {
    xs.push_back(p.x);
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());


//  for (auto &t : p) {
//    eprintf("%d %d\n", t.x, t.y);
//  }

  vector<Point> down;
  for (int i = 0; i < n; ++i) {
    if (i > 0 && points[i].x <= points[i - 1].x) {
      break;
    }
    down.push_back(points[i]);
  }

  reverse(points.begin() + 1, points.end());
  vector<Point> up;
  {
    int j = 0;
    while (points[j].x == points[j + 1].x) j++;
    for (int i = j; i < n; ++i) {
      if (i > j && points[i].x <= points[i - 1].x) {
        break;
      }
      up.push_back(points[i]);
    }
  }

//  for (auto &p : down) {
//    eprintf("(%d %d) ", p.x, p.y);
//  }
//  eprintf("\n");
//  for (auto &p : up) {
//    eprintf("(%d %d) ", p.x, p.y);
//  }
//  eprintf("\n");

  ld res = 0.0;
  ld cur_s = 0.0;
  int i1 = 0, i2 = 0;
  for (size_t i = 0; i + 1 < xs.size(); ++i) {
    int xL = xs[i];
    int xR = xs[i + 1];
//    eprintf("xL %d xR %d\n", xL, xR);
    while (down[i1 + 1].x < xR) {
      ++i1;
    }
    while (up[i2 + 1].x < xR) {
      ++i2;
    }

    const auto &p1 = up[i2];
    const auto &p2 = up[i2 + 1];
    const auto &p3 = down[i1];
    const auto &p4 = down[i1 + 1];

    auto buildSlope = [](const Point &p1, const Point &p2) -> pair<ld, ld>{
      auto A = (p2.y - p1.y) / ld(p2.x - p1.x);
      auto B = p1.y - p1.x * A;
//      eprintf("p1 (%d %d) p2 (%d %d) A %.5lf B %.5lf\n", p1.x, p1.y, p2.x, p2.y, (double)A, (double)B);
      return {A, B};
    };

    auto [A1, B1] = buildSlope(p1, p2);
    auto [A2, B2] = buildSlope(p3, p4);

    ld A = A1 - A2;
    ld B = B1 - B2;

    eprintf("A %.10lf B %.10lf\n", (double)A, (double)B);

//    double a = (A / 2) / tot_s * 2;
//    double b = (B) / tot_s * 2;
//    double c = (B * xL - A * xL * xL / 2.0 + cur_s) / tot_s * 2;
//
//    vector<double> v;
//    v.push_back(0);
//    v.push_back(c * c);
//    v.push_back(2 * b * c);
//    v.push_back(b * b + 2 * a * c);
//    v.push_back(2 * a * b);
//    v.push_back(a * a);
//    for (int ii = 1; ii <= 5; ++ii) {
//      v[ii] *= -1;
//      v[ii] /= ii;
//    }
//    v[1] += 1;
//
//    double cur = 0;
//    for (int ii = 1; ii <= 5; ++ii) {
//      cur += v[ii] * (pow(xR, ii) - pow(xL, ii));
//    }

    auto f = [&](ld x) {
      ld val = cur_s + ((x - xL) * (A * (x + xL) / 2 + B)) * 2.0 / tot_s;
//      double val = (cur_s + ((A / 2 * x + B) * x + (B * xL - A * xL * xL / 2.0))) * 2.0 / tot_s;
//      eprintf("x %.10lf val %.10lf\n", (double)x, (double)val);
      return val;
    };

    //[xL, xR]
    auto g = [&](ld x) {
      return 1 - f(x) * f(x);
    };

    ld cur = 8 / 9.0 * g((xL + xR) / 2.0);
    cur += 5.0 / 9.0 * g((xL + xR) / 2.0 + sqrt(0.6) * (xR - xL) / 2.0);
    cur += 5.0 / 9.0 * g((xL + xR) / 2.0 - sqrt(0.6) * (xR - xL) / 2.0);
    cur *= (xR - xL);
    cur /= 2;
//
//
//    auto F = [&](double x) {
//      return ((A / 6 * x + B / 2.0) * x + (B * xL - A * xL * xL / 2.0)) * x;
//    };

//    double cur = cur_s + F(xR) - F(xL);

    eprintf("cur %.10lf\n", (double)cur);
    res += cur;

    cur_s = f(xR);
    eprintf("cur_s %.10lf\n", (double)cur_s);
  }

//  res /= cur_s;
  res += xs[0];

  eprintf("res = %.10lf\n", (double)res);

  return res;
}

bool solve() {
  int n;
  if (scanf("%d", &n) != 1) {
    return false;
  }

  vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &points[i].x);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &points[i].y);
  }

  ld res = 0;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      res += calc(points);
      for (auto &p : points) {
        p.x *= -1;
      }
      reverse(points.begin(), points.end());
    }
    for (auto &p : points) {
      swap(p.x, p.y);
    }
    reverse(points.begin(), points.end());
  }
  printf("%.20lf\n", (double)res);

  return true;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
  freopen("f.out", "w", stdout);
#endif

  while (solve()) {
  }

  return 0;
}
