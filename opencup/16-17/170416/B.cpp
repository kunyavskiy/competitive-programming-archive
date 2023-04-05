#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <tuple>
#include <assert.h>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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
typedef long double ld;

struct point {
  ll x, y, z;

  point(ll x, ll y, ll z) : x(x), y(y), z(z) {}

  point() { x = y = z = 0; }

  bool operator==(const point &a) const {
    return x == a.x && y == a.y && z == a.z;
  }

  bool load() {
    ll _x, _y, _z;
    if (scanf("%lld%lld%lld", &_x, &_y, &_z) != 3) return 0;
    x = _x, y = _y, z = _z;
    return true;
  }

  bool operator<(const point &rhs) const {
    if (x < rhs.x)
      return true;
    if (rhs.x < x)
      return false;
    if (y < rhs.y)
      return true;
    if (rhs.y < y)
      return false;
    return z < rhs.z;
  }

  double dist() {
    return sqrt(x * 1.0 * x + y * 1.0 * y + z * 1.0 * z);
  }
};

inline point operator+(const point &a, const point &b) {
  return point(a.x + b.x, a.y + b.y, a.z + b.z);
}

inline point operator-(const point &a, const point &b) {
  return point(a.x - b.x, a.y - b.y, a.z - b.z);
}

inline ll det(ll a, ll b, ll c, ll d) {
  return a * d - b * c;
}

inline ll det(ll a11, ll a12, ll a13, ll a21, ll a22, ll a23, ll a31, ll a32, ll a33) {
  return a11 * det(a22, a23, a32, a33) - a12 * det(a21, a23, a31, a33) + a13 * det(a21, a22, a31, a32);
}

int sgn(ll x) {
  return (x > 0) - (x < 0);
}

inline ll det(const point &a, const point &b, const point &c) {
  return det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
}

point vp(const point &a, const point &b) {
  return point(det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), det(a.x, a.y, b.x, b.y));
}

ll sp(const point &a, const point &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

const ld eps = 1e-4;
const ld INF = 1e9;


struct point2d {
  ld x, y;

  point2d() {}
  point2d(ld x, ld y) : x(x), y(y) {}


  point2d operator + (const point2d & p) const
  {
    return point2d(x + p.x, y + p.y);
  }

  point2d operator - (const point2d & p) const
  {
    return point2d(x - p.x, y - p.y);
  }

  point2d operator * (ld k) const
  {
    return point2d(x * k, y * k);
  }

  point2d operator / (ld k) const
  {
    return point2d(x / k, y / k);
  }

  ld operator * (const point2d & p) const
  {
    return x * p.y - y * p.x;
  }

  ld operator % (const point2d & p) const
  {
    return x * p.x + y * p.y;
  }

  ld abs() const
  {
    return sqrt(x * x + y * y);
  }

  ld distTo(const point2d & p) const
  {
    return (*this - p).abs();
  }

  point2d rotate90() const
  {
    return point2d(-y, x);
  }

  bool operator<(const point2d& r) const {
    if (fabs(r.x - x) > eps) {
      return x < r.x;
    }
    return y < r.y - eps;
  }

  bool operator==(const point2d& r) const {
    return fabs(x - r.x) < eps && fabs(y - r.y) < eps;
  }
};


struct Line {
  point2d p, v;

  Line(const point2d & p, const point2d & v) : p(p), v(v) {}

  point2d intersect(const Line & l) const
  {
    if (fabs(v * l.v) < eps)
      return getpoint2d(INF);
    ld t = ((l.p - p) * l.v) / (v * l.v);
    return getpoint2d(t);
  }

  point2d getpoint2d(ld t) const
  {
    return p + v * t;
  }

  ld getProection(const point2d & p0) const
  {
    return ((p0 - p) % v) / v.abs() / v.abs();
  }
};

Line buildMiddlePerpendicular(const point2d & p1, const point2d & p2)
{
  return Line((p1 + p2) / 2.0, (p2 - p1).rotate90());
}

struct Circle {
  point2d p;
  ld r;

  Circle(const point2d & p, ld r) : p(p), r(r) {}

  Circle(const point2d & p1, const point2d & p2)
  {
    p = (p1 + p2) / 2;
    r = p.distTo(p1);
  }

  bool operator < (const Circle & c) const
  {
    return r < c.r;
  }

  bool cover(const point2d & p0) const
  {
    return p.distTo(p0) < r + eps;
  }

};

struct Segment {
  ld a, b;

  Segment(ld a, ld b) : a(a), b(b)
  {
    //assert(a < b + eps);
  }

  bool cover(ld x) const
  {
    return a < x + eps && x < b + eps;
  }

  Segment intersect(const Segment & s) const
  {
    return Segment(max(a, s.a), min(b, s.b));
  }
};

Segment getSegment(const point2d & p1, const point2d & p2, const point2d & p3)
{
//	printf("getSegment\np1 = "); p1.print();
//	printf("p2 = "); p2.print();
//	printf("p3 = "); p3.print();
  if (fabs((p1 - p3) * (p2 - p3)) < eps)
  {
    //assert((p1 - p3) % (p2 - p3) < -eps);
    return Segment(-INF, INF);
  }

  Line line1 = buildMiddlePerpendicular(p1, p2);
  Line line2 = buildMiddlePerpendicular(p1, p3);

  ld t3 = line1.getProection(p3);

  point2d intersection = line1.intersect(line2);
  ld t0 = line1.getProection(intersection);

//	printf("t0 = %.4lf, t3 = %.4lf\n", t0, t3);

  if (t3 > 0)
    return Segment(t0, INF);
  else
    return Segment(-INF, t0);
}

Circle solve(const vector <point2d> & p, int i, int j)
{
  Line perpendicular = buildMiddlePerpendicular(p[i], p[j]);
  Segment current(-INF, INF);
  for (int k = 0; k < j; ++k)
    current = current.intersect(getSegment(p[i], p[j], p[k]));

  point2d center;
  if (current.cover(0))
    center = perpendicular.getpoint2d(0);
  else if (fabs(current.a) < fabs(current.b))
    center = perpendicular.getpoint2d(current.a);
  else
    center = perpendicular.getpoint2d(current.b);

  return Circle(center, center.distTo(p[i]));
}

Circle solve(const vector <point2d> & p, int i)
{
  Circle answer(p[0], p[i]);
  for (int j = 1; j < i; ++j)
    if (!answer.cover(p[j]))
    {
      answer = solve(p, i, j);
//			printf("solve i = %d j = %d\n", i, j);
//			answer.print();
    }
  return answer;
}

Circle solve(const vector <point2d> & p)
{

  Circle answer(p[0], p[1]);
  for (int i = 2; i < int(p.size()); ++i)
    if (!answer.cover(p[i]))
    {
      answer = solve(p, i);
//			printf("solve i = %d\n", i);
//			answer.print();
    }
  return answer;
}

struct Plane {
  point a, b, c;

  void norm(point p) {
    if (side(p) < 0) {
      swap(b, c);
    }
  }

  int side(const point &p) const { return sgn(det(p - a, b - a, c - a)); }

  pair<point2d, ld> proj(const point& p) {
    point n = vp(c - a, b - a);

    double nLen = sqrt(sp(n, n));
    double bLen = sqrt(sp(b - a, b - a));
    assert(bLen > eps);
    assert(nLen > eps);

    double dist = sp(n, p - a) / nLen;

    double x = sp(b - a, p - a) / bLen;

    point nn = vp(n, b - a);
    double nnLen = nn.dist();;

    assert(nnLen > eps);

    double y = sp(nn, p - a) / nnLen;

    return {{x, y}, abs(dist)};
  };
};


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  vector<point> v(n);

  for (int i = 0; i < n; i++) {
    v[i].load();
  }

  vector<Plane> ps;

  for (int i = 0; i < 4; i++)
    for (int j = i + 1; j < 4; j++)
      for (int k = j + 1; k < 4; k++) {
        Plane p {v[i], v[j], v[k]};
        int other = 1 + 2 + 3 - i - j - k;
        p.norm(v[other]);
        ps.push_back(p);
      }

  for (int i = 4; i < n; i++) {
    vector<Plane> nps;
    vector<pair<point, point>> sd;
    for (Plane p : ps) {
      if (p.side(v[i]) > 0) {
        nps.push_back(p);
        sd.push_back({p.a, p.b});
        sd.push_back({p.a, p.c});
        sd.push_back({p.b, p.c});
      }
    }

    for (auto &x : sd) {
      if (x.first < x.second) {
        swap(x.first, x.second);
      }
    }

    sort(sd.begin(), sd.end());

    for (int j = 0; j < (int)sd.size(); j++) {
      if (j + 1 < (int)sd.size() && sd[j] == sd[j + 1]) {
        j++;
      } else {
        Plane p{v[i], sd[j].first, sd[j].second};
        for (int k = 0; k < i; k++) {
          if (!(v[k] == sd[j].first) && !(v[k] == sd[j].second)) {
            p.norm(v[k]);
            break;
          }
        }
        nps.push_back(p);
      }
    }

    ps = nps;
  }

  ld ans = 1e100;

  for (Plane p : ps) {
    ld maxDist = 0;
    vector<point2d> p2ds;
    for (point pt : v) {
      assert(p.side(pt) >= 0);
      point2d p2d;
      ld dist;
      tie(p2d, dist) = p.proj(pt);
      maxDist = max(maxDist, dist);
      p2ds.push_back(p2d);
    }

    sort(p2ds.begin(), p2ds.end());
    p2ds.erase(unique(p2ds.begin(), p2ds.end()), p2ds.end());

    random_shuffle(p2ds.begin(), p2ds.end());

    Circle c = solve(p2ds);
    eprintf("%lf %lf\n", (double)c.r, (double)maxDist);
    ans = min(ans, maxDist * c.r * c.r * M_PI);
  }

  printf("%.18lf\n", (double )ans);
  return 0;
}
