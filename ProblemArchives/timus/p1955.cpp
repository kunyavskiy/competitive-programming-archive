#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#include <string>
#include <deque>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <set>

using namespace std;

#define mp make_pair
#define pb push_back
#ifdef DEBUG
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#define timestamp(str) eprintf("[ "str" ] time=%.4lf\n", clock() / double(CLOCKS_PER_SEC))
#else
#define eprintf(...)
#define timestamp(str)
#endif
#define sz(x) (int)((x).size())

typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<bool> vb;
typedef vector<vb> vvb;
typedef pair<int, int> pii;

#define TASKNAME ""

const long long linf = 1e18;
const int inf = 1e9;
const double eps = 1e-9;
#define INF inf
#define EPS eps

int sgn(double x) { return x < -eps ? -1 : x > eps; }
struct pt {
  double x, y;
  pt() : x(0), y(0) {}
  pt(double x, double y) : x(x), y(y) {}
  pt operator-(const pt &p2) const { return pt(x - p2.x, y - p2.y); }
  int operator*(const pt &p2) const { return sgn(x * p2.y - y * p2.x); }

  bool operator<(const pt &p2) const { if (sgn(x - p2.x)) return sgn(x - p2.x) < 0; return sgn(y - p2.y) < 0; }
  bool operator==(const pt &p2) const { return sgn(x - p2.x) == 0 && sgn(y - p2.y) == 0; }
  double dist2() const { return x * x + y * y; }
};

struct line {
  double a, b, c;
  line (const pt &p1, const pt &p2) {
    a = p1.y - p2.y;
    b = p2.x - p1.x;
    c = -a * p1.x - b * p1.y;
  }
  int side(const pt &p) const { return sgn(a * p.x + b * p.y + c); }

  pt operator&(const line &l2) const {
    double d = a * l2.b - b * l2.a;
    assert(sgn(d));

    pt res(
      (b * l2.c - c * l2.b) / d,
      (a * l2.c - c * l2.a) / -d
    );
    assert(side(res) == 0);
    assert(l2.side(res) == 0);
    return res;
  }
};

int main() {
/*  #ifdef DEBUG
  freopen(TASKNAME ".in", "r", stdin);
  freopen(TASKNAME ".out", "w", stdout);
  #else
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);
  #endif*/

  int n;
  while (scanf("%d", &n) >= 1) {
    vector<pt> pts(n);
    for (int i = 0; i < n; i++)
      scanf("%lf%lf", &pts[i].x, &pts[i].y);
    pts.pb(pts[0]);

    double ans = 0;
    for (int a = 0; a < n; a++)
    for (int b = a + 1; b < n; b++) {
//      eprintf("a=%d,b=%d\n", a, b);
      line l(pts[a], pts[b]);

      vector<pt> lps;

      for (int i = 0; i < n; i++) {
        if (l.side(pts[i]) == 0) lps.pb(pts[i]);

        if (l.side(pts[i]) * l.side(pts[i + 1]) < 0) {
//          eprintf("a\n");
          lps.pb(l & line(pts[i], pts[i + 1]));
        }
      }
      sort(lps.begin(), lps.end());
      lps.erase(unique(lps.begin(), lps.end()), lps.end());

      int k = sz(lps);
      vi linebal(k, 0);
      for (int i = 0; i < n; i++)
        if (l.side(pts[i]) == 0 && l.side(pts[i + 1]) == 0) {
          int a = lower_bound(lps.begin(), lps.end(), pts[i]) - lps.begin();
          int b = lower_bound(lps.begin(), lps.end(), pts[i + 1]) - lps.begin();
          assert(lps[a] == pts[i]);
          assert(lps[b] == pts[i + 1]);

          if (a > b) swap(a, b);
          linebal[a]++;
          linebal[b]--;
        }

      vi bbal(k, 0);
      for (int i = 0; i < n; i++) {
        pt a = pts[i], b = pts[i + 1];
        if (l.side(b) == 0) swap(a, b);
        if (l.side(b) == 0) continue;
        if (l.side(a) == 0) {
          // l.side(a) == 0 && l.side(b) != 0
          int aid = lower_bound(lps.begin(), lps.end(), a) - lps.begin();
          assert(lps[aid] == a);

          if (l.side(b) > 0) bbal[aid]++;
        } else if (l.side(a) * l.side(b) < 0) {
          pt p = l & line(a, b);
          int id = lower_bound(lps.begin(), lps.end(), p) - lps.begin();
          assert(lps[id] == p);
          bbal[id]++;
        }
      }

/*      for (int i = 0; i < k; i++)
        eprintf("%.2lf %.2lf\n", lps[i].x, lps[i].y);

      for (int i = 0; i < k; i++)
        eprintf("%d%c", linebal[i], "\n "[i + 1 < k]);
      for (int i = 0; i < k; i++)
        eprintf("%d%c", bbal[i], "\n "[i + 1 < k]);*/

      vb isgood(k, false);
      int clinebal = 0, cbbal = 0;
      for (int i = 0; i < k; i++) {
        clinebal += linebal[i];
        cbbal ^= bbal[i] & 1;
        isgood[i] = clinebal || cbbal;
      }
      assert(!isgood[k - 1]);

      int last = 0;
      for (int i = 0; i + 1 < k; i++)
        if (isgood[i]) {
          ans = max(ans, (lps[i + 1] - lps[last]).dist2());
        } else {
          last = i + 1;
        }
    }
    printf("%.18lf\n", sqrt(ans));
  }
  timestamp("end");
  return 0;
}
