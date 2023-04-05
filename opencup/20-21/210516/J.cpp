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

#define TIMESTAMP(x) eprintf("[" #x "] Time : %.3lf s.\n", (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() {
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
  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }
    map<int, vector<int>, greater<>> b;
    for (int i = 0; i < n; i++) {
      b[a[i]].push_back(i);
    }

    vector<int> bit(n);
    auto add = [&](int pos, int val) {
      for (; pos < n; pos = (pos | (pos + 1))) {
        bit[pos] += val;
      }
    };
    auto sump = [&](int pos) {
      int res = 0;
      for (; pos != -1; pos = (pos & (pos + 1)) - 1) {
        res += bit[pos];
      }
      return res;
    };

    auto sum = [&](int l, int r) {
      if (l < r) {
        return sump(r - 1) - sump(l - 1);
      }
      return sump(n - 1) - sump(l - 1) + sump(r - 1);
    };
    for (int i = 0; i < n; i++) {
      add(i, 1);
    }

    int cur = 0;
    long long ans = 0;
    for (auto &[_, pos]: b) {
      sort(pos.begin(), pos.end());
      auto it = lower_bound(pos.begin(), pos.end(), cur);
      if (it != pos.end()) {
        rotate(pos.begin(), it, pos.end());
      }
      for (int x : pos) {
        if (cur != x) {
          ans += sum(cur, x);
        }
        add(x, -1);
        cur = x;
      }
    }

    printf("%lld\n", ans);

  }


  return 0;
}
