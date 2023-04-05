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


namespace mod {
  typedef long long ll;
  const int MOD = (int)1e9 + 7;

  void add(int &a, ll b) {
    a = (a + b) % MOD;
  }

  int mul(int a, int b) {
    return 1LL * a * b % MOD;
  }

  int bin(int a, ll n) {
    int res = 1;
    while (n) {
      if (n & 1) res = 1LL * res * a % MOD;
      a = 1LL * a * a % MOD;
      n >>= 1;
    }
    return res;
  }

  int inv(int x) {
    return bin(x, MOD - 2);
  }

  vector<int> fct, ofct, rev;

  void ensureFact(int n) {
    if ((int)fct.size() > n) return;
    int old = fct.size();
    fct.resize(n + 1);
    ofct.resize(n + 1);
    rev.resize(n + 1);
    if (old == 0) {
      fct[0] = ofct[0] = 1;
      rev[0] = 0;
      old++;
    }
    for (int i = old; i <= n; i++) {
      fct[i] = mul(fct[i - 1], i);
      if (i == 1) rev[i] = 1;
      else rev[i] = (MOD - mul(MOD / i, rev[MOD % i])) % MOD;
      ofct[i] = mul(ofct[i - 1], rev[i]);
    }
  }

  int getC(int n, int k) {
    if (n < k || k < 0) return 0;
    ensureFact(n);
    return mul(fct[n], mul(ofct[k], ofct[n - k]));
  }
}
using namespace mod;

struct poly : vector<int> {
  using vector<int>::vector;
  poly(const vector<int> &a) : vector<int>(a) {}
  //poly(int x) : vector<int>(1, x) {}

  friend ostream& operator<< (ostream& out, const poly& p) {
    out << p.to_string();
    return out;
  }

  int& operator[](int id) {
    if (id >= (int)size()) resize(id + 1);
    assert(id >= 0 && id < (int)size());
    return vector<int>::operator[](id);
  }

  int operator[](int id) const {
    assert(id >= 0);
    if (id < (int)size()) return vector<int>::operator[](id);
    return 0;
  }

  poly operator+ (const poly &b) {
    const poly &a = *this;
    poly c(max(a.size(), b.size()));
    for (int i = 0; i < (int)c.size(); i++) {
      c[i] = (a[i] + b[i]) % MOD;
    }
    return c;
  }

  poly operator+= (const poly &p) {
    return *this = *this + p;
  }

  poly operator- (const poly &b) {
    const poly &a = *this;
    poly c(max(a.size(), b.size()));
    for (int i = 0; i < (int)c.size(); i++) {
      c[i] = (a[i] - b[i] + MOD) % MOD;
    }
    return c;
  }

  poly operator-= (const poly &p) {
    return *this = *this - p;
  }

  poly operator* (int d) const {
    poly res = *this;
    for (int i = 0; i < (int)size(); i++) {
      res[i] = 1LL * res[i] * d % MOD;
    }
    return res;
  }

  poly operator*= (int d) {
    return *this = *this * d;
  }

  poly operator/ (int d) const {
    poly res = *this;
    d = ::inv(d);
    for (int i = 0; i < (int)size(); i++) {
      res[i] = 1LL * res[i] * d % MOD;
    }
    return res;
  }

  poly operator/= (int d) {
    return *this = *this / d;
  }

  poly operator* (const poly &p) const {
    vector<int> c(this->size() + p.size() - 1);
    for (int i = 0; i < (int)this->size(); i++) {
      for (int j = 0; j < (int)p.size(); j++) {
        c[i + j] = (c[i + j] + 1LL * (*this)[i] * p[j]) % MOD;
      }
    }
    return poly(c);
  }

  poly operator*= (const poly &p) {
    return *this = *this * p;
  }

  poly inv() const {
    assert((*this)[0] != 0);
    poly r(1, ::inv((*this)[0]));
    for (int n = 1; n < (int)size(); n <<= 1) {
      poly ca = cut(2 * n);
      r = (r * 2 - r * r * ca).cut(2 * n);
    }
    r.resize(size());
    return r;
  }

  poly sqrt() const {
    assert((*this)[0] == 1);
    poly r(1, 1);
    for (int n = 1; n < (int)size(); n <<= 1) {
      poly ca = cut(2 * n);
      r = ((r + ca * r.cut(2 * n).inv()) / 2).cut(2 * n);
    }
    r.resize(size());
    return r;
  }

  void norm() {
    while (size() > 1 && back() == 0) {
      pop_back();
    }
  }

  poly rev() const {
    return poly(rbegin(), rend());
  }

  poly cut(int n) const {
    poly res = *this;
    res.resize(n);
    return res;
  }

  pair<poly, poly> div(poly b) const {
    auto a = *this;
    a.norm(); b.norm();
    if (a.size() < b.size()) return make_pair(poly({0}), a);

    int x = b.back();
    assert(x != 0);
    b /= x;

    auto rb = b.rev().cut(a.size() - b.size() + 1);
    auto q = (rb.inv() * a.rev()).cut(a.size() - b.size() + 1).rev();

    poly r = a - b * q;
    q /= x;
    r.norm();
    return {q, r};
  }

  poly operator/ (const poly &p) const {
    return div(p).first;
  }

  poly operator/= (const poly &p) {
    return *this = *this / p;
  }

  poly operator% (const poly &p) const {
    return div(p).second;
  }

  poly operator%= (const poly &p) {
    return *this = *this % p;
  }

  poly derivative() const {
    poly res(max(1, (int)size() - 1), 0);
    for (int i = 1; i < (int)size(); i++) res[i - 1] = mul((*this)[i], i);
    return res;
  }

  poly integrate() const {
    poly res(size() + 1);
    for (int i = 0; i < (int)size(); i++) {
      res[i + 1] = (*this)[i] * 1LL * ::inv(i + 1) % MOD;
    }
    return res;
  }

  int eval(int x) {
    int res = 0;
    for (int i = (int)size() - 1; i >= 0; i--) {
      res = (1LL * res * x + (*this)[i]) % MOD;
    }
    return res;
  }

  string to_string() const {
    string res = "";
    for (int i = 0; i < (int)size(); i++) {
      res += ::to_string((*this)[i]);
      if (i + 1 < (int)size()) res += " ";
    }
    return res;
  }

  bool operator==(const poly &rgh) const {
    return (vector<int>)*this == (vector<int>)rgh;
  }
};

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
//  freopen("f.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> p(n), b(n);
    int root = -1;
    vector<vector<int>> e(n);
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &b[i], &p[i]);
      p[i]--;
      if (p[i] == -1) {
        root = i;
      } else {
        e[p[i]].push_back(i);
      }
    }

    function<vector<pair<int, poly>>(int)> dfs = [&](int v) {
      vector<vector<pair<int, poly>>> t;
      t.resize(1);
      t.back().push_back({0, {inv(b[v])}});
      t.back().push_back({b[v], {0}});

      for (int to : e[v]) {
        t.push_back(dfs(to));
      }
      vector<int> xx;
      for (auto v : t) {
        for (auto o : v) {
          xx.push_back(o.first);
        }
      }
      sort(xx.begin(), xx.end());
      xx.resize(unique(xx.begin(), xx.end()) - xx.begin());

      int m = t.size();
      vector<int> ptr(m);

      for (int i = 1; i < m; i++) {
        int sum = 0;
        for (int j = 0; j + 1 < (int)t[i].size(); j++) {
          int L = t[i][j].first;
          int R = t[i][j + 1].first;
          poly p = t[i][j].second.integrate();
          sum = (sum + p.eval(R) - (ll)p.eval(L) + MOD) % MOD;
        }
        t[i].back().second = poly({0});
        for (int j = (int)t[i].size() - 2; j >= 0; j--) {
          t[i][j].second = t[i][j].second.integrate() * poly({MOD - 1});
          int R = t[i][j + 1].first;
          int delta = (t[i][j + 1].second.eval(R) - t[i][j].second.eval(R) + MOD) % MOD;
          t[i][j].second += poly({delta});
        }
      }

      vector<pair<int, poly>> res;
      for (int x : xx) {
        auto cur = poly({1});
        for (int i = 0; i < m; i++) {
          while (ptr[i] + 1 < (int)t[i].size() && t[i][ptr[i] + 1].first <= x) {
            ptr[i]++;
          }
          cur = cur * t[i][ptr[i]].second;
        }
        res.push_back({x, cur});
      }
//      int all = 0;
//      for (int i = 0; i + 1 < (int)res.size(); i++) {
//        int L = res[i].first;
//        int R = res[i + 1].first;
//        int z = (res[i].second.eval(R) - res[i].second.eval(L) + MOD) % MOD;
//        all = (all + z) % MOD;
//      }
//      for (int i = 0; i < (int)res.size(); i++) {
//        res[i].second = poly({all}) - res[i].second;
//        res[i].second = res[i].second * inv(b[v]);
//      }
      return res;
    };
    auto o = dfs(root);
    int ans = 0;
    for (int i = 0; i < (int)o.size() - 1; i++) {
      int L = o[i].first;
      int R = o[i + 1].first;
      auto p = o[i].second.integrate();
      ans = (ans + (ll)p.eval(R) - p.eval(L) + MOD) % MOD;
    }
    cout << ans << endl;
  }

  return 0;
}
