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
    return !lt(a, b);
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

  _pt<T>() : x(0), y(0) {}
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

  // long long can be casted to double with loss of precision...
  bool operator< (const _pt<T> &p) const {
    if (!eq(x, p.x)) return lt(x, p.x);
    return lt(y, p.y);
  }

  bool operator== (const _pt<T> &p) const {
    return eq(x, p.x) && eq(y, p.y);
  }

  void read() {
    std::cin >> x >> y;
  }
};
typedef _pt<long long> pt;

std::vector<pt> convex_hull(std::vector<pt> a, int on_side) {
  int n = a.size();
  sort(a.begin(), a.end());
  //a.resize(unique(a.begin(), a.end()) - a.begin());

  pt p1 = a[0], p2 = a.back();
  std::vector<pt> up, down;
  for (int i = 0; i < n; i++) {
    if (i == 0 || i == n - 1 || (a[i] - p1).turn(p2 - p1) >= 0) {
      while (down.size() > 1 && (a[i] - down.back()).turn(down.back() - down[(int)down.size() - 2]) >= on_side) {
        down.pop_back();
      }
      down.push_back(a[i]);
    }
    if (i == 0 || i == n - 1 || (a[i] - p1).turn(p2 - p1) <= 0) {
      while (up.size() > 1 && (a[i] - up.back()).turn(up.back() - up[(int)up.size() - 2]) <= -on_side) {
        up.pop_back();
      }
      up.push_back(a[i]);
    }
  }
  for (int i = (int)up.size() - 2; i > 0; i--) down.push_back(up[i]);
  return down;
}

int main() {
#ifdef LOCAL
  freopen("i.in", "r", stdin);
//  freopen("i.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<pt> a(n);
    for (int i = 0; i < n; i++) scanf("%lld%lld", &a[i].x, &a[i].y);

    auto b = convex_hull(a, 0);

    int ans = 1;

    if (b.size() == 1) ans = 1;
    else if (b.size() == 2) {
      ll border = 0;
      auto v = b[1] - b[0];
      v.x = abs(v.x);
      v.y = abs(v.y);
      ll g = __gcd(v.x, v.y);
      border += g + 1;
      ans = n == border;
    } else if (b.size() >= 3) {
//      for (auto o : b) db2(o.x, o.y);
//      db("");
      ll area2 = 0;
      ll border = 0;
      for (int i = 0; i < (int) b.size(); i++) {
        area2 += b[i] * b[(i + 1) % b.size()];
        auto v = b[(i + 1) % b.size()] - b[i];
        v.x = abs(v.x);
        v.y = abs(v.y);
        ll g = __gcd(v.x, v.y);
        border += g;
//        if (v.x != 0) border += v.x / g;
//        else border += v.y / g;
      }
      area2 = abs(area2);
//      db2(area2, border);

      // area = inside + border / 2 - 1
      ll inside2 = area2 + 2 - border;
//      ans = inside2 == 0;
      ans = inside2 + 2 * border == 2 * n;
    }
    printf("%d\n", ans);
  }

  return 0;
}
