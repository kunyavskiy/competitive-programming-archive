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

char buf[110000];

int dp[1024];
int ndp[1024];
int dp2[1024][10];

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  while (scanf("%s", buf) == 1) {
    memset(dp, 0, sizeof(dp));
    memset(dp2, 0, sizeof(dp2));
    dp[0] = 1;

    for (int i = 0; buf[i]; i++) {
      int d = buf[i] - '0';
      memset(ndp, 0, sizeof(ndp));

      for (int mask = 0; mask < 1024; mask++) {
        if (mask & (1 << d)) {
          add(ndp[mask], dp[mask ^ (1 << d)]);
        }
        add(ndp[mask], dp2[mask][d]);
        add(dp2[mask][d], dp[mask]);
      }

      memcpy(dp, ndp, sizeof(dp));
    }

    int ans = 0;
    for (int i = 1; i < 1024; i++) {
      add(ans, dp[i]);
    }

    printf("%d\n", ans);
  }

  return 0;
}
