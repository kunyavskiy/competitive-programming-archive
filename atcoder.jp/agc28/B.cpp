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

const int MOD = 1000000007;

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

const int MAXN = 110000;

int invv[MAXN];
int invvp[MAXN];
int f[MAXN];
int invf[MAXN];
int coef[MAXN];

int cnk(int n, int k) {
  return mul(f[n], mul(invf[k], invf[n - k]));
}


int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  invv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    invv[i] = mul(MOD - invv[MOD % i], MOD / i);
    assert(mul(i, invv[i]) == 1);
  }

  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i-1], i);
    invf[i] = mul(invf[i-1], invv[i]);
  }

  invvp[0] = 0;
  for (int i = 1; i < MAXN; i++) {
    invvp[i] = invvp[i - 1];
    add(invvp[i], invv[i]);
  }

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      int coef = MOD - 1;
      add(coef, invvp[i + 1]);
      add(coef, invvp[n - i]);
      add(ans, mul(v[i], coef));
    }
    ans = mul(ans, f[n]);

    printf("%d\n", ans);
  }


  return 0;
}
