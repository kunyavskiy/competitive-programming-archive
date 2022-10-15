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

const int MAXN = 1001;

int f[MAXN];
int invf[MAXN];

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif


  f[0] = invf[0] = 1;
  for (int i = 1; i < MAXN; i++) {
    f[i] = mul(f[i - 1], i);
    invf[i] = minv(f[i]);
  }

  int n, k;
  while (scanf("%d%d", &n, &k) == 2) {
    int ans = 0;
    vector<int> prob(n + 1);
    for (int i = 1; i <= n; i++) {
      int cni = mul(mul(invf[i], invf[n-i]), f[n]);
      prob[i] = mul(cni, invf[i]);
    }
    prob[1] = 1;
    if (n != 1) {
      sub(prob[1], prob[n]);
    }
    for (int i = n - 1; i > 1; i--) {
      sub(prob[i], prob[i + 1]);
      sub(prob[1], prob[i]);
    }
    for (int i = 1; i <= n; i++) {
      add(ans, mul(mul(mpow(n - i + 1, i), f[n - i]), prob[i]));
    }
    for (int i = 1; i <= n; i++) {
      ans = mul(ans, i);
    }
    printf("%d\n", ans);
  }

  return 0;
}
