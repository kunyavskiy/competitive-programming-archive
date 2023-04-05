//#include <iostream>
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
#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if ( ( _WIN32 || __WIN32__ ) && __cplusplus < 201103L)
    #define LLD "%I64d"
#else
    #define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

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


const double eps = 1e-6;

int sgn(double x) { return x < -eps ? -1 : x > eps; }
struct pt {
  double x, y;
  pt() : x(0), y(0) {}
  pt(double x, double y) : x(x), y(y) {}
  pt operator+(const pt &p2) const { return pt(x + p2.x, y + p2.y); }
  pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
  pt operator*(const double b) const { return pt(x * b, y * b); }
  int operator*(const pt &p2) const { return sgn(x * p2.y - y * p2.x); }
  int operator^(const pt &p2) const { return sgn(x * p2.x + y * p2.y); }
  double dist2() const { return x * x + y * y; }
  bool operator<(const pt &p2) const { return fabs(x - p2.x) > eps ? x < p2.x : y < p2.y - eps; }
  bool operator==(const pt &p2) const { return fabs(x - p2.x) < eps && fabs(y - p2.y) < eps; }
};
struct line {
  double a, b, c;
  line() : a(0), b(0), c(1) {}
  line(const pt &p1, const pt &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
  }
  line(double a, double b, double c) : a(a), b(b), c(c) {}
  double distz(const pt &p) const { return a * p.x + b * p.y + c; }
  double norm2() const { return a * a + b * b; }
  double dists(const pt &p) const { return distz(p) / sqrt(norm2()); }
  int side(const pt &p2) const { return sgn(a * p2.x + b * p2.y + c); }
  void inverse() { a = -a, b = -b, c = -c;}
};

bool operator||(const line &l1, const line &l2) {
  double d = l1.a * l2.b - l1.b * l2.a;
  return (fabs(d) < eps);
}


pt operator&(const line &l1, const line &l2) {
  double d = l1.a * l2.b - l1.b * l2.a;
#ifdef LOCAL
  assert(fabs(d) > eps);
#endif
  pt res(
      (l1.b * l2.c - l1.c * l2.b) / d,
      (l1.a * l2.c - l1.c * l2.a) / -d
  );
#ifdef LOCAL
  assert(l1.side(res) == 0);
  assert(l2.side(res) == 0);
#endif
  return res;
}

bool is_in(double l, double r, double x) {
  if (l > r) swap(l, r);
  return l <= x + eps && x - eps <= r;
}
/*BOXNEXT*/
bool contains(const pt &a, const pt &b, const pt &p) {
  if ((p - a) * (p - b) != 0) return false;
  return is_in(a.x, b.x, p.x) &&
         is_in(a.y, b.y, p.y);
}

vector<pt> cross(const pt &center, double r,
                 const line &l) {
  double di = l.distz(center);
  double d2 = l.norm2();
  assert(fabs(d2) > eps);
  pt mid = center + pt(l.a, l.b) * (-di / d2);
#ifdef DEBUG
  assert(l.side(mid) == 0);
#endif

  double s = r * r - di * di / d2;
  if (s < -eps) return vector<pt>();
  if (fabs(di * di - r * r * d2) < eps)
    return vector<pt>(1, mid);

  pt off = pt(-l.b, l.a) * sqrt(s / d2);
#ifdef LOCAL
  assert(fabs(off.dist2() - s) < eps);
#endif
  vector<pt> res;
  res.pb(mid + off);
  res.pb(mid - off);
  return res;
}

pt p[2];
int a[2][3];

vector<line> get(pt p1, int d1, pt p2, int d2) {
  line l = {p1.x - p2.x, p1.y - p2.y, (double)(d2 - d1)};
  vector<pt> v = cross(pt(), 1, l);

  vector<line> res;
  for (pt p : v) {
    line r = {p.x, p.y, 0};
    r.c = -r.dists(p1) + d1;
#ifdef LOCAL
    assert(fabs(r.dists(p1) - d1) < eps);
    assert(fabs(r.dists(p2) - d2) < eps);
#endif
    res.push_back(r);
  }
  return res;
}

int main() {
#ifdef LOCAL
    assert(freopen(TASKNAME".in", "r", stdin));
    assert(freopen(TASKNAME".out", "w", stdout));
#endif

  for (int i = 0; i < 2; i++) {
    scanf("%lf%lf", &p[i].x, &p[i].y);
    scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);
  }

  vector<line> L[3];

  for (int i = 0; i < 3; i++) {
    for (int d1 = -1; d1 < 2; d1 += 2)
      for (int d2 = -1; d2 < 2; d2 += 2) {
        vector<line> ll = get(p[0], a[0][i] * d1, p[1], a[1][i] * d2);
        L[i].insert(L[i].end(), ll.begin(), ll.end());
      }
  }

  for (line l1 : L[0])
    for (line l2 : L[1])
      for (line l3 : L[2]) {
        if (l1 || l2) continue;
        if (l1 || l3) continue;
        if (l2 || l3) continue;

        pt X = l1 & l3;
        pt Y = l1 & l2;
        pt Z = l2 & l3;

        if (l1.side(Z) < 0) l1.inverse();
        if (l2.side(X) < 0) l2.inverse();
        if (l3.side(Y) < 0) l3.inverse();

        vector<line> ll = {l1, l2, l3};

        bool ok = true;
//        eprintf("%.18f %.18f\n", X.x, X.y);
//        eprintf("%.18f %.18f\n", Y.x, Y.y);
//        eprintf("%.18f %.18f\n", Z.x, Z.y);

        for (int i = 0; i < 2; i++) {
          bool inside = 1;
          for (int j = 0; j < 3; j++) {
//            eprintf("%.18f ", ll[j].dists(p[i]));
            if (ll[j].side(p[i]) < 0) {
              inside = 0;
            }
          }
//          eprintf("\n");
          if (inside == (a[i][0] < 0)) {
            ok = false;
          }
        }
//        eprintf("\n");
//        eprintf("\n");

        if (ok) {
          printf("%.18f %.18f\n", X.x, X.y);
          printf("%.18f %.18f\n", Y.x, Y.y);
          printf("%.18f %.18f\n", Z.x, Z.y);
          return 0;
        }
      }


  return 0;
}
