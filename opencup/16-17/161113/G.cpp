#include <bits/stdc++.h>

#define pb push_back
#define mp make_pair
#define TASKNAME "G"

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
typedef pair<double, double> pdd;
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

const double pi = acos(-1.0);

struct Point {
  int x, y;
  Point() {}
  Point(int _x, int _y) : x(_x), y(_y) {}

  void read() {
    scanf("%d%d", &x, &y);
  }
  Point operator - (const Point & p) const {
    return Point(x - p.x, y - p.y);
  }

  Point operator + (const Point & p) const {
    return Point(x + p.x, y + p.y);
  }

  Point operator * (int k) const {
    return Point(x * k, y * k);
  }

  double polarAngle() const {
    return atan2(y, x);
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
    eprintf("%d %d\n", x, y);
  }
};

struct Event {
  double x;
  int cnt;

  Event(double _x, int _cnt) : x(_x) , cnt(_cnt) {}

  bool operator < (const Event & e)  const {
    if (fabs(x - e.x) > eps) {
      return x < e.x;
    }
    return cnt < e.cnt;
  }
};

bool isFullCircle(pdd seg) {
  return (seg.first == -100);
}

bool onSegment(double L, double R, double x) {
  if (isFullCircle(pdd(L, R))) return true;

  if (L < R) {
    return L - eps < x && x < R + eps;
  } else {
    return (x < R + eps) || (L - eps < x);
  }
}

void unionSegs(double &L1, double &R1, double L2, double R2) {
  double L, R;
  if (R1 < L1) {
    R1 += pi;
  }
  if (L2 < L1) {
    L2 += pi;
  }
  if (R2 < L1) {
    R2 += pi;
  }

//  L = min(L1, L2);
  R = max(R1, R2);
  if (L2 > R) {
    L = L2;
  } else {
    L = L1;
  }

  if (R - L > pi) {
    L = R = -100;
  } else {
    if (L > pi) {
      L -= pi;
    }
    if (R > pi) {
      R -= pi;
    }
  }

  L1 = L;
  R1 = R;
}

int findMaxPoint(vector <pdd> segs) {
  int resTot = 0;
  int bestCnt = 0;
  int cnt = 0;
  vector <Event> events;
  for (int i = 0; i < int(segs.size()); ++i) {
    if (isFullCircle(segs[i])) {
      resTot++;
    } else {
      events.push_back(Event(segs[i].first, 1));
      events.push_back(Event(segs[i].second, -1));
      if (segs[i].first > segs[i].second) {
        cnt++;
      }
    }
  }

  sort(events.begin(), events.end());
  for (int i = 0; i < int(events.size()); ++i) {
    cnt += events[i].cnt;
    bestCnt = max(bestCnt, cnt);
  }
  return bestCnt + resTot;
}

bool solve() {
  int n;
  if (scanf("%d", &n) != 1) { return false;}

  vector <vector<Point>> p(n);
  for (int i = 0; i < n; ++i) {
    int k;
    scanf("%d", &k);
    p[i].resize(k);
    for (int j = 0; j < k; ++j) {
      p[i][j].read();
    }
  }

  int res = 1;
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < int(p[i].size()); ++j) {
      vector <pdd> segs;
      Point p0 = p[i][j];
      p0.print();
      for (int s = 0; s < n; ++s) {
//        if (s == i) { continue; }
        bool found = false;
        double totAngL = 0.0, totAngR = 0.0;
        for (int t = 0; t < int(p[s].size()); ++t) {
          Point p1 = p[s][t];
          Point p2 = p[s][(t + 1) % (int)p[s].size()];
          if ((p1 - p0) * (p2 - p0) == 0) {
            continue;
          }
          double ang1 = (p1 - p0).polarAngle();
          double ang2 = (p2 - p0).polarAngle();
//          eprintf("ang1 %.5lf ang2 %.5lf\n", ang1, ang2);
          double angL, angR;
          if (fabs(ang2 - ang1) < pi) {
            angL = min(ang1, ang2);
            angR = max(ang1, ang2);
          } else {
            angL = max(ang1, ang2);
            angR = min(ang1, ang2);
          }

          if (angL < 0) {
            angL += pi;
          }
          if (angR < 0) {
            angR += pi;
          }

          if (!found) {
            totAngL = angL;
            totAngR = angR;
            found = true;
          } else {
            unionSegs(totAngL, totAngR, angL, angR);
          }
          eprintf("t %d angL %.5lf angR %.5lf totAngL %.5lf totAngR %.5lf\n", t, angL, angR, totAngL, totAngR);
        }

        eprintf("s %d %.5lf %.5lf\n", s, totAngL, totAngR);

        segs.push_back(pdd(totAngL, totAngR));
      }
      int cur = findMaxPoint(segs);
      eprintf("cur = %d\n", cur);
      res = max(res, cur);
    }
  }

  printf("%d\n", res);

  return true;
}

int main() {
  #ifdef LOCAL
  freopen("G.in", "r", stdin);
  freopen("G.out", "w", stdout);
  #endif

  while (solve());

  return 0;
}
