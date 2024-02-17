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

void solve(int n) {
  vector<int> x(n), y(n);
  vector<char> c(n);
  for (int i = 0; i < n; i++) {
    scanf("%d %d %c", &x[i], &y[i], &c[i]);
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (c[i] == c[j]) {
        for (int k = 0; k < n; k++) {
          if ((x[k] - x[i]) * 1LL * (y[j] - y[i]) - (x[j] - x[i]) * 1LL * (y[k] - y[i]) != 0) {
            printf("Infinity\n");
            return;
          }
        }
        printf("2\n");
        return;
      }
    }
  }
  printf("1\n");
}

int main() {
  #ifdef LOCAL
  freopen("c.in", "rnd", stdin);
  freopen("c.out", "w", stdout);
  #endif

  int n;
  while (scanf("%d", &n) == 1) {
    solve(n);
  }

  return 0;
}
