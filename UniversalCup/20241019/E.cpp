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
#include <variant>
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

int main() {
#ifdef LOCAL
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int q;
  while (scanf("%d", &q) == 1) {
    vector<variant<int, vector<int>>> ops;
    ops.push_back(vector<int>(1, 1));
    int size = 1;

    for (int op = 0; op < q; op++) {
      int ty, x;
      scanf("%d%d", &ty, &x);
      if (ty == 1) {
        if (ops.back().index() != 1) {
          ops.push_back(vector<int>());
        }
        get<1>(ops.back()).push_back(x);
        size++;
      } else if (ty == 2) {
        ops.push_back(x);
        size *= 2;
      } else if (ty == 3) {
        --x;
        if (x >= size) {
          printf("-1\n");
        } else {
          for (int i = (int)ops.size() - 1;; i--) {
            if (ops[i].index() == 0) {
              if (x % 2 == 0) {
                printf("%d\n", get<0>(ops[i]));
                break;
              }
              x /= 2;
            } else {
              auto &v = get<1>(ops[i]);
              if (x >= (int)v.size()) {
                x -= (int)v.size();
              } else {
                printf("%d\n", v[v.size() - x - 1]);
                break;
              }
            }
          }
        }
      }
      size = min(size, 1'000'100'000);
    }
  }

  return 0;
}
