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
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

#define db(x) cerr << #x << " = " << x << endl
#define db2(x, y) cerr << "(" << #x << ", " << #y << ") = (" << x << ", " << y << ")\n";
#define db3(x, y, z) cerr << "(" << #x << ", " << #y << ", " << #z << ") = (" << x << ", " << y << ", " << z << ")\n"
#define dbv(a) cerr << #a << " = "; for (auto xxxx: a) cerr << xxxx << " "; cerr << endl


using namespace std;

#ifdef LOCAL

static struct __timestamper {
  string what;

  __timestamper(const char *what) : what(what) {};

  __timestamper(const string &what) : what(what) {};

  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");

#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct pt {
  int x, y;
  int hpl() const {
    if (y > 0 || (y == 0 && x > 0)) return 1;
    return -1;
  }
  double ang() const {
    return atan2(y, x);
  }

};

pt operator-(const pt &a, const pt &b) {
  return {a.x - b.x, a.y - b.y};
}

pt operator+(const pt &a, const pt &b) {
  return {a.x + b.x, a.y + b.y};
}

ll operator*(const pt &a, const pt &b) {
  return a.x * 1LL * b.y - a.y * 1LL * b.x;
}

ll sp(const pt& a, const pt &b) {
  return a.x * 1LL * b.x + a.y * 1LL * b.y;
}

ll dist2(const pt& a, const pt&b) {
  return sp(a - b, a - b);
}

__int128_t sqr(ll x) {
  return __int128_t(x) * x;
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif


  int n;
  while (scanf("%d", &n) == 1) {
    vector<pt> points(n);
    for (pt &x : points) {
      scanf("%d%d", &x.x, &x.y);
    }
    vector<pt> ds;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        ds.push_back(points[i] - points[j]);
        ds.push_back(points[j] - points[i]);
      }
    }
    ds.push_back({1, 0});
    ds.push_back({0, 1});
    ds.push_back({-1, 0});
    ds.push_back({0, -1});
    sort(ds.begin(), ds.end(), [](const pt &a, const pt &b) {
      if (a.hpl() != b.hpl()) {
        return a.hpl() < b.hpl();
      }
      return a * b > 0;
    });
    ds.push_back(ds[0]);
    double res = 0;
    for (int id = 0; id + 1 < (int)ds.size(); id++) {
      if (ds[id] * ds[id+1] == 0) continue;
      pt n = (ds[id] + ds[id + 1]);
      double weight = ds[id + 1].ang() - ds[id].ang();
      if (weight < 0) weight += 2 * M_PI;

      weight /= 2 * M_PI;

      sort(points.begin(), points.end(), [&](const pt& a, const pt&b) {
        return sp(n, a) < sp(n, b);
      });
      vector<ll> sps(points.size());
      for (int i = 0; i < (int)points.size(); i++) {
        sps[i] = sp(points[i], n);
      }
      ll spn = sp(n, n);

      ll ans = 1LL << 60;
      int ops = 0;
      for (int i = 0; i < (int)points.size(); i++) {
        for (int j = i - 1; j >= 0; j--) {
          if (sqr(sps[i] - sps[j]) >= __int128_t(ans) * spn) break;
          ans = min(ans, dist2(points[i], points[j]));
          ops++;
        }
      }

      eprintf("ops = %d, weight = %lf\n", ops, weight);

      res += ops * weight;
    }

    printf("%.18lf\n", res);
  }


  return 0;
}
