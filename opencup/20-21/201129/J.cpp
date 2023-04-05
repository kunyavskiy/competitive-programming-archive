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

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    vector<int> mx(n * m + 1, std::numeric_limits<int>::max()), Mx(n * m + 1, std::numeric_limits<int>::min());
    vector<int> my(n * m + 1, std::numeric_limits<int>::max()), My(n * m + 1, std::numeric_limits<int>::min());
    vector<vector<int>> a(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        scanf("%d", &a[i][j]);
        mx[a[i][j]] = min(mx[a[i][j]], 2 * i);
        my[a[i][j]] = min(my[a[i][j]], 2 * j);
        Mx[a[i][j]] = max(Mx[a[i][j]], 2 * (i + 1));
        My[a[i][j]] = max(My[a[i][j]], 2 * (j + 1));
      }
    }

    vector<vector<ll>> v(2 * n + 1, vector<ll>(2 * m + 1));
    vector<vector<ll>> h(2 * n + 1, vector<ll>(2 * m + 1));

    for (int val = 0; val <= n * m; val++) {
      if (mx[val] > Mx[val]) continue;
      for (int i = mx[val] + 1; i < Mx[val] - 1; i++) {
        v[i][my[val] + 1] += val;
        v[i][My[val] - 1] += val;
      }
      for (int j = my[val] + 1; j < My[val] - 1; j++) {
        h[mx[val] + 1][j] += val;
        h[Mx[val] - 1][j] += val;
      }
    }

    long long ans = 0;
    for (int val = 0; val <= n * m; val++) {
      if (mx[val] > Mx[val]) continue;
      long long x = 0;
      for (int i = mx[val]; i < Mx[val]; i++) {
        x += h[i][my[val]];
        x += h[i][My[val]];
      }
      for (int j = my[val]; j < My[val]; j++) {
        x += v[mx[val]][j];
        x += v[Mx[val]][j];
      }
      assert(x % 2 == 0);
      x /= 2;
      ans += x ^ val;
#ifdef LOCAL
      printf("%lld %d\n", x, val);
#endif
    }
    printf("%lld\n", ans);
  }

  return 0;
}
