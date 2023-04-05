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

const int MAXN = 10 * 1000 * 1000;

int invv[MAXN];
int f[MAXN];
int invf[MAXN];

int cnk(int n, int k) {
  if (n < 0) {
    int x = cnk((-n) + k - 1, k);
    if (k % 2 == 1) x = MOD - x;
    return x;
  }
  assert(n >= k);
  assert(n < MAXN);
  return mul(f[n], mul(invf[k], invf[n - k]));
}

void solve(int n) {
  if (n % 2 == 0) {
    printf("%d\n", mpow(10, n / 2));
    return;
  }
  int m = n / 2;
  int ans = 0;
  for (int i = 0; i < 5; i++) {
    int cans = 0;
    int need = 9 * (m / 2) + i;
    for (int x = 0; x * 10 <= need; x++) {
      int cur = 1;
      if ((x + need) % 2) {
        cur = MOD - 1;
      }
      cur = mul(cur, cnk(m, x));
      cur = mul(cur, cnk(-m, need - 10 * x));
      add(cans, cur);
    }
//    eprintf("%d %d\n", 2 * i, cans);
    add(ans, cans);
  }
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  invv[1] = 1;
  for (int i = 2; i < MAXN; i++) {
    invv[i] = mul(MOD - invv[MOD % i], MOD / i);
    assert(mul(i, invv[i]) == 1);
  }

  f[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
  }
  invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    invf[i] = mul(invf[i - 1], invv[i]);
  }

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }
  return 0;
}
