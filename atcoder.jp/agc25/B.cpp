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

const int MAXN = 310000;

int facs[MAXN];
int ifacs[MAXN];

void init_facs() {
  facs[0] = ifacs[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    facs[i] = mul(facs[i - 1], i);
    ifacs[i] = minv(facs[i]);
  }
}

int cnk(int n, int k) {
  return mul(facs[n], mul(ifacs[k], ifacs[n - k]));
}

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  init_facs();

  ll n, a, b, k;
  while (scanf("%lld%lld%lld%lld", &n, &a, &b, &k) == 4) {
    int ans = 0;
    for (int i = 0; i <= n; i++) {
      if (i * a <= k && (k - i * a) % b == 0) {
        ll cnta = i;
        ll cntb = (k - i * a) / b;
        if (cntb <= n) {
          add(ans, mul(cnk(n, cnta), cnk(n, cntb)));
        }
      }
    }
    printf("%d\n", ans);
  }




  return 0;
}
