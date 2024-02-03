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

const int K = 12;

int main() {
#ifdef LOCAL
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  vector<int> deg3(K + 1);
  deg3[0] = 1;
  for (int i = 1; i <= K; i++) {
    deg3[i] = deg3[i-1] * 3;
  }

  int n;
  while (scanf("%d", &n) == 1) {
    set<int> s;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
      s.insert(v[i]);
    }
    vector<vector<bool>> used(2, vector<bool>(deg3[K]));
    auto dfs = [&](auto dfs, int t, int v) {
      assert(v < deg3[K]);
      if (used[t][v])
        return;
      used[t][v] = true;
      if (t == 0) {
        dfs(dfs, 1, v);
      } else if (t == 1 && s.count(v)) {
        dfs(dfs, 0, v);
      }
      for (int i = 0; i < K; i++) {
        int curd = v / deg3[i] % 3;
        if (t == 0) {
          if (curd >= 1) {
            dfs(dfs, 1, v - deg3[i]);
            if (curd >= 2) {
              dfs(dfs, 1, v - 2 * deg3[i]);
            }
          }
        } else if (t == 1 && curd < 2){
          dfs(dfs, 1, v + deg3[i]);
        }
      }
    };
    dfs(dfs, 0, v[0]);
    if (used[0][v.back()]) {
      printf("Yes\n");
    } else {
      printf("No\n");
    }
  }


  return 0;
}
