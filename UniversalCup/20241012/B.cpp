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
#include <numeric>
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

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

const int MAXN = 1000100;

int t[2 * MAXN];
int invv[2 * MAXN + 1];
int fs[2 * MAXN + 1];
int ifs[2 * MAXN + 1];
int ctl[MAXN + 1];
int zero[2 * MAXN + 1];

void solve() {
  int n, p, b0, A, B;
  scanf("%d%d%d%d%d", &n, &p, &b0, &A, &B);
  auto mul = [&](int a, int b) -> int { return (a * 1LL * b) % p;};
  auto add = [&](int& a, int b) {
    unsigned x = unsigned (a) + b;
    if (x >= unsigned (p)) x -= p;
    a = x;
  };
  auto mpow = [&](int a, int b) {
    int res = 1;
    while (b) {
      if (b & 1)
        res = mul(res, a);
      a = mul(a, a);
      b >>= 1;
    }
    return res;
  };

  auto minv = [&](int x) { return mpow(x, p - 2); };

  for (int i = 0; i < 2 * n; ++i) {
    b0 = mul(b0, A);
    add(b0, B);
    t[i] = (i ? t[i - 1] : 0);
    add(t[i], b0 + 1);
  }


  invv[1] = 1;
  for (int i = 2; i <= 2*n; i++) {
    invv[i] = mul(p - invv[p % i], p / i);
#ifdef LOCAL
    assert(mul(i, invv[i]) == 1);
#endif
  }
  fs[0] = ifs[0] = 1;
  for (int i = 1; i <= 2*n; i++) {
    fs[i] = mul(fs[i-1], i);
    ifs[i] = mul(ifs[i-1], invv[i]);
  }
  auto cnk = [&](int n, int k) { return mul(fs[n], mul(ifs[k], ifs[n-k])); };

  for (int i = 0; i <= n; i++) {
    ctl[i] = mul(cnk(2 * i, i), invv[i+1]);
  }
  for (int i = 1; i <= 2 * n; i++) {
    zero[i] = 0;
    if (i % 2 == 1) {
      add(zero[i], mul(ctl[(i - 1) / 2], ctl[n - (i - 1) / 2 - 1]));
    }
  }
  int coef = (p - ctl[n]) % p;
  int ans = 0;
  for (int i = 0; i < 2 * n; i++) {
    add(coef, zero[i]);
    add(coef, zero[i]);
    //eprintf("coef[%d] = %d\n", i, coef);
    add(ans, mul(coef, t[i]));
  }
  ans = mul(ans, minv(ctl[n]));
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
