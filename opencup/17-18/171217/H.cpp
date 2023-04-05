#include <iostream>
#include <vector>
#include <cassert>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MOD = 998244353;
const int ROOT = 3;

typedef vector<int> vi;

int mmul(int a, int b) {
  return (a * 1LL * b) % MOD;
}

void madd(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void msub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}


int mpow(int a, int b) {
  if (!b) return 1;
  if (b & 1) return (mpow(a, b - 1) * 1LL * a) % MOD;
  int temp = mpow(a, b / 2);
  return (temp * 1LL * temp) % MOD;
}

bool checkRoot(int x) {
  return mpow(x, (MOD - 1) / 7) != 1 && mpow(x, (MOD - 1) / 17) != 1 && mpow(x, (MOD - 1) / 2) != 1;
}

const int MROOT = 19;
const int MROOTP = 1 << MROOT;
int rts[MROOTP + 10], brev[MROOTP + 10];

void PreCalcRoots() {
  rts[0] = 1; // ROOT is primary root for MOD
  rts[1] = mpow(ROOT, (MOD - 1) / MROOTP);
  for (int i = 2; i < MROOTP; i++)
    rts[i] = mmul(rts[i - 1], rts[1]);
  for (int i = 0; i < MROOTP; i++)
    brev[i] = (brev[i >> 1] >> 1) | ((i & 1) << (MROOT - 1));
}

inline void butterfly(int &a, int &b, int x) {
  int temp = mmul(x, b);
  b = a;
  madd(a, temp);
  madd(b, MOD - temp);
}

void fft(vi &a, bool inv) {
  int n = __builtin_ctz(((int) ((a).size())));
  for (int i = 0; i < (1 << n); i++) {
    int temp = brev[i] >> (MROOT - n);
    if (temp > i) swap(a[i], a[temp]);
  }
  for (int step = 0; step < n; step++) {
    int pos = 0;
    int dlt = (inv ? -1 : 1) * (1 << (MROOT - step - 1));
    for (int i = 0; i < (1 << n); i++) {
      if ((i ^ (1 << step)) > i)
        butterfly(a[i], a[i ^ (1 << step)], rts[pos]);
      pos = (pos + dlt) & (MROOTP - 1);
    }
  }
}

vi multiply(vi a, vi b) {
  int rsz = ((int) ((a).size())) + ((int) ((b).size())), rsz2 = 1;
  while (rsz2 < rsz) rsz2 *= 2;
  a.resize(rsz2);
  b.resize(rsz2);
  fft(a, false);
  fft(b, false);
  for (int i = 0; i < ((int) ((a).size())); i++)
    a[i] = mmul(a[i], b[i]);
  fft(a, true);
  int in = mpow(((int) ((a).size())), MOD - 2);
  for (int i = 0; i < ((int) ((a).size())); i++)
    a[i] = mmul(a[i], in);
  return a;
}

vi inverse(vi a) {
  assert(a[0] != 0);
  vi x(1, mpow(a[0], MOD - 2));
  while (((int) ((x).size())) < ((int) ((a).size()))) {
    vi temp(a.begin(), a.begin() + min(((int) ((a).size())), 2 * ((int) ((x).size()))));
    vi nx = multiply(multiply(x, x), temp);
    x.resize(2 * ((int) ((x).size())));
    for (int i = 0; i < ((int) ((x).size())); i++)
      madd(x[i], x[i]), madd(x[i], MOD - nx[i]);
  }
  return x;
}

vi e2p(vi e) {
  size_t k = e.size();
  vi num(k);
  for (size_t i = 0; i < k; i++) {
    msub(num[i], mmul(i, e[i]));
  }
  vi res = multiply(num, inverse(e));
  res.resize(k);
  for (size_t i = 1; i < k; i += 2){
    res[i] = MOD - res[i];
  }
  return res;
}

void check(vi p, vi e, vi q) {
  size_t k = p.size();
  vi e2 = e;
  for (size_t i = 0; i < k; i++) {
    e2[i] = mmul(e2[i], i);
  }
  vi prod = multiply(p, e);
  for (size_t i = 0; i < k; i++) {
    int x = prod[i];
    madd(x, q[i]);
    assert(e2[i] == x);
  }
}

vi p2e_rec(vi p, vi q) {
  if (p.size() == 1) {
    if (p[0] == 0) {
      assert(q[0] == 0);
      return vi(1, 1);
    }
    return vi(1, (MOD - mmul(q[0], mpow(p[0], MOD - 2))) % MOD);
  }
  size_t n2 = p.size();
  assert(n2 % 2 == 0);
  size_t n = n2 / 2;
  vi p1 = vi(p.begin(), p.begin() + n);
  vi q1 = vi(q.begin(), q.begin() + n);
  vi p2 = vi(p.begin() + n, p.end());
  vi q2 = vi(q.begin() + n, q.end());

  vi e1 = p2e_rec(p1, q1);

//  check(e1, p1, q1);

  vi prod = multiply(e1, p1);
  for (size_t i = 0; i < n; i++) {
    madd(q2[i], prod[i + n]);
  }
  prod = multiply(p2, e1);
  for (size_t i = 0; i < n; i++) {
    madd(q2[i], prod[i]);
  }
  msub(p1[0], n);
  vi e2 = p2e_rec(p1, q2);
//  check(e2, p1, q2);
  e1.insert(e1.end(), e2.begin(), e2.end());
//  check(e1, p, q);
  return e1;
}


vi p2e(vi p) {
  size_t k = p.size();
  vi q(k, 0);
  return p2e_rec(p, q);
}


vi readPoly(int n, int k) {
  vi r(n + 1);
  for (int i = 0; i <= n; i++) {
    scanf("%d", &r[i]);
  }
  r.resize(k);
  return r;
}

int main() {
#ifdef LOCAL
  freopen("h.in", "r", stdin);
  freopen("h.out", "w", stdout);
#endif

  checkRoot(ROOT);
  PreCalcRoots();

  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);

  int real_k = k;

  while (k & (k - 1)) {
    k++;
  }

  vi ef = readPoly(n, k);
  vi eg = readPoly(m, k);

  vi pf = e2p(ef);
  vi pg = e2p(eg);

  vi ph(k);
  for (int i = 0; i < k; i++) {
    ph[i] = mmul(pf[i], pg[i]);
    if (i % 2 == 0) {
      ph[i] = (MOD - ph[i]) % MOD;
    }
  }

  vi eh = p2e(ph);

  for (int i = 0; i < real_k; i++) {
    printf("%d ", (eh[i] + MOD) % MOD);
  }
  printf("\n");
  return 0;
}
