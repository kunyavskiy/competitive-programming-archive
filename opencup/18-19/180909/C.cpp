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
#include <random>

#define db(x) cerr << #x << " = " << x << endl
#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock)*1.0/CLOCKS_PER_SEC)

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
typedef __int128 lll;

const int SHIFT = 13;
const ll MASK = (1LL << SHIFT) - 1;
const ll MOD = 1LL << (4 * SHIFT);


namespace fftd {
  struct num {
    double x, y;
    num() {}
    num(double xx, double yy): x(xx), y(yy) {}
    num(double alp): x(cos(alp)), y(sin(alp)) {}
  };
  inline num operator + (num a, num b) { return num(a.x + b.x, a.y + b.y); }
  inline num operator - (num a, num b) { return num(a.x - b.x, a.y - b.y); }
  inline num operator * (num a, num b) { return num(a.x * b.x - a.y * b.y, a.x * b.y + a.y * b.x); }
  inline num conj(num a) { return num(a.x, -a.y); }

  const double PI = acos(-1);

  std::vector<num> root;
  std::vector<int> rev;
  std::vector<num> a0, a1, b0, b1, r0, r1;
  int N;

  void prepRoots() {
    if ((int)root.size() >= N) return;
    int old = root.size();
    root.resize(N);
    if (old == 0) {
      if (root.size() < 2) root.resize(2);
      root[1] = num(1, 0);
    }
    for (int k = 1; (1 << k) < N; k++) {
      if ((1 << k) < old) continue;
      num x(2 * PI / (1LL << (k + 1)));
      for (int i = (1LL << (k - 1)); i < (1LL << (k)); i++) {
        root[2 * i] = root[i];
        root[2 * i + 1] = root[i] * x;
      }
    }
    rev.resize(N);
    for (int i = 1; i < N; i++) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) * (N / 2));
  }

  template<typename T>
  void prepAB(std::vector<T> &A, std::vector<T> &B) {
    N = 1;
    while (N < (int)(A.size() + B.size())) N <<= 1;
    while ((int)A.size() < N) A.push_back(0);
    while ((int)B.size() < N) B.push_back(0);
    prepRoots();
  }

  void fft(std::vector<num> &f) {
    for (int i = 0; i < N; i++) {
      int j = rev[i] >> __builtin_ctz(root.size() / N);
      if (i < j) std::swap(f[i], f[j]);
    }
    for (int k = 1; k < N; k <<= 1) {
      for (int i = 0; i < N; i += 2 * k) {
        for (int j = 0; j < k; j++) {
          num z = f[i + j + k] * root[j + k];
          f[i + j + k] = f[i + j] - z;
          f[i + j] = f[i + j] + z;
        }
      }
    }
  }


  std::vector<ll> mul(std::vector<ll> A, std::vector<ll> B) {
    if (0) {
      vector<ll> C(A.size() + B.size() - 1);
      for (int i = 0; i < (int)A.size(); i++) {
        for (int j = 0; j < (int)B.size(); j++) {
          C[i + j] = (C[i + j] + (lll)A[i] * B[j]) % MOD;
        }
      }
      return C;
    }
    int rsz = A.size() + B.size() - 1;
    prepAB(A, B);

    a0.resize(N);
    a1.resize(N);
    b0.resize(N);
    b1.resize(N);
    r0.resize(N);
    r1.resize(N);

    for (int i = 0; i < N; i++) {
      a0[i] = num(((A[i] >> (SHIFT * 0)) & MASK), ((A[i] >> (SHIFT * 1)) & MASK));
      a1[i] = num(((A[i] >> (SHIFT * 2)) & MASK), ((A[i] >> (SHIFT * 3)) & MASK));
      b0[i] = num(((B[i] >> (SHIFT * 0)) & MASK), ((B[i] >> (SHIFT * 1)) & MASK));
      b1[i] = num(((B[i] >> (SHIFT * 2)) & MASK), ((B[i] >> (SHIFT * 3)) & MASK));
    }
    fft(a0);
    fft(a1);
    fft(b0);
    fft(b1);

    for (int i = 0; i < N; i++) {
      int j = (N - i) & (N - 1);

      num x0 = (a0[i] + conj(a0[j])) * num(0.5, 0);
      num x1 = (a0[i] - conj(a0[j])) * num(0, -0.5);
      num x2 = (a1[i] + conj(a1[j])) * num(0.5, 0);
      num x3 = (a1[i] - conj(a1[j])) * num(0, -0.5);

      num y0 = (b0[i] + conj(b0[j])) * num(0.5 / N, 0);
      num y1 = (b0[i] - conj(b0[j])) * num(0, -0.5 / N);
      num y2 = (b1[i] + conj(b1[j])) * num(0.5 / N, 0);
      num y3 = (b1[i] - conj(b1[j])) * num(0, -0.5 / N);

      r0[i] = x0 * y0 + (x0 * y1 + x1 * y0) * num(0, 1);
      r1[i] = (x0 * y2 + x1 * y1 + x2 * y0) + (x0 * y3 + x1 * y2 + x2 * y1 + x3 * y0) * num(0, 1);
    }
    reverse(r0.begin() + 1, r0.begin() + N);
    reverse(r1.begin() + 1, r1.begin() + N);

    fft(r0);
    fft(r1);

    std::vector<ll> C(N);
    for (int i = 0; i < N; i++) {
      ll z0 = (ll)round(r0[i].x);
      ll z1 = (ll)round(r0[i].y);
      ll z2 = (ll)round(r1[i].x);
      ll z3 = (ll)round(r1[i].y);

      //cerr << z0 << " " << z1 << " " << z2 << " " << z3 << endl;

      C[i] = 0;
      C[i] += z0 << (SHIFT * 0);
      C[i] += z1 << (SHIFT * 1);
      C[i] += z2 << (SHIFT * 2);
      C[i] += z3 << (SHIFT * 3);
      C[i] = ((unsigned long long)C[i]) % MOD;
    }
    C.resize(rsz);
    return C;
  }
}

void print(vector<ll> a) {
  for (int i = 0; i < (int)a.size(); i++) {
    printf("%lld%c", a[i], " \n"[i + 1 == (int)a.size()]);
  }
}

ll rev(ll x, ll m) {
  if (x == 1) return 1;
  return (1 - rev(m % x, x) * (lll)m) / x + m;
}

ll MODSMALL = 1LL << 32;

vector<ll> fast(vector<ll> a, vector<ll> b) {
  int n = a.size();

  vector<lll> fct(n + 1);
  vector<lll> ofct(n + 1);
  vector<int> pw(n + 1);

  fct[0] = 1;
  ofct[0] = 1;
  for (int i = 1; i <= n; i++) {
    fct[i] = fct[i - 1] * i;
    pw[i] = pw[i - 1];
    while (fct[i] % 2 == 0) {
      fct[i] /= 2;
      pw[i]++;
    }
    fct[i] %= MODSMALL;
    ofct[i] = rev(fct[i], MODSMALL);
  }

  vector<ll> na(n), nb(n);
  for (int i = 0; i < n; i++) {
    na[i] = a[i];
    na[i] = na[i] * ofct[i] % MODSMALL;
    for (int j = pw[i]; j < i; j++) {
      na[i] = 2 * na[i] % MOD;
    }

    nb[i] = b[i];
    nb[i] = nb[i] * ofct[i] % MODSMALL;
    for (int j = pw[i]; j < i; j++) {
      nb[i] = 2 * nb[i] % MOD;
    }
  }
  /*for (int i = 0; i < n; i++) {
    cerr << na[i] << " " << nb[i] << endl;
  }*/
  auto nc = fftd::mul(na, nb);
  /*for (int i = 0; i < n; i++) {
    cerr << nc[i] << endl;
  }*/
  for (int i = 0; i < n; i++) {
    for (int j = pw[i]; j < i; j++) {
      assert(nc[i] % 2 == 0);
      nc[i] /= 2;
    }
    nc[i] %= MODSMALL;
    nc[i] = nc[i] * fct[i] % MODSMALL;
  }
  nc.resize(n);
  return nc;
}

void test() {
  int n = 2e5;
  vector<ll> a(n), b(n);
  mt19937 rnd;
  for (int i = 0; i < n; i++) {
    a[i] = rnd();
    b[i] = rnd();
  }
  auto c = fast(a, b);
  cerr << clock() / (double)CLOCKS_PER_SEC << endl;
  exit(0);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  //freopen("c.out", "w", stdout);
#endif

  //test();

  int n;
  while (scanf("%d", &n) == 1) {
    n++;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++) {
      scanf("%lld", &a[i]);
    }
    for (int i = 0; i < n; i++) {
      scanf("%lld", &b[i]);
    }

    print(fast(a, b));
  }

  return 0;
}
