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
  freopen("b.in", "r", stdin);
  freopen("b.out", "w", stdout);
#endif

  int n, l;
  while (scanf("%d%d", &l, &n) == 2) {
    vector<int> v(n);
    for (int &x: v) {
      scanf("%d", &x);
    }

    vector<int> bv;

    ll ans = 0;
    for (int i = 0; i <= n; i++) {
      ll cur;
      if (v.empty()) {
        cur = bv.back();
      } else if (bv.empty()) {
        cur = v.back();
      } else {
        {
          cur = 0;
          int sz = min(v.size(), bv.size());
          for (int j = 0; j < sz; j++) {
            cur += 2 * v[v.size() - j - 1];
            cur += 2 * bv[bv.size() - j - 1];
          }
          cur -= min(v.back(), bv.back());
        }
      }

      eprintf("\n");
      for (int x : v) {
        eprintf("%d ", x);
      }
      eprintf("\n");
      for (int x : bv) {
        eprintf("%d ", x);
      }
      eprintf("\n");
      eprintf("%d %lld\n", i, cur);

      ans = max(ans, cur);
      if (v.size()) {
        bv.push_back(l - v.back());
        v.pop_back();
      }
    }

    printf("%lld\n", ans);
  }

  return 0;
}
