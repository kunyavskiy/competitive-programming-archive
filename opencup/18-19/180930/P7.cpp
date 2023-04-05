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
#include <unordered_map>

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
  int id;

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

  int up() const {
    if (x > 0 || (x == 0 && y > 0)) return 1;
    if (x < 0 || (x == 0 && y < 0)) return -1;
    return 0;
  }
};
typedef _pt<long long> pt;


vector<pt> convex_hull(vector<pt> a, int on_side) {
  int n = a.size();
  sort(a.begin(), a.end());
  a.resize(unique(a.begin(), a.end()) - a.begin());

  if (a.size() <= 2) return a;

  pt p1 = a[0], p2 = a.back();
  vector<pt> up, down;
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


/*vector<pt> minkowski_sum(vector<pt> a, vector<pt> b) {
  assert(0);
  assert(a[0] == pt(0, 0) && b[0] == pt(0, 0));
  auto cmp = [&](const pt &x, const pt &y) {
    if (x.up() != y.up()) return x.up() > y.up();
    return x.turn(y) > 0;
  };
  vector<pt> aa(a.size()), bb(b.size());
  for (int i = 0; i < (int)aa.size(); i++) aa[i] = a[(i + 1) % a.size()] - a[i];
  for (int i = 0; i < (int)bb.size(); i++) bb[i] = b[(i + 1) % b.size()] - b[i];
  vector<pt> cc(a.size() + b.size());
  merge(aa.begin(), aa.end(), bb.begin(), bb.end(), cc.begin(), cmp);
  vector<pt> c(a.size() + b.size());
  c[0] = pt(0, 0);
  for (int i = 1; i < (int)c.size(); i++) c[i] = c[i - 1] + cc[i - 1];
  return c;
}*/

struct Output {
  double res;
  vector<vector<int>> ids;
  vector<pair<ll, ll>> coef;
};

void print(Output out) {
  printf("%.15f\n", out.res);
  for (int i = 0; i < (int)out.ids.size(); i++) {
    ll g = __gcd(out.coef[i].first, out.coef[i].second);
    out.coef[i].first /= g;
    out.coef[i].second /= g;

    if (out.ids[i].size() == 2) {
      if (out.coef[i].first == 0) {
        out.ids[i].erase(out.ids[i].begin());
      } else if (out.coef[i].first == out.coef[i].second) {
        out.ids[i].pop_back();
      }
    }

    if (out.ids[i].size() == 1) {
      printf("1 %d\n", out.ids[i][0] + 1);
    } else {
      printf("2 %d %d %lld %lld\n", out.ids[i][0] + 1, out.ids[i][1] + 1, out.coef[i].first, out.coef[i].second);
    }
  }
}

bool compAng(const pt &p1, const pt &p2) {
  if (p1.up() != p2.up()) return p1.up() > p2.up();
  return (p1 * p2) > 0;
}

struct cmp {
  bool operator()(const pair<pt, int> &p1, const pair<pt, int> &p2) {
    if (compAng(p1.first, p2.first) || compAng(p2.first, p1.first)) {
      return compAng(p1.first, p2.first);
    }
    return p1.second < p2.second;
  }
};

Output solve(vector<vector<pt>> a, int M) {
  int n = a.size();

  vector<pt> shift(n);
  vector<int> mn(n);
  pt allShift(0, 0);
  pt allMn(0, 0);
  for (int i = 0; i < n; i++) {
    a[i] = convex_hull(a[i], 0);
    shift[i] = a[i][0];
    mn[i] = 0;
    for (int j = 0; j < (int)a[i].size(); j++) {
      //a[i][j] = a[i][j] - shift[i];
      a[i][j].x -= shift[i].x;
      a[i][j].y -= shift[i].y;
      if (a[i][j].y < a[i][mn[i]].y) {
        mn[i] = j;
      }
    }
    allShift = allShift + shift[i];
    allMn = allMn + a[i][mn[i]];
  }

  Output res;
  res.ids.resize(n);
  res.coef.resize(n);
  if ((allMn + allShift).x <= M) {
    res.res = (allMn + allShift).y;
    for (int i = 0; i < n; i++) {
      res.ids[i].push_back(a[i][mn[i]].id);
      res.coef[i] = {1, 2};
    }
    return res;
  }
  if (allShift.x > M) {
    assert(0);
  }

  set<pair<pt, int>, cmp> st;
  for (int i = 0; i < n; i++) {
    if (a[i].size() == 1) continue;
    for (int j = 0; j < (int)a[i].size(); j++) {
      st.insert({a[i][(j + 1) % a[i].size()] - a[i][j], i});
    }
  }

  pt cur = allShift;
  vector<int> ptr(n);
  while (1) {
    assert(!st.empty());
    auto o = *st.begin();
    st.erase(st.begin());

    ll newX = cur.x + o.first.x;
    if (newX < M) {
      ptr[o.second]++;
      cur = cur + o.first;
      continue;
    }

    // cur.y + (M - cur.x) * o.first.y / o.first.x
    res.res = cur.y + 1.0 * (M - cur.x) * o.first.y / o.first.x;
    for (int i = 0; i < n; i++) {
      if (i != o.second) {
        res.ids[i].push_back(a[i][ptr[i]].id);
        res.coef[i] = {1, 2};
      } else {
        res.ids[i].push_back(a[i][ptr[i]].id);
        res.ids[i].push_back(a[i][ptr[i] + 1].id);
        res.coef[i] = {o.first.x - (M - cur.x), o.first.x};
      }
    }
    return res;
  }
  assert(0);
}

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<vector<pt>> a(n);
    for (int i = 0; i < n; i++) {
      int k;
      scanf("%d", &k);
      a[i].resize(k);
      for (int j = 0; j < k; j++) {
        scanf("%lld%lld", &a[i][j].x, &a[i][j].y);
        a[i][j].id = j;
      }
    }

    print(solve(a, m));
  }

  return 0;
}
