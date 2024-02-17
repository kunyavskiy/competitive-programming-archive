#include <bits/stdc++.h>

#define ALL(v) (v).begin(), (v).end()
#define rep(i, l, r) for (int i = (l); i < (r); ++i)

using ll = long long;
using ld = double;
using ull = unsigned long long;

using namespace std;


/*
ll pw(ll a, ll b) {
        ll ans = 1; while (b) {
                while (!(b & 1)) b >>= 1, a = (a * a) % MOD;
                ans = (ans * a) % MOD, --b;
        } return ans;
}
*/

struct point {
  point() : x(0), y(0) {
  }
  point(ld x, ld y) : x(x), y(y) {
  }

  point operator+(point other) {
    return point(x + other.x, y + other.y);
  }

  point operator-(point other) {
    return point(x - other.x, y - other.y);
  }

  point operator/(ld l) {
    return point(x / l, y / l);
  }
  ld operator^(point other) {
    return x * other.x + y * other.y;
  }

  ld operator*(point other) {
    return x * other.y - y * other.x;
  }

  ld len() {
    return sqrt(x * x + y * y);
  }

  ld x, y;
};

point rot(point p) {
  return point(p.y, -p.x);
}

int n;

const int N = 500;

ll w[N];
point pp[N];


vector<pair<ld, int>> xx, yy;

int psx[N];
int psy[N];

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif
  ios_base::sync_with_stdio(false), cin.tie(0), cout.tie(0);
  cout.setf(ios::fixed), cout.precision(20);

  cin >> n;
  ld ans = 0;
  for (int i = 0; i < n; ++i) {
    cin >> pp[i].x >> pp[i].y >> w[i];
    ans = max<ld>(ans, w[i]);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) {
        continue;
      }
      point yv = pp[j] - pp[i];
      yv = yv / yv.len();
      auto xv = rot(yv);

      xx.clear(); yy.clear();

      for (int k = 0; k < n; ++k) {
        ld x = xv ^ (pp[k] - pp[i]);
        if (x < 0 && (k != i && k != j)) {
          continue;
        }
        ld y = yv ^ (pp[k] - pp[i]);
        xx.emplace_back(x, k);
        yy.emplace_back(y, k);
      }
      sort(ALL(xx));
      sort(ALL(yy));

      for (int i = 0;)

      int l = 0, r = 0;
      for (int k = 0; k < (int)yy.size(); ++k) {
        psy[yy[k].second] = k;
      }
      for (int k = 0; k < (int)xx.size(); ++k) {
        psx[xx[k].second] = k;
      }
      ld cs = -2 * ((pp[j] - pp[i]) ^ yv);
      for (int k = 0; k < (int)xx.size(); ++k) {
        i
      }

    }
  }

  cout << ans << "\n";
  return 0;
}




