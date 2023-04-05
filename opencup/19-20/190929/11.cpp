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

typedef long long ll;
typedef long double ld;

namespace dbl_utils {
  typedef double dbl;

  const dbl EPS = 1e-9;

  bool eq(dbl a, dbl b) {
    return fabs(a - b) < EPS;
  }

  bool ne(dbl a, dbl b) {
    return !eq(a, b);
  }

  bool lt(dbl a, dbl b) {
    return a < b && !eq(a, b);
  }

  bool le(dbl a, dbl b) {
    return !lt(b, a);
  }

  bool ge(dbl a, dbl b) {
    return !lt(b, a);
  }

  bool gt(dbl a, dbl b) {
    return lt(b, a);
  }

  int sign(dbl x) {
    if (eq(x, 0)) return 0;
    if (x > 0) return 1;
    return -1;
  }
}
using namespace dbl_utils;

template <typename T>
struct _pt {
  T x, y;

  _pt<T>() {}
  _pt<T>(T _x, T _y) : x(_x), y(_y) {}

  _pt<T> operator+ (const _pt<T> &p) const {
    return _pt<T>(x + p.x, y + p.y);
  }

  _pt<T>& operator+= (const _pt<T> &p) {
    return *this = *this + p;
  }

  _pt<T> operator- (const _pt<T> &p) const {
    return _pt<T>(x - p.x, y - p.y);
  }

  _pt<T>& operator-= (const _pt<T> &p) {
    return *this = *this - p;
  }

  _pt<T> operator* (T d) const {
    return _pt<T>(x * d, y * d);
  }

  _pt<T>& operator*= (T d) {
    return *this = *this * d;
  }

  T operator* (const _pt<T> &p) const {
    return x * p.y - y * p.x;
  }

  T operator% (const _pt<T> &p) const {
    return x * p.x + y * p.y;
  }

  T d2() const {
    return *this % *this;
  }

  dbl d() const {
    return sqrt((dbl)d2());
  }

  dbl ang() const {
    return atan2((dbl)y, (dbl)x);
  }

  _pt<T> rotate90() const {
    return _pt<T>(-y, x);
  }

  _pt<T> rotate(dbl ang) {
    return _pt<T>(x * cos(ang) - y * sin(ang),
                  x * sin(ang) + y * cos(ang));
  }

  int turn(const _pt<T> &p) const {
    return sign((*this) * p);
  }

  bool operator< (const _pt<T> &p) const {
    if (!eq(x, p.x)) return lt(x, p.x);
    return lt(y, p.y);
  }

  bool operator== (const _pt<T> &p) const {
    return eq(x, p.x) && eq(y, p.y);
  }

  void read() {
    cin >> x >> y;
  }
};
typedef _pt<dbl> pt;

const dbl INF = 1e18;
const dbl PHI = (sqrt(5.0) - 1) / 2;

dbl tern(dbl L, dbl R, function<dbl(dbl)> f) {
  dbl fL = f(R - (R - L) * PHI);
  dbl fR = f(L + (R - L) * PHI);
  for (int it = 0; it < 70; it++) {
    if (fL > fR) {
      R = L + (R - L) * PHI;
      fR = fL;
      fL = f(R - (R - L) * PHI);
    } else {
      L = R - (R - L) * PHI;
      fL = fR;
      fR = f(L + (R - L) * PHI);
    }
  }
  return max(fL, fR);
}

inline dbl dist(const pt &p, const pt &A, const pt &B, const pt &n) {
  dbl res = INF;

  pt pA = p - A;
  pt pB = p - B;
  pt AB = A - B;
  dbl cres = pA % n;

  if ((pA % AB) <= 0 &&
    (pB % AB) >= 0) {
    res = cres*cres;
  } else {
    res = min(pA.d2(), pB.d2());
  }
  if (cres < 0) res = -res;
  return res;
}

int sgn(dbl x) {
  if (x > 0) return 1;
  if (x < 0) return -1;
  return 0;
}

void solve(vector<pt> a, int p1, int p2, int p3) {
  int n = a.size();

  int cur = 0;
  vector<int> c(n);
  for (int i = 0; i < n; i++) {
    cur += i == p1 || i == p2 || i == p3;
    c[i] = cur % 3;
  }
  vector<char> good(n);
  for (int i = 0; i < n; i++) {
    good[i] = c[i] == c[(i - 1 + n) % n] && c[i] == c[(i + 1) % n];
  }

  vector<pt> norm(n);
  for (int i = 0; i < n; i++) {
    pt A = a[i];
    pt B = a[(i + 1) % n];
    pt n = (B - A).rotate90();
    n = n * (1.0 / n.d());
    norm[i] = n;
  }


  dbl mnx = INF, mxx = -INF, mny = INF, mxy = -INF;
  for (auto p : a) {
    mnx = min(mnx, p.x);
    mxx = max(mxx, p.x);
    mny = min(mny, p.y);
    mxy = max(mxy, p.y);
  }

  auto get_d = [&](const pt &p) {
    vector<dbl> dd(3, INF);
    for (int i = 0; i < n; i++) {
//      dbl d = good[i] ? ((p - a[i]) % norm[i]) : dist(p, a[i], a[(i + 1) % n], norm[i]);
      dbl d = dist(p, a[i], a[(i + 1) % n], norm[i]);
      dd[c[i]] = min(dd[c[i]], d);
    }
    return dd;
  };

  dbl ans = -INF;
  pt ansP;
  tern(mnx, mxx, [&](dbl x) {
    return tern(mny, mxy, [&](dbl y) {
      auto dd = get_d(pt(x, y));
      auto mx = *max_element(dd.begin(), dd.end());
      auto mn = *min_element(dd.begin(), dd.end());
      dbl res = sqrt(mx * sgn(mx)) * sgn(mx) - sqrt(mn * sgn(mn)) * sgn(mn);
//      dbl res = mx - mn;

      res *= -1;
      if (ans < res) {
        ans = res;
        ansP = pt(x, y);
      }
      return res;
    });
  });
  dbv(get_d(ansP));

  printf("Yes\n%.17f %.17f\n", (double)ansP.x, (double)ansP.y);
}

void test() {
  int n = 4e4;
  vector<pt> a(n);
  for (int i = 0; i < n; i++) {
    a[i] = pt(i, i * i);
  }
  int i1 = rand() % n;
  int i2 = rand() % n;
  int i3 = rand() % n;
  solve(a, i1, i2, i3);
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("11.in", "r", stdin);
//  freopen("p11.out", "w", stdout);
#endif
//  test();

  int n;
  while (scanf("%d", &n) == 1) {
    vector<pt> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf", &a[i].x,&a[i].y);
    }
    int p1, p2, p3;
    scanf("%d%d%d", &p1, &p2, &p3);
    p1--; p2--; p3--;
    if (p1>p2) swap(p1, p2);
    if (p1>p3) swap(p1, p3);
    if (p2>p3) swap(p2, p3);

    solve(a, p1, p2, p3);
  }

  return 0;
}
