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
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
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

void solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n == 1) {
    printf("Yes\n");
    for (int i = 1; i <= m; i++) {
      printf("%d ", i);
    }
    printf("\n");
    return;
  }
  if ((n % 2 == 0 && m % 2 == 1) || m == 1) {
    printf("No\n");
    return;
  }

  int M = m;
  vector<vector<int>> ans(n, vector<int>(M));
  while (m != 3 && m != 0) {
    for (int i = 0; i < n; i++) {
      ans[i][m - 2] = n * (m - 2) + i;
      ans[i][m - 1] = n * (m - 2) + 2 * n - i - 1;
    }
    m -= 2;
  }

  if (m == 3) {
    assert(n % 2 == 1);
    int tot = 3 * (3 * n - 1) / 2;
    for (int i = 0; i < n; i++) {
      ans[i][0] = i;
      ans[i][1] = n + (i + n / 2 + 1) % n;
      ans[i][2] = tot - ans[i][0] - ans[i][1];
    }
  }

  printf("Yes\n");
  eprintf("===\n");
  for (int i = 0; i < n; i++) {
#ifdef LOCAL
    eprintf("sum = %d\n", accumulate(ans[i].begin(), ans[i].end(), 0) );
    assert(accumulate(ans[i].begin(), ans[i].end(), 0) * 2 == M * (n * M - 1));
#endif
    for (int j = 0; j < M; j++) {
      assert(0 <= ans[i][j] && ans[i][j] < n * M);
      printf("%d ", ans[i][j] + 1);
    }
    printf("\n");
  }
}

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
