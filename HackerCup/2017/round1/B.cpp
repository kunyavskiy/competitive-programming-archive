//#include <iostream>
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
#include <stdarg.h>

#define mp make_pair
#define pb push_back

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

#if (_WIN32 || __WIN32__)
#define LLD "%I64d"
#else
#define LLD "%lld"
#endif

using namespace std;

#define TASKNAME "B"

typedef long long ll;
typedef long double ld;

void solve() {
  int n, r;
  scanf("%d%d", &n, &r);
  vector<int> x(n), y(n);

  for (int i = 0; i < n; i++) {
    scanf("%d%d", &x[i], &y[i]);
  }

  int ans = 0;

  for (int x1 : x) {
    for (int y1 : y) {
      for (int x2 : x) {
        for (int y2 : y) {
          int cnt = 0;
          for (int i = 0; i < n; i++) {
            if (x1 <= x[i] && x[i] <= x1 + r && y1 <= y[i] && y[i] <= y1 + r) {
              cnt++;
              continue;
            }
            if (x2 <= x[i] && x[i] <= x2 + r && y2 <= y[i] && y[i] <= y2 + r) {
              cnt++;
              continue;
            }
          }
          ans = max(ans, cnt);
        }
      }
    }
  }
  printf("%d\n", ans);
}

int main() {
  freopen(TASKNAME".in", "r", stdin);
  freopen(TASKNAME".out", "w", stdout);

  int t;
  scanf("%d", &t);
  for (int i = 1; i <= t; i++) {
    fprintf(stderr, "Case #%d\n", i);
    printf("Case #%d: ", i);
    solve();
  }

  return 0;
}
