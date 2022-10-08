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

const ll LIM = 1e15;

ll smul(ll a, ll b) {
  ll res;
  if (__builtin_mul_overflow(a, b, &res)) return LIM + 1;
  return min(res, LIM + 1);
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    vector<vector<ll>> ans(n, vector<ll>(n));
    ll prev = 0;
    int D = 23;
    for (int i = 0; i < n; i++) {
      int start = 0;
      int end = n;
      int dir = 1;
      if (i & 1) {
        start = n - 1;
        end = -1;
        dir = -1;
      }
      for (int j = start; j != end; j += dir) {
        if (i == 0 && j == 0) {
          prev = 2 * D;
        } else {
          if (i) {
            prev = smul(prev / __gcd(prev, ans[i-1][j]), ans[i-1][j]);
          }
          prev += D;
        }
        assert(prev < LIM);
        ans[i][j] = prev;
      }
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        printf("%lld ", ans[i][j]);
      }
      printf("\n");
    }
  }

  return 0;
}
