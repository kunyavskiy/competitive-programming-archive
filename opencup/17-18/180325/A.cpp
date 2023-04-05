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

typedef double dbl;

const dbl eps = 1e-9;

struct pnt {
  dbl x, y;

  pnt( dbl _x = 0, dbl _y = 0 ) : x(_x), y(_y) { }

  inline pnt operator - () const { return pnt(-x, -y); }

  inline pnt operator + ( const pnt &p ) const { return pnt(x + p.x, y + p.y); }
  inline pnt operator - ( const pnt &p ) const { return pnt(x - p.x, y - p.y); }
  inline pnt operator * ( const dbl &k ) const { return pnt(x * k, y * k); }
  inline pnt operator / ( const dbl &k ) const { return pnt(x / k, y / k); }

  inline dbl operator * ( const pnt &p ) const { return x * p.y - y * p.x; }
  inline dbl operator ^ ( const pnt &p ) const { return x * p.x + y * p.y; }

  inline bool operator == ( const pnt &p ) const { return fabs(x - p.x) + fabs(y - p.y) < eps; }
  inline bool operator != ( const pnt &p ) const { return fabs(x - p.x) + fabs(y - p.y) > eps; }
  inline bool operator < ( const pnt &p ) const  { return fabs(x - p.x) > eps ? x < p.x : y + eps < p.y; }

  inline void read() { assert(scanf("%lf%lf", &x, &y) == 2); }

  inline dbl d2() const { return x * x + y * y; }
  inline dbl d() const { return sqrt(d2()); }

  inline pnt norm() const { return *this / d(); }
  inline pnt ort() const { return pnt(-y, x); }
  inline dbl ang() const { return atan2(y, x); }

  pnt rot( dbl a ) {
    dbl co = cos(a), si = sin(a);
    return pnt(x * co - y * si, x * si + y * co);
  }

  static const int prec = 20;
  void out() { printf("%.*f %.*f ", prec, (double)x, prec, (double)y); }
  void outln() { out(), puts(""); }
};

string str( pnt p ) {
  static char buf[99];
  sprintf(buf, "(%.*f,%.*f)", pnt::prec, (double)p.x, pnt::prec, (double)p.y);
  return string(buf);
}

inline pnt pntByAng( dbl a ) { return pnt(cos(a), sin(a)); }

struct line {
  dbl a, b, c;
  line() { }
  line( pnt p, pnt q ) {
    pnt no = (q - p).ort().norm();
    a = no.x;
    b = no.y;
    c = -(no ^ p);
  }
  line( pnt no, dbl C ) {
    dbl d = no.d();
    a = no.x / d, b = no.y / d, c = C / d;
  }
  dbl d( const pnt &p ) const { return a * p.x + b * p.y + c; }
  pnt no() const { return pnt(a, b); }
};

struct circle {
  pnt p;
  dbl r;
};

vector<pnt> v; // to store intersection

#define pb push_back
#define forn(i, n) for (int i = 0; i < (int)(n); i++)
#define sqr(x) ((x) * (x))

// Intersection of two lines
void line_line( const line &l, const line &m ) {
  dbl t = m.a * l.b - l.a * m.b;
  if (fabs(t) > eps)
    v.pb(pnt(-(m.c * l.b - l.c * m.b) / t, (m.c * l.a - l.c * m.a) / t));
}

// Intersection of circle and line
void circle_line( const circle &c, const line &l ) {
  dbl d = l.d(c.p);
  if (fabs(d) > c.r + eps)
    return;
  if (fabs(fabs(d) / c.r - 1) < eps)
    v.pb(c.p - l.no() * d);
  else {
    dbl s = sqrt(fabs(sqr(c.r) - sqr(d)));
    v.pb(c.p - l.no() * d + l.no().ort() * s);
    v.pb(c.p - l.no() * d - l.no().ort() * s);
  }
}

// Intersection of two circles
void circle_circle( const circle &a, const circle &b ) {
  circle_line(a, line((b.p - a.p) * 2, a.p.d2() - b.p.d2() + sqr(b.r) - sqr(a.r)));
}

// Squared distance between point p and segment [a..b]
dbl dist2( pnt p, pnt a, pnt b ) {
  if (((p - a) ^ (b - a)) < 0) return (p - a).d2();
  if (((p - b) ^ (a - b)) < 0) return (p - b).d2();
  return fabs((p - a) * (b - a)) / (b - a).d2();
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int n, m;
  scanf("%d", &n);
  vector<pnt> a(n);
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    a[i].x = x;
    a[i].y = y;
  }
  scanf("%d", &m);
  vector<pnt> b(m);
  for (int i = 0; i < m; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    b[i].x = x;
    b[i].y = y;
  }
  vector<pnt> ll(m);
  vector<pnt> rr(m);
  for (int i = 0; i < m; i++) {
    pnt A = b[i];
    pnt B = b[(i + 1) % m];
    pnt AB = B - A;
    line L1(A, B);
    bool lf = false;
    bool rf = false;
    for (int j = 0; j < n; j++) {
      pnt C = a[j];
      pnt D = a[(j + 1) % n];
      line L2(C, D);
      v.clear();
      line_line(L1, L2);
      if (v.size() > 0) {
        pnt P = v[0];
        pnt AP = P - A;
        if ((AP ^ AB) < (AB ^ AB) * .5) {
          if (!lf || (AP ^ AB) > (ll[i] ^ AB)) {
            ll[i] = AP;
            lf = true;
          }
        } else {
          if (!rf || (AP ^ AB) < (rr[i] ^ AB)) {
            rr[i] = AP;
            rf = true;
          }
        }
      }
    }
//    cout << i << ": " << ll[i].x << "," << ll[i].y << "   " << rr[i].x << "," << rr[i].y << endl;
  }


  dbl d[m][m];

  for (int i = 0; i < m; i++) {
    d[i][i] = 0;
  }

  dbl res = 1e100;

  for (int dd = 1; dd < m; dd++) {
    for (int i = 0; i < m; i++) {
      int j = (i + dd) % m;
      pnt C = b[(i - 1 + m) % m];
      pnt D = b[i];
      pnt E = b[j];
      pnt F = b[(j + 1) % m];
      line L2(C, D);
      line L3(E, F);
      d[i][j] = 1e100;
      for (int k = i; k != j; k = (k + 1) % m) {
        pnt A = b[k];
        pnt B = b[(k + 1) % m];
        pnt AB = B - A;
        line L1(A, B);
        pnt LL = ll[k];
        pnt RR = rr[k];
        v.clear();
        line_line(L1, L2);
        if (v.size() > 0) {
          pnt P = v[0];
          pnt AP = P - A;
          if ((AP ^ AB) < (AB ^ AB) * .5 && (AP ^ AB) > (LL ^ AB)) {
            LL = AP;
          }
        }
        v.clear();
        line_line(L1, L3);
        if (v.size() > 0) {
          pnt P = v[0];
          pnt AP = P - A;
          if ((AP ^ AB) > (AB ^ AB) * .5 && (AP ^ AB) < (RR ^ AB)) {
            RR = AP;
          }
        }
        dbl cost = (RR - LL).d();
        d[i][j] = min(d[i][j], cost + d[i][k] + d[(k + 1) % m][j]);
      }
//      cout << i << " " << j << " " << d[i][j] << endl;
      if (dd == m - 1) {
        dbl cost = (rr[j] - ll[j]).d();
        res = min(res, cost + d[i][j]);
      }
    }
  }

  cout.precision(20);

  cout << fixed << res << endl;

  return 0;
}
