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

ll solve(int l, int r) {
  l--;
  ll res = 0;
  for (int x1 = l; x1 < r; x1++) {
    for (int y1 = 0; y1 <= x1; y1++) {
      for (int x2 = l; x2 < r; x2++) {
        for (int y2 = 0; y2 <= x2; y2++) {
          if (x1 == x2 && y1 == y2) continue;
          int x3 = x2 + y1 - y2;
          int y3 = x2 - x1 + y1;
          if (x3 < l || x3 >= r || y3 < 0 || y3 > x3) {
            continue;
          }
          res++;
        }
      }
    }
  }
  return res / 3;
}

ll pref_sum(ll r) {
  return r * (r - 1) / 2;
}

ll solve2(int l, int r) {
  l--;
  ll res = 0;
  for (int x1 = l; x1 < r; x1++) {
    for (int y1 = l; y1 <= x1; y1++) {
      res += pref_sum(x1) - pref_sum(max(l, x1 - y1));
      res += x1 * (r - x1);
    }
  }
  for (int x1 = l; x1 < r; x1++) {
    for (int y1 = max(0, x1 - r + l); y1 < l; y1++) {
      res += x1 * (r - l - x1 + y1);
      res += pref_sum(x1 - y1 + l) - pref_sum(max(l, x1 - y1));
      res += (y1 - l) * (x1 - y1 + l - max(l, x1 - y1));
    }
  }
  for (int x1 = l; x1 < r; x1++) {
    for (int y1 = 0; y1 < x1 - r + l; y1++) {
      res += pref_sum(r) - pref_sum(max(l, x1 - y1));
      res += (y1 - l) * (r - max(l, x1 - y1));
    }
  }
  for (int x1 = l; x1 < r; x1++) {
    for (int y1 = 0; y1 <= min(x1, r - l); y1++) {
      res += r - y1 - max(l, x1 - y1);
    }
  }
  for (int x1 = l; x1 < r; x1++) {
    for (int y1 = 0; y1 <= min(x1, r - l - 1); y1++) {
      res -= pref_sum(r) - pref_sum(r - y1);
      res -= (y1 - r) * y1;
    }
    for (int y1 = r - l; y1 <= x1; y1++) {
      res -= pref_sum(r) - pref_sum(l);
      res -= (y1 - r) * (r - l);
    }
  }
  res -= (r * (r + 1)) / 2 - (l * (l + 1)) / 2;
  return res / 3;
}

ll gcd(ll a, ll b) {
  while (b > 0) {
    ll c = a % b;
    a = b;
    b = c;
  }
  return a;
}

ll lcm(ll a, ll b) {
  a = abs(a);
  b = abs(b);
  return a / gcd(a, b) * b;
}

struct rat {
  __int128 x, y;

  rat(__int128 _x = 0, __int128 _y = 1) : x(_x), y(_y) {
  }

  void norm() {
    __int128 g = __gcd(x, y);
    x /= g;
    y /= g;
  }

  rat operator+ (const rat &r) const {
    __int128 g = __gcd(y, r.y);
    __int128 ny = (y / g) * r.y;
    __int128 nx = x * (ny / y) + r.x * (ny / r.y);
    rat res{nx, ny};
    res.norm();
    return res;
  }

  rat operator* (const rat &r) const {
    __int128 g1 = __gcd(x, r.y);
    __int128 g2 = __gcd(r.x, y);
    return {(x / g1) * (r.x / g2), (y / g2) * (r.y / g1)};
  }
};

int main() {
#ifdef LOCAL
  freopen("l.in", "r", stdin);
  freopen("l.out", "w", stdout);
#endif

//  for (int l = 1; l <= 30; l++) {
//    for (int r = l; r <= 30; r++) {
//      assert(solve(l, r) == solve2(l, r));
//    }
//  }
//
  vector<int> x;
  vector<int> y;
  int MAX = 5;
  for (int i = 0; i <= MAX; i++) {
    for (int j = 0; j <= MAX; j++) {
      x.push_back(i);
      y.push_back(j);
    }
  }

  vector<rat> A;
  vector<rat> B;
  for (int qqq = 0; qqq < 2; qqq++) {

    vector<vector<ll>> a;
    int need = x.size() * 2;
    for (int r = 1; (int) a.size() < need; r++) {
      for (int l = 1; l <= r && (int) a.size() < need; l++) {
        if ((qqq == 0 && r < l * 2) || (qqq == 1 && r >= l * 2)) {
          vector<ll> q;
          for (int i = 0; i < (int) x.size(); i++) {
            ll p = 1;
            for (int j = 0; j < x[i]; j++) p *= l;
            for (int j = 0; j < y[i]; j++) p *= r;
            q.push_back(p);
          }
          q.push_back(solve(l, r));
          a.push_back(q);
//          cerr << l << " " << r << " " << q.back() << endl;
        }
      }
    }

    int n = x.size();
    for (int i = 0; i < n; i++) {
      for (int j = i; j < (int) a.size(); j++) {
        if (a[j][i] != 0) {
          swap(a[i], a[j]);
          break;
        }
      }
      assert(a[i][i] != 0);
      for (int j = 0; j < (int) a.size(); j++) {
        if (j != i && a[j][i] != 0) {
          ll q = lcm(a[i][i], a[j][i]);
          ll ki = q / a[i][i];
          ll kj = q / a[j][i];
          for (int t = 0; t <= n; t++) {
            a[j][t] = a[j][t] * kj - a[i][t] * ki;
          }
        }
      }
    }
    vector<rat> R;
    for (int i = 0; i < n; i++) {
      ll P = a[i][n];
      ll Q = a[i][i];
      R.emplace_back(P, Q);
    }
    if (qqq == 0) {
      A = R;
    } else {
      B = R;
    }
  }

  int n;
  scanf("%d", &n);
#ifdef TEST
  n = 3e5;
#endif
  for (int i = 0; i < n; i++) {
    int l, r;
#ifndef TEST
    scanf("%d%d", &l, &r);
#else
    l = 1;
    r = 1e5;
#endif

    vector<rat> R;
    if (r < l * 2) {
      R = A;
    } else {
      R = B;
    }

    rat s;

    vector<__int128> pl(MAX + 1);
    vector<__int128> pr(MAX + 1);
    pl[0] = 1;
    for (int o = 1; o <= MAX; o++) {
      pl[o] = pl[o - 1] * l;
    }
    pr[0] = 1;
    for (int o = 1; o <= MAX; o++) {
      pr[o] = pr[o - 1] * r;
    }

    for (int o = 0; o < (int)x.size(); o++) {
      if (R[o].x == 0) continue;
      rat w = {pl[x[o]] * pr[y[o]], 1};
      s = s + w * R[o];
    }
    s.norm();
    assert(s.y == 1);
    printf("Case #%d: %llu\n", i + 1, (unsigned long long)s.x);
//    cout << "Case #" << (i + 1) << ": " << (unsigned long long)s.x << "\n";
  }
  return 0;
}
