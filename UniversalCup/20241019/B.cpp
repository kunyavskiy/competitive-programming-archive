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

const int MOD = 998244353;

void add(int &a, int b) {
  if ((a += b) >= MOD)
    a -= MOD;
}

void sub(int &a, int b) {
  if ((a -= b) < 0)
    a += MOD;
}

int mul(int a, int b) { return (int)((a * 1LL * b) % MOD); }

int mpow(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1)
      res = mul(res, a);
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

int minv(int x) { return mpow(x, MOD - 2); }

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    for (int& x : a) scanf("%d", &x);
    vector<pair<int, int>> v;
    int ans = 1;
    for (int i = 0; i < n; i++) {
      int x = a[i];
      while (!v.empty() && v.back().first < x) {
        v.pop_back();
      }
      if (v.empty()) {
        ans = mul(ans, mpow(2, i));
      } else {
        int r = mpow(2, i - v.back().second);
        sub(r, 1);
        r = mul(r, mpow(2, v.back().second));
        ans = mul(ans, r);
      }
      v.emplace_back(x, i);
    }
    printf("%d\n", ans);
  }

  return 0;
}
