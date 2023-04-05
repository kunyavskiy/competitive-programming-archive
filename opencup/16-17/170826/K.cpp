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
  if (b == 0) return 1;
  if (b & 1) return mul(mpow(a, b - 1), a);
  return mpow(mul(a, a), b / 2);
}

int inv(int a) {
  return mpow(a, MOD - 2);
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int n, m, k;
  while (scanf("%d%d%d", &n, &k, &m) == 3) {
    int cnk = 1;
    int ans = 0;
    if (m == 1) {
      ans = n - k;
    } else {
      for (int i = m; i <= n + m - k; i++) {
        eprintf("c[%d][%d] = %d\n", i - 2, m - 2, cnk);
        int cur = n + m - k - i;
        cur = mul(cur, 2);
        cur = mul(cur, cnk);
        add(ans, cur);
        cnk = mul(cnk, i - 1);
        cnk = mul(cnk, inv(i + 1 - m));
      }
      sub(ans, n + m - k - m);
    }
    printf("%d\n", ans);
  }

  return 0;
}
