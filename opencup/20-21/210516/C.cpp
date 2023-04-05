#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("[" #x "] Time : %.3lf s.\n", (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() {
    TIMESTAMPf("%s", what.data());
  }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

struct point {
  double x, y, z;

  point operator+(point o) {
    return {x + o.x, y + o.y, z + o.z};
  }

  point operator-(point o) {
    return {x - o.x, y - o.y, z - o.z};
  }

  point operator*(double k) {
    return {x * k, y * k, z * k};
  }

  double len() {
    return sqrt(x * x + y * y + z * z);
  }
};

point vp(point a, point b) {
  return {a.y * b.z - a.z * b.y,
          a.z * b.x - a.x * b.z,
          a.x * b.y - a.y * b.x};
}

double sp(point a, point b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

double angle(point a, point b) {
  double sn = vp(a, b).len();
  double cs = sp(a, b);
  return atan2(sn, cs);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int nv;
  cin >> nv;
  vector<point> v(nv);
  for (int i = 0; i < nv; i++) {
    cin >> v[i].x >> v[i].y >> v[i].z;
  }
  int ne;
  cin >> ne;
  vector<pair<int, int>> e(ne);
  for (int i = 0; i < ne; i++) {
    cin >> e[i].first >> e[i].second;
  }
  int nf;
  cin >> nf;
  vector<vector<int>> f(nf);
  for (int i = 0; i < nf; i++) {
    int k;
    cin >> k;
    f[i].resize(k);
    for (int j = 0; j < k; j++) {
      cin >> f[i][j];
    }
  }

  double D;
  cin >> D;

  point c;
  for (int i = 0; i < nv; i++) { c = c + v[i]; }
  c = c * (1.0 / nv);

  double res = 0;

  vector<point> norm(nf);

  vector<vector<int>> fe(ne);

  for (int i = 0; i < nf; i++) {
    int o = e[f[i][0]].first;
    for (int j : f[i]) {
      fe[j].push_back(i);
      int a = e[j].first;
      int b = e[j].second;
      point aa = v[a] - v[o];
      point bb = v[b] - v[o];
      point cc = vp(aa, bb);
      if (cc.len() > norm[i].len()) {
        norm[i] = cc;
      }
      res += cc.len() / 2 * D;
//      res += abs(sp(cc, v[o] - c)) / 6;
    }
    if (sp(norm[i], v[o] - c) < 0) norm[i] = norm[i] * -1;
  }
  for (int i = 0; i < ne; i++) {
    int a = fe[i][0];
    int b = fe[i][1];
    double al = angle(norm[a], norm[b]);
    res += (v[e[i].first] - v[e[i].second]).len() * D * D * al / 2;
  }
  res += 4 * M_PI * D * D * D / 3;

  cout << setprecision(20) << res << "\n";

  return 0;
}
