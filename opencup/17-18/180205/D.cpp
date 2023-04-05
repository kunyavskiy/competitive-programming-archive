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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD) a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0) a += MOD;
}

int mul(int a, int b) {
  return (int) ((a * 1LL * b) % MOD);
}

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) {
  return mpow(x, MOD - 2);
}

void mod_out(int x __attribute__((unused)), const char *name __attribute__((unused))) {
#ifdef LOCAL
  for (int i = 1; i <= 1000; i++) {
    if (mul(x, i) <= 1000) {
      eprintf("%s = %d/%d\n", name, mul(x, i), i);
      return;
    }
    if (mul(x, i) >= MOD - 1000) {
      eprintf("%s = %d/%d\n", name, mul(x, i) - MOD, i);
      return;
    }
  }
  eprintf("%s = ?/?[%d]\n", name, x);
#endif
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);

  int p = mul(a, minv(b));
  int q = 1;
  sub(q, p);

  mod_out(p, "p");
  mod_out(q, "q");

  int res = 0;
  int g = 1;

  int ans = 1;
  for (int k = 1; k < n; k++) {
    int c;
    if (p != q) {
      int c1 = mpow(p, n - k + 1);
      sub(c1, mpow(q, n - k + 1));
//    mod_out(c1, "c1");
      int c2 = mpow(p, k);
      sub(c2, mpow(q, k));
//    mod_out(c2, "c2");
      c = mul(c1, minv(c2));
    } else {
      int c1 = mul(n - k + 1, minv(mpow(2, n - k)));
      int c2 = mul(k, minv(mpow(2, k - 1)));
      c = mul(c1, minv(c2));
    }
    ans = mul(ans, c);
    mod_out(ans, "ans");
    add(res, mul(ans, g));
    g = mul(g, g);
    add(g, 2);
  }

  mod_out(res, "res");
  printf("%d\n", res);
  return 0;
}
