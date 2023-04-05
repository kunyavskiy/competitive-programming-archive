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
typedef double dbl;

const dbl INF = 1e20;
const dbl EPS = 1e-9;

bool eq(dbl x, dbl y) {
  return fabs(x - y) < EPS;
}

bool ls(dbl x, dbl y) {
  return !eq(x, y) && x < y;
}

template <typename T, class F = function<T(const T&, const T&)>>
class sparse_table {
public:
  int n;
  vector<vector<T>> mat;
  F func;

  sparse_table(const vector<T>& a, const F& f) : func(f) {
    n = static_cast<int>(a.size());
    int max_log = 32 - __builtin_clz(n);
    mat.resize(max_log);
    mat[0] = a;
    for (int j = 1; j < max_log; j++) {
      mat[j].resize(n - (1 << j) + 1);
      for (int i = 0; i <= n - (1 << j); i++) {
        mat[j][i] = func(mat[j - 1][i], mat[j - 1][i + (1 << (j - 1))]);
      }
    }
  }

  T get(int from, int to) const {
    assert(0 <= from && from <= to && to <= n - 1);
    int lg = 32 - __builtin_clz(to - from + 1) - 1;
    return func(mat[lg][from], mat[lg][to - (1 << lg) + 1]);
  }
};

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
//  freopen("k.out", "w", stdout);
#endif

  int T;
  scanf("%d", &T);
  while (T--) {
    int n;
    scanf("%d", &n);
    vector<dbl> x1(n), y1(n), x2(n), y2(n), vx(n), vy(n);
    for (int i = 0; i < n; i++) {
      scanf("%lf%lf%lf%lf%lf%lf", &x1[i], &y1[i], &x2[i], &y2[i], &vx[i], &vy[i]);
    }


    struct line {
      dbl k;
      dbl b;
    };
    typedef vector<dbl> poly;
    auto get_poly = [&](const line &l) {
      poly res;
      res.push_back(l.b);
      res.push_back(l.k);
      return res;
    };
    auto calc = [&](const poly &p, dbl x) {
      dbl cur = 1;
      dbl res = 0;
      for (auto c : p) {
        res += cur * c;
        cur *= x;
      }
      return res;
    };
    auto get_max = [&](const poly &p, dbl l, dbl r) {
      assert(p.size() == 3);
      if (eq(p[2], 0)) {
        return max(calc(p, l), calc(p, r));
      } else {
        dbl x = -p[1] / (2 * p[2]);
        dbl res = -INF;
        if (l <= x && x <= r) {
          res = calc(p, x);
        }
        res = max(res, max(calc(p, l), calc(p, r)));
        return res;
      }
    };

    auto convex = [&](vector<line> a) {
      sort(a.begin(), a.end(), [&](const line &l1, const line &l2) {
        if (eq(l1.k, l2.k)) return l1.b > l2.b;
        return l1.k < l2.k;
      });

      vector<pair<dbl, line>> vct;
      vct.emplace_back(-INF, a[0]);
      for (int i = 1; i < (int)a.size(); i++) {
        if (eq(a[i].k, a[i - 1].k)) continue;
        while (1) {
          assert(!vct.empty());
          auto prev = vct.back().second;
          auto cur = a[i];
          assert(!eq(prev.k, cur.k));
          dbl t = (cur.b - prev.b) / (prev.k - cur.k);

          if (!ls(vct.back().first, t)) {
            vct.pop_back();
          } else {
            vct.emplace_back(t, cur);
            break;
          }
        }
      }
      vector<pair<dbl, poly>> res;
      for (auto o : vct) {
        res.emplace_back(o.first, get_poly(o.second));
      };
      res.emplace_back(INF, poly(2, 0));
      return res;
    };

    vector<pair<dbl, poly>> v1, v2, v3, v4;
    {
      vector<line> a;
      for (int i = 0; i < n; i++) {
        a.push_back({(dbl)vx[i], (dbl)x1[i]});
      }
      v1 = convex(a);
    }
    {
      vector<line> a;
      for (int i = 0; i < n; i++) {
        a.push_back({(dbl)-vx[i], (dbl)-x2[i]});
      }
      v2 = convex(a);
    }
    {
      vector<line> a;
      for (int i = 0; i < n; i++) {
        a.push_back({(dbl)vy[i], (dbl)y1[i]});
      }
      v3 = convex(a);
    }
    {
      vector<line> a;
      for (int i = 0; i < n; i++) {
        a.push_back({(dbl)-vy[i], (dbl)-y2[i]});
      }
      v4 = convex(a);
    }

    auto comb = [&](vector<pair<dbl, poly>> a, vector<pair<dbl, poly>> b, function<poly(poly, poly)> f) {
      vector<pair<dbl, poly>> res;

      int i = 0, j = 0;
      while (i + 1 < (int)a.size() && j + 1 < (int)b.size()) {
        dbl cur = max(a[i].first, b[j].first);
        dbl nxt = min(a[i + 1].first, b[j + 1].first);

        res.push_back({cur, f(a[i].second, b[j].second)});
        if (eq(nxt, a[i + 1].first)) i++;
        else j++;
      }
      res.push_back({INF, poly(res.back().second.size(), 0)});
      return res;
    };

    auto fix = [&](vector<pair<dbl, poly>> a) {
      vector<pair<dbl, poly>> res;
      for (int i = 0; i < (int)a.size() - 1; i++) {
        dbl l = a[i].first, r = a[i + 1].first;
        auto p = a[i].second;
        if (calc(p, l) <= 0 && calc(p, r) <= 0) {
          res.push_back({l, poly({0, 0})});
        } else {
          if (calc(p, l) >= 0 && calc(p, r) >= 0) {
            res.push_back({l, p});
          } else {
            assert(!eq(p[1], 0));
            dbl x = -p[0] / p[1];
//            db3(l, r, x);
            assert(!ls(x, l) && !ls(r, x));

            if (calc(p, l) <= 0) {
              res.push_back({l, poly({0, 0})});
              res.push_back({x, p});
            } else {
              res.push_back({l, p});
              res.push_back({x, poly({0, 0})});
            }
          }
        }
      }
      res.push_back({INF, poly(a.back().second.size(), 0)});
      return res;
    };

    v1 = comb(v1, v2, [&](const poly &x, const poly &y) {
      assert(x.size() == y.size());
      poly z(x.size());
      for (int i = 0; i < (int)x.size(); i++) z[i] = -(x[i] + y[i]);
      return z;
    });
    v1 = fix(v1);
    v3 = comb(v3, v4, [&](const poly &x, const poly &y) {
      assert(x.size() == y.size());
      poly z(x.size());
      for (int i = 0; i < (int)x.size(); i++) z[i] = -(x[i] + y[i]);
      return z;
    });
    v3 = fix(v3);
    v1 = comb(v1, v3, [&](const poly &x, const poly &y) {
      poly z(x.size() + y.size() - 1);
      for (int i = 0; i < (int)x.size(); i++) {
        for (int j = 0; j < (int)y.size(); j++) {
          z[i + j] += x[i] * y[j];
        }
      }
      return z;
    });

//    for (int i = 0; i < (int)v1.size(); i++) {
//      db(v1[i].first);
//      dbv(v1[i].second);
//    }
    vector<dbl> mx(v1.size());
    for (int i = 0; i < (int)v1.size() - 1; i++) {
      mx[i] = get_max(v1[i].second, v1[i].first, v1[i + 1].first);
    }
    sparse_table<dbl> sp(mx, [&](dbl x, dbl y) { return max(x, y); });

    int q;
    scanf("%d", &q);
    for (int i = 0; i < q; i++) {
      dbl l, r;
      scanf("%lf%lf", &l, &r);

      int i1 = lower_bound(v1.begin(), v1.end(), make_pair(l, poly())) - v1.begin();
      int i2 = lower_bound(v1.begin(), v1.end(), make_pair(r, poly())) - v1.begin() - 2;
      dbl res = i1 <= i2 ? sp.get(i1, i2) : -INF;
//      res = max(res, get_max(v1[i1 - 1].second, l, r));
//      res = max(res, get_max(v1[i2 + 1].second, l, r));
      res = max(res, get_max(v1[i1 - 1].second, max(l, v1[i1 - 1].first), min(r, v1[i1].first)));
      res = max(res, get_max(v1[i2 + 1].second, max(l, v1[i2 + 1].first), min(r, v1[i2 + 2].first)));

      printf("%.17f\n", res);
    }
  }

  return 0;
}
