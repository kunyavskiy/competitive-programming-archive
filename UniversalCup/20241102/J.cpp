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

void solve() {
  int n, m, q;
  scanf("%d%d%d", &n, &m, &q);
  int finished = m;
  int cur_level = -1;
  vector<int> last_level(m, -1);
  vector<ll> score(m);
  for (int i = 0; i < q; i++) {
    int ty;
    scanf("%d", &ty);
    if (ty == 1) {
      scanf("%d", &cur_level);
      finished = m;
    } else if (ty == 2 || ty == 3) {
      int id, level;
      scanf("%d%d", &id, &level);
      id--;
      if (level == cur_level && level != last_level[id]) {
        last_level[id] = level;
        if (ty == 2) {
          score[id] += finished;
          finished--;
        }
      }
    }
  }
  vector<int> order(m);
  std::iota(order.begin(), order.end(), 0);
  stable_sort(order.begin(), order.end(), [&](int a, int b) { return score[a] > score[b]; });
  for (int x : order) {
    printf("%d %lld\n", x + 1, score[x]);
  }
}

int main() {
#ifdef LOCAL
  freopen("j.in", "r", stdin);
  freopen("j.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) solve();
  return 0;
}
