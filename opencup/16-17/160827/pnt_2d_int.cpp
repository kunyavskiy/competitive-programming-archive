#include <bits/stdc++.h>

using namespace std;

#define forn(i, n) for (int i = 0; i < (int)(n); i++)

typedef double dbl;
typedef long long ll;

struct pnt {
  int x, y;

  pnt( int _x = 0, int _y = 0 ) : x(_x), y(_y) { }

  inline pnt operator - () const { return pnt(-x, -y); }

  inline pnt operator + ( const pnt &p ) const { return pnt(x + p.x, y + p.y); }
  inline pnt operator - ( const pnt &p ) const { return pnt(x - p.x, y - p.y); }
  inline pnt operator * ( const int &k ) const { return pnt(x * k, y * k); }
  inline pnt operator / ( const int &k ) const { return pnt(x / k, y / k); }

  inline ll operator * ( const pnt &p ) const { return (ll)x * p.y - (ll)y * p.x; }
  inline ll operator ^ ( const pnt &p ) const { return (ll)x * p.x + (ll)y * p.y; }

  bool zero() { return !x && !y; }
  inline bool operator == ( const pnt &p ) const { return x == p.x && y == p.y; }
  inline bool operator != ( const pnt &p ) const { return !(*this == p); }
  inline bool operator < ( const pnt &p ) const { return x < p.x || (x == p.x && y < p.y); }

  inline void read() { assert(scanf("%d%d", &x, &y) == 2); }

  inline ll d2() const { return (ll)x * x + (ll)y * y; }
  inline dbl d() const { return sqrt((dbl)d2()); }

  inline pnt norm() const { return *this / d(); }
  inline pnt ort() const { return pnt(-y, x); }
  inline dbl ang() const { return atan2((dbl)y, (dbl)x); }

  void out() { printf("%d %d ", x, y); }
  void outln() { out(), puts(""); }
};

string str( pnt p ) {
  static char buf[99];
  sprintf(buf, "(%d,%d)", p.x, p.y);
  return string(buf);
}
