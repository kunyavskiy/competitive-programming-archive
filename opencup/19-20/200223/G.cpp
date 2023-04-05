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

typedef __int128_t ll;
typedef long double ld;
typedef long double dbl;

struct pt {
  ll x, y, z;

  ll d2() const {
    return x * x + y * y + z * z;
  }

  dbl d() const {
    return sqrtl((dbl)d2());
  }

  bool ok() const {
    bool f = d2() != 0;
    f &= abs(x) <= 1e6;
    f &= abs(y) <= 1e6;
    f &= abs(z) <= 1e6;
    return f;
  }

  void print() {
    cout << (int)x << " " << (int)y << " " << (int)z << endl;
  }
};

ll det(ll a,ll b,ll c,ll d){
  return a*d - b*c;
}

ll det(ll a11,ll a12,ll a13,ll a21,ll a22, ll a23, ll a31, ll a32,ll a33){
  return a11*det(a22,a23,a32,a33) - a12*det(a21,a23,a31,a33) + a13*det(a21,a22,a31,a32);
}

dbl calc_dist(pt a, pt b, pt c) {
  ll x = det(a.x, a.y, a.z, b.x, b.y, b.z, c.x, c.y, c.z);
  if (x != 1) {
    a.print();
    b.print();
    c.print();
    printf("%lld\n", (long long)x);
    assert(0);
  }
  return x / a.d() / b.d() / c.d();
}

dbl sqr(dbl x) {
  return x * x;
}

dbl ds(pt a, pt b) {
  dbl xa = a.x / a.d();
  dbl ya = a.y / a.d();
  dbl za = a.z / a.d();

  dbl xb = b.x / b.d();
  dbl yb = b.y / b.d();
  dbl zb = b.z / b.d();

  return sqrtl(sqr(xa - xb) + sqr(ya - yb) + sqr(za - zb));
}

ll rnd() {
  ll x;
  do {
    x = rand() % (int) (2e6 + 1) - 1e6;
  } while (abs(x) < 7e5);
  return x;
}

pt find_1() {
  return {rnd(), rnd(), rnd()};
}

void norm(ll x, ll y, ll&rx, ll&ry) {
  ll shift_x = y;
  ll shift_y = -x;
  if (shift_x < 0) {
    shift_x *= -1;
    shift_y *= -1;
  }
  ll k = rx / shift_x;
  rx -= k * shift_x;
  ry -= k * shift_y;
  if (rx < 0) {
    rx += shift_x;
    ry += shift_y;
  }
  if (rand() % 2) {
    rx -= shift_x;
    ry -= shift_y;
  }
};


void gcdex(ll a,ll b,ll &x,ll &y) {
  if (!a){
    x = 0, y = 1;
    return;
  }
  ll x1, y1;
  gcdex(b % a, a, x1, y1);
  x = y1 - (b / a) * x1;
  y = x1;
  norm(a, b, x, y);
}

bool solve_d(ll x, ll y, ll d, ll &rx, ll& ry) {
  ll g = __gcd(x, y);
  if (d % g != 0) {
    return false;
  }
  gcdex(x, y, rx, ry);
  assert(x * rx + y * ry == g);
  norm(x, y, rx, ry);
  rx *= d / g;
  ry *= d / g;
  norm(x, y, rx, ry);
  assert(x * rx + y * ry == d);
  return true;
}

pt find_2(pt a) {
  for (int i = 0; i < 10; i++) {
    ll z = rnd();
    ll x, y;
    if (solve_d(a.x, a.y, -a.d2()/2 - z * a.z, x, y)) {
      return {x, y, z};
    }
  }
  return {};
}

pt find_3(pt a, pt b) {
  for (int i = 0; i < 10; i++) {
    ll z = rnd();
    ll x, y;
    if (solve_d(det(a.y, a.z, b.y, b.z), -det(a.x, a.z, b.x, b.z), 1 - z * det(a.x, a.y, b.x, b.y), x, y)) {
      return {x, y, z};
    }
  }
  return {};
}


int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
//  freopen("g.out", "w", stdout);
#endif

  for (int it = 0;; it++) {
    if (it % 100000 == 0) db(it);

    pt a = find_1();
    if (!a.ok()) continue;

    pt b = find_2(a);
    if (!b.ok()) continue;

    pt c = find_3(a, b);
//    if (!c.d2()) continue;
    if (!c.ok()) continue;

    dbl d = calc_dist(a, b, c);
    dbl d1 = ds(a, b);
    dbl d2 = ds(a, c);//(a - c).d();
    dbl d3 = ds(b, c); //(b - c).d();
    eprintf("%e %lf %lf %lf\n", (double)d, (double)d1, (double)d2, (double)d3);
    a.print();
    b.print();
    c.print();

    bool ok = 1;
    ok &= d1 > 1.7;
    ok &= d2 > 1.7;
    ok &= d3 > 1.7;
    ok &= d < 1.5e-19;
    ok &= c.ok();

    if (ok) {
      a.print();
      b.print();
      c.print();
      break;
    }
  }

  return 0;
}
