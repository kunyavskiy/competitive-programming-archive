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
#define pb push_back
#define sz(a) (int)(a).size()
#define all(a) (a).begin() (a).end()
#define pw(x) (1ll << (x))


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
  const int MOD = 998244353;

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
namespace fft {

  std::vector<int> root;
  std::vector<int> rev;
  int N;

  void prepRoots(int NMOD) {
    if (MOD == NMOD && (int)root.size() >= N) return;
    assert(MOD == NMOD);


    int cN = max(N, 1 << 17);
    rev.resize(cN);
    root.resize(cN);
    for (int i = 1; i < cN; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (cN / 2));
    int croot = 2;
    while (!(bin(croot, cN) == 1 && bin(croot, cN / 2) != 1)) croot++;
    int cur = 1;
    for (int i = cN >> 1; i < cN; i++) {
      root[i] = cur;
      cur = 1LL * cur * croot % MOD;
    }
    for (int i = (cN >> 1) - 1; i >= 1; i--) {
      root[i] = root[i * 2];
    }
  }

  void prepAB(std::vector<int> &A, std::vector<int> &B, int NMOD) {
    N = 1;
    while (N < (int)(A.size() + B.size())) N <<= 1;
    while ((int)A.size() < N) A.push_back(0);
    while ((int)B.size() < N) B.push_back(0);
    prepRoots(NMOD);
  }

  void fft(std::vector<int> &f) {
    for (int i = 0; i < N; i++) {
      int j = rev[i] >> __builtin_ctz(root.size() / N);
      if (i < j) std::swap(f[i], f[j]);
    }
    for (int k = 1; k < N; k <<= 1) {
      for (int i = 0; i < N; i += 2 * k) {
        for (int j = 0; j < k; j++) {
          int z = 1LL * f[i + j + k] * root[j + k] % MOD;
          f[i + j + k] = (f[i + j] - z + MOD) % MOD;
          f[i + j] = (f[i + j] + z) % MOD;
        }
      }
    }
  }

  std::vector<int> mulMod(std::vector<int> a, std::vector<int> b, int NMOD = MOD) {
    int rsz = a.size() + b.size() - 1;
    bool eq = a == b;
    prepAB(a, b, NMOD);

    fft(a);
    if (eq) {
      b = a;
    } else {
      fft(b);
    }
    int oN = inv(N);
    for (int i = 0; i < N; i++) {
      a[i] = 1LL * a[i] * b[i] % MOD * oN % MOD;
    }
    reverse(a.begin() + 1, a.begin() + N);
    fft(a);
    a.resize(rsz);

    return a;
  }
}
struct fft_online {
  vector<int> a, b, c;

  fft_online(vector<int> _a) : a(_a) {}

  int add(int k, int x) {
    if ((int)c.size() < 3 * (k + 1)) {
      a.resize(max((int)a.size(), 4 * (k + 1)));
      b.resize(max((int)b.size(), 4 * (k + 1)));
      c.resize(max((int)c.size(), 4 * (k + 1)));
    }
    b[k] = x;
    c[k] = (c[k] + a[0] * (ll)b[k]) % MOD;
    int z = 1;

    while ((k & (z - 1)) == (z - 1)) {

      vector<int> ca(z), cb(z);
      for (int i = 0; i < z; i++) ca[i] = a[z + i];
      for (int i = 0; i < z; i++) cb[i] = b[k - z + 1 + i];
      auto cc = fft::mulMod(ca, cb, MOD);
      for (int i = 0; i < 2 * z - 1; i++) mod::add(c[k + 1 + i], cc[i]);
      z <<= 1;
    }
    return c[k];
  }



};

struct poly : vector<int> {
  using vector<int>::vector;
  poly(const vector<int> &a) : vector<int>(a) {}
  poly(int x) : vector<int>(1, x) {}

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
    return poly(fft::mulMod(*this, p, MOD));
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

  poly exp() const {
    assert((*this)[0] == 0);
    fft_online t(derivative());
    vector<int> g(size());
    g[0] = 1;
    for (int i = 1; i < (int)g.size(); i++) {
      int x = t.add(i - 1, g[i - 1]);
      g[i] = mul(x, ::inv(i));
    }
    return g;
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

  int eval(int x) const {
    int res = 0;
    int cur = 1;
    for (int i = 0; i < (int)size(); i++) {
      res = (res + 1LL * cur * (*this)[i]) % MOD;
      cur = 1LL * cur * x % MOD;
    }
    return res;
  }
};

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  //freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);

    function<poly(int, int)> rec = [&](int l, int r) {
      if (l == r) {
        poly p(vector<int>({a[l], MOD - 1}));
        return p;
      }
      int m = (l + r) >> 1;
      return rec(l, m) * rec(m + 1, r);
    };
    auto p = rec(0, n - 1);

    //cout << p.to_string() << endl;

    int mn = *min_element(a.begin(), a.end());

    vector<int> b(p.size() + 1);
    for (int i = 0; i < (int)p.size(); i++) {
      b[i + 1] = 1LL * p[i] * inv(i + 1) % MOD;
    }
    int ans = poly(b).eval(mn);
    for (int x : a) ans = 1LL * ans * inv(x) % MOD;
    cout << ans << endl;
  }

  return 0;
}
