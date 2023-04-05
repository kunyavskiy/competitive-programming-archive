#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "I"

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time = %.3lfs\n",clock()*1.0/CLOCKS_PER_SEC)

#ifdef _WIN32
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

#define sz(x) ((int)(x).size())
#define forn(i, n) for (int i = 0; i < (n); i++)

using namespace std;

typedef long double ld;
typedef long long ll;
typedef vector <ll> vll;
typedef vector<int> vi;
typedef vector <vi> vvi;
typedef vector<bool> vb;
typedef vector <vb> vvb;
typedef pair<int, int> pii;
typedef pair <ll, ll> pll;
typedef vector <pii> vpii;

const int inf = 1e9;
const ld eps = 1e-9;
const int INF = inf;
const ld EPS = eps;

#ifdef LOCAL
struct __timestamper {
  ~__timestamper(){
    TIMESTAMP(end);
  }
} __Timestamper;
#else
struct __timestamper {
};
#endif

/*Template end*/

struct Point {
  double x, y;
  Point() {}
  Point(double _x, double _y) : x(_x), y(_y) {}

  Point operator - (const Point & p) const {
    return Point(x - p.x, y - p.y);
  }

  Point operator + (const Point & p) const {
    return Point(x + p.x, y + p.y);
  }

  Point operator * (double k) const {
    return Point(x * k, y * k);
  }

  double distTo(const Point & p) const {
    return (*this - p).abs();
  }

  double abs() const {
    return sqrt(x * x + y * y);
  }

  double operator * (const Point & p) const {
    return x * p.y - y * p.x;
  }

  void print() const {
    eprintf("%.2lf %.2lf\n", x, y);
  }
};

bool check(const Point & p1, const Point & p2, const Point & p3) {
  return (p2 - p1) * (p3 - p1) < 0;
}

int sign(double x) {
  if (x > eps) { return 1; }
  if (x < -eps) { return -1; }
  return 0;
}

bool check2(const Point & A, const Point & B, const Point & p1, const Point & p2) {
  Point p0(0, 0);
  int s0 = sign((B - A) * (p0 - A));
  int s1 = sign((B - A) * (p1 - A));
  int s2 = sign((B - A) * (p2 - A));
  return s0 * s1 == 1 && s0 * s2 == 1;
}

pair<Point, Point> find(const Point & p0, const Point & v) {
  Point A = p0 + v * (double(0 - p0.y) / v.y);
  Point B = p0 + v * (double(p0.x - 0) / (-v.x));
  return make_pair(A, B);
}

double getLen(const Point & p1, const Point & p2) {
  if (p1.x == p2.x || p1.y == p2.y) {
    return INF;
  }
  Point v = p2 - p1;
  pair<Point,Point> ab = find(p1, v);
  double res = ab.first.distTo(ab.second);
  eprintf("getLen2\n");
  ab.first.print();
  ab.second.print();
  eprintf("res = %.10lf\n", res);
  return res;
}

double getLen(const Point & p1, const Point & p2, const Point & p3) {
  assert(p2.x != 0 && p2.y != 0);
  double a = pow(p2.y, 1.0/3.0);
  double b = pow(p2.x, 1.0/3.0);
  Point v(b, -a);
  pair<Point,Point> ab = find(p2, v);
  eprintf("getLen3\n");
  v.print();
  ab.first.print();
  ab.second.print();
  double res = ab.first.distTo(ab.second);
  eprintf("res = %.10lf\n", res);
  if (check2(ab.first, ab.second, p1, p3)) {
    return res;
  } else {
    return INF;
  }
}

int solve() {
  int n;
  if (scanf("%d", &n) != 1) { return 0; }
  const int MAXX = int(1e4);
  vector <int> maxY(MAXX + 1, 0);
  for (int i = 0; i < n; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    maxY[x] = max(maxY[x], y);
    maxY[0] = max(maxY[0], y);
  }
  vector <Point> v;
  v.push_back(Point(0, maxY[0]));
  for (int i = 1; i <= MAXX; ++i) {
    Point curP(i, maxY[i]);
    if (curP.y == 0) { continue; }
    while (v.size() >= 2 && !check(v[int(v.size()) - 2], v.back(), curP)) {
      v.pop_back();
    }
    v.push_back(curP);
  }

  v.push_back(Point(v.back().x, 0));
  int k = int(v.size());
  for (int i = 0; i < k; ++i) {
    v[i].print();
  }
  double res = INF;
  for (int i = 1; i < k - 1; ++i)  {
    Point p1 = v[i - 1];
    Point p2 = v[i];
    Point p3 = v[i + 1];
    res = min(res, getLen(p1, p2));
    res = min(res, getLen(p1, p2, p3));
  }
  printf("%.10lf\n", res);
  return 1;
}

int main() {
  #ifdef LOCAL
  freopen("I.in", "r", stdin);
  freopen("I.out", "w", stdout);
  #endif

  while(solve());

  return 0;
}
