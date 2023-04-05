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

const int INF = 1e9;
typedef long long ll;
typedef long double ld;

struct pt {
  int x, y;

  pt() {}
  pt(int _x, int _y) : x(_x), y(_y) {}

  pt operator- (const pt &p) const {
    return pt(x - p.x, y - p.y);
  }

  ll d2() const {
    return 1LL * x * x + 1LL * y * y;
  }
};

ll Rand(ll n) {
  return abs(((ll)rand() << 31) ^ rand()) % n;
}

pt curPos;
vector<vector<int>> dices;
int queries;

pt getStart() {
  queries = 0;
  pt res;
#ifdef LOCAL
  dices.clear();
  dices.push_back(vector<int>(6, 1));

  //res.x = Rand(2e9 + 1) - 1e9;
  //res.y = Rand(2e9 + 1) - 1e9;
  res.y = Rand(10) - 5;
  res.x = Rand(10) - 5;
  curPos = res;
#else
  cin >> res.x >> res.y;
#endif
  return res;
}

vector<int> last;
vector<int> getDice() {
  assert(queries++ < 60000);

#ifdef LOCAL
  last.resize(6);
  for (int i = 0; i < 6; i++) {
    last[i] = rand() % 10000 + 1;
  }
  return last;
#else
  vector<int> res(6);
  for (int i = 0; i < 6; i++) cin >> res[i];
  return res;
#endif
}

ll lastDist;
ll take(bool f) {
#ifdef LOCAL
  if (f) {
    dices.push_back(last);
  }
  ll res = 0;
  for (auto v : dices) {
    res += v[rand() % 6];
  }
  lastDist = res;
  return res;
#else
  cout << (f ? "take" : "pass") << endl;
  ll res = 0;
  cin >> res;
  return res;
#endif
}

ll mySqrt(ll x) {
  ll y = sqrt(x);
  while (y * y < x) y++;
  while (y * y > x) y--;
  return y;
}

bool isSquare(ll x) {
  ll y = mySqrt(x);
  return y * y == x;
}

ll canGo(ll need, ll dist2) {
  if (isSquare(dist2)) return need * need == dist2;
  ll sdist2 = mySqrt(dist2);
  return sdist2 == need || sdist2 == need - 1;
}

void go(pt nw) {
  assert(abs(nw.x) <= INF && abs(nw.y) <= INF);
#ifdef LOCAL
  ll dist2 = (curPos - nw).d2();
  assert(canGo(lastDist, dist2));

  curPos = nw;
#else
  cout << nw.x << " " << nw.y << endl;
#endif
}

void Answer() {
  assert(curPos.x == 0 && curPos.y == 0);
}

namespace pkun {
#define pb push_back
#define sz(x) ((int)(x).size())

  const double eps = 1e-9;

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
    double dist(const pt &p) const { return fabs(distz(p)) / sqrt(norm2()); }
    int side(const pt &p2) const { return sgn(a * p2.x + b * p2.y + c); }
  };

#define sqr(x) ((x) * (x))

// BEGIN ALGO
// Assumption: line.norm2() > 0
// Assumption: r >= 0

// returns 0-2 _unique_ points, which lie both on circle and line
// res[0] lies on the left side of (l.a, l.b)
// for example (center=0,0, r=2, 0x+1y-1=0): (-sqrt(3), 1), (sqrt(3),1)

  pt operator&(const line &l1, const line &l2) {
    double d = l1.a * l2.b - l1.b * l2.a;
    assert(fabs(d) > eps);
    pt res(
        (l1.b * l2.c - l1.c * l2.b) / d,
        (l1.a * l2.c - l1.c * l2.a) / -d
    );
    assert(l1.side(res) == 0);
    assert(l2.side(res) == 0);
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
    //db(fabs(off.dist2() - s));
    //assert(fabs(off.dist2() - s) < eps);
    vector<pt> res;
    res.pb(mid + off);
    res.pb(mid - off);
    return res;
  }




// returns 0-2 _unique_ points.
// res[0] lies on the left side of line (a-->b)
  vector<pt> cross(const pt &a, double r1, pt b,
                   double r2) {
    b = b - a;
    if (fabs(b.dist2()) < eps) {
      if (fabs(r1) < eps && fabs(r2) < eps)
        return vector<pt>(1, a);

      assert(fabs(r1 - r2) > eps);
      return vector<pt>();
    }
    vector<pt> res = cross(b, r2,
                           line(2 * b.x, 2 * b.y,
                                sqr(r2) - sqr(r1) -
                                sqr(b.x) - sqr(b.y)));
    for (int i = 0; i < sz(res); i++)
      res[i] = res[i] + a;
    return res;
  }
}


ll disp(vector<int> a) {
  double res = 0;
  ll sum = 0;
  for (ll x : a) {
    sum += x;
  }
  double av = sum / 6.0;
  for (ll x : a) {
    res += (x - av) * (x - av);
  }
  return sqrt(res / 6);
}


void solve() {
  /*const int T = 500;
  vector<vector<pt>> turns(T);
  for (int i = 1; i < T; i++) {
    for (int x = -i; x <= i; x++) {
      for (int y = -i; y <= i; y++) {
        if (canGo(i, pt(x, y).d2())) {
          turns[i].push_back({x, y});
        } else if (y > 0) break;
      }
    }
  }*/
  //cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  //exit(0);

  auto cur = getStart();

  vector<vector<int>> dices;
  dices.push_back(vector<int>(6, 1));

  double expectation = 1;


  bool chosen = 0;
  int rad = -1;

  while (cur.x != 0 || cur.y != 0) {
    auto ndice = getDice();

    ll s;
    if (expectation < 5e4 && disp(ndice) < 1700) {
      dices.push_back(ndice);
      for (auto x : ndice) expectation += x / 6.0;
      s = take(true);
    } else {
      if (expectation >= 5e4 && !chosen) {
        ll mx = 0;
        for (auto v : dices) mx += *max_element(v.begin(), v.end());
        chosen = 1;
        vector<ll> cnt(mx + 1);
        cnt[0] = 1;
        for (auto v : dices) {
          vector<ll> ncnt(mx + 1);
          for (int i = 0; i <= mx; i++) {
            if (!cnt[i]) continue;
            for (int x : v) ncnt[i + x] += cnt[i];
          }
          cnt = ncnt;
        }

        ll av = expectation;
        ll bestSum = -1;
        for (int cs = 0.5 * av; cs <= 1.5 * av; cs++) {
        //for (int cs = 1; cs <= mx; cs++) {
          if (!(cs >= 1 && cs <= mx)) continue;
          if (bestSum < cnt[cs]) {
            bestSum = cnt[cs];
            rad = cs;
          }
        }
      }
      s = take(false);
    }

    if (canGo(s, cur.d2())) {
      go(pt(0, 0));
      Answer();
      return;
    }

    if (!chosen) {
      pt dest = cur;
      if (dest.x > 0) dest.x -= s;
      else dest.x += s;
      go(dest);
      cur = dest;
      continue;
    }

    bool turnFound = 0;
    pt dest;
    if (rad != -1) {
      auto v = pkun::cross(pkun::pt(cur.x, cur.y), s, pkun::pt(0, 0), rad);
      for (auto pp : v) {
        for (int dx = -2; dx <= 2; dx++) {
          for (int dy = -2; dy <= 2; dy++) {
            pt nw = pt(pp.x + dx, pp.y + dy);
            if (canGo(s, (cur - nw).d2()) && canGo(rad, nw.d2())) {
              turnFound = 1;
              dest = nw;
            }
            if (turnFound) break;
          }
          if (turnFound) break;
        }
        if (turnFound) break;
      }
    }
    if (!turnFound) {
      pt dir;
      if (rad == -1 || cur.d2() > rad * rad) {
        dir = pt(-cur.x, -cur.y);
      } else {
        dir = pt(cur.x, cur.y);
      }
      double len = sqrt(dir.d2());
      double nx = cur.x + dir.x / len * s;
      double ny = cur.y + dir.y / len * s;
      auto pp = pkun::pt(nx, ny);
      for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
          pt nw = pt(pp.x + dx, pp.y + dy);
          if (canGo(s, (cur - nw).d2())) {
            turnFound = 1;
            dest = nw;
          }
          if (turnFound) break;
        }
        if (turnFound) break;
      }
    }
    if (!turnFound) {
      turnFound = 1;
      dest = cur;
      if (dest.x > 0) dest.x -= s;
      else dest.x += s;
    }
    assert(turnFound);
    go(dest);
    cur = dest;
  }
  //assert(0);
}

void gen() {
  vector<ll> v;
  int n = 1e5;
  for (int i = 0; i < n; i++) {
    vector<int> a(6);
    for (int j = 0; j < 6; j++) {
      a[j] = rand() % (int)1e4 + 1;
    }
    v.push_back(disp(a));
  }
  sort(v.begin(), v.end());
  db(v[0]);
  db(v[n / 10]);
  db(v[n / 2]);
  db(v.back());
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  //gen();

#ifdef LOCAL
  while (1) {
    int test = 0;
    while (1) {
      srand(test);
      db(test++);
      solve();
      db(queries);
    }
  }
#endif

  solve();

  return 0;
}
