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

# 1 "lib/math/matrix.h"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "lib/math/matrix.h"


# 1 "lib/math/mod_utils.h" 1


namespace mod {
  typedef long long ll;
  const int MOD = 1000000007;

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
# 4 "lib/math/matrix.h" 2

struct matrix {
  vector<vector<int>> a;

  matrix() {}
  matrix(int n, int m) : a(n, vector<int>(m, 0)) {}
  matrix(vector<vector<int>> _a) : a(_a) {}
  matrix(const matrix &_a) : a(_a.a) {}

  vector<int>& operator[](int i) {
    assert(0 <= i && i < (int)a.size());
    return a[i];
  }

  const vector<int>& operator[](int i) const {
    assert(0 <= i && i < (int)a.size());
    return a[i];
  }

  matrix operator+ (const matrix &b) const {
    assert(a.size() == b.a.size() && a[0].size() == b.a[0].size());
    matrix c = *this;
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)a[0].size(); j++) {
        add(c[i][j], b[i][j]);
      }
    }
    return c;
  }

  matrix operator- (const matrix &b) const {
    assert(a.size() == b.a.size() && a[0].size() == b.a[0].size());
    matrix c = *this;
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)a[0].size(); j++) {
        add(c[i][j], MOD - b[i][j]);
      }
    }
    return c;
  }

  matrix operator* (int d) const {
    auto b = *this;
    for (auto &v : b.a) {
      for (auto &x : v) {
        x = mul(x, d);
      }
    }
    return b;
  }

  matrix operator* (const matrix &b) const {
    assert(a[0].size() == b.a.size());
    matrix c(a.size(), b.a[0].size());
    const ll MODMOD = 1LL * MOD * MOD;
    for (int i = 0; i < (int)a.size(); i++) {
      for (int j = 0; j < (int)b.a[0].size(); j++) {
        ll x = 0;
        for (int k = 0; k < (int)a[0].size(); k++) {
          x += 1LL * a[i][k] * b[k][j];
          if (x >= MODMOD) x -= MODMOD;
        }
        c[i][j] = x % MOD;
      }
    }
    return c;
  }

  matrix operator^ (ll p) const {
    matrix a = *this;
    matrix b(a.a.size(), a.a.size());
    for (int i = 0; i < (int)a.a.size(); i++) b[i][i] = 1;
    while (p > 0) {
      if (p % 2 == 0) {
        p /= 2;
        a = a * a;
      } else {
        p--;
        b = b * a;
      }
    }
    return b;
  }

  bool operator== (const matrix &b) const {
    return a == b.a;
  }

  void print() {
    for (auto v : a) {
      for (auto x : v) cout << x << " ";
      cout << endl;
    }
  }
};

int x, n, m, res;
int qq[5][5];
bool z[5];
int p[5];

void bt(int i) {
  if (i == n) {
    int y = 0;
    int c = 0;
    for (int q = 0; q < n; q++) {
      for (int w = q + 1; w < n; w++) {
        int q1 = p[q];
        int w1 = p[w];
        int cc = qq[q1][w1];
        y |= ((x >> c) & 1) << cc;
        c++;
      }
    }
    res = min(res, y);
  } else {
    for (int j = 0; j < n; j++) {
      if (!z[j]) {
        z[j] = true;
        p[i] = j;
        bt(i + 1);
        z[j] = false;
      }
    }
  }
}

bool connected(int x) {
  vector<int> c(n);
  for (int i = 0; i < n; i++) c[i] = i;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if ((x >> qq[i][j]) & 1) {
        int p = c[i];
        for (int k = 0; k < n; k++) {
          if (c[k] == p) c[k] = c[j];
        }
      }
    }
  }
  for (int i = 1; i < n; i++) {
    if (c[i] != c[0]) return false;
  }
  return true;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  scanf("%d", &n);

  m = n * (n - 1) / 2;

  map<int, int> first;

  int c = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      qq[i][j] = qq[j][i] = c++;
    }
  }

  vector<int> s;
  for (x = 0; x < (1 << m); x++) {
    res = x;
    bt(0);
//    cout << x << " " << res << "\n";
    if (res == x) {
      s.push_back(x);
    }
    first[x] = res;
  }

  int N = s.size();

  matrix A(N, N);
  for (int q = 0; q < N; q++) {
    int x = s[q];
    for (int i = 0; i < m; i++) {
      int y = first[x ^ (1 << i)];
      int w = 0;
      while (s[w] != y) w++;
      A[q][w]++;
    }
  }

  vector<bool> con(N);
  matrix B = A;
  for (int q = 0; q < N; q++) {
    int x = s[q];
    if (connected(x)) {
      con[q] = true;
      for (int w = 0; w < N; w++) {
        B[q][w] = 0;
      }
      B[q][q] = m;
    }
  }

  int start = 0;
  int mm;
  scanf("%d", &mm);
  for (int i = 0; i < mm; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    x--; y--;
    start |= (1 << qq[x][y]);
  }

  start = first[start];
  int st = 0;
  while (s[st] != start) st++;

  vector<matrix> AA(60);
  AA[0] = A;
  for (int i = 1; i < (int)AA.size(); i++) {
    AA[i] = AA[i - 1] * AA[i - 1];
  }
  vector<matrix> BB(60);
  BB[0] = B;
  for (int i = 1; i < (int)BB.size(); i++) {
    BB[i] = BB[i - 1] * BB[i - 1];
  }

  int Q;
  scanf("%d", &Q);

  matrix S(1, N);
  S[0][st] = 1;

  for (int i = 0; i < Q; i++) {
    ll l, r;
    scanf("%lld%lld", &l, &r);
//    l = 0;
//    r = 1e15;

    matrix D = S;
    ll pp = l;
    for (int i = 0; i < (int)AA.size(); i++) {
      if (pp & (1ll << i)) {
        D = D * AA[i];
      }
    }
    pp = (r - l);
    for (int i = 0; i < (int)BB.size(); i++) {
      if (pp & (1ll << i)) {
        D = D * BB[i];
      }
    }

    int res = 0;
    for (int i = 0; i < N; i++) {
      if (con[i]) add(res, D[0][i]);
    }

    res = mul(res, inv(bin(m, r)));

    cout << res << "\n";
  }

  //cout << s.size() << "\n";

  return 0;
}
