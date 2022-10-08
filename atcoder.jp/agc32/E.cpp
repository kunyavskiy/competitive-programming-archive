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
  freopen("e.in", "r", stdin);
  freopen("e.out", "w", stdout);
#endif

  int n, m;
  while (scanf("%d%d", &n, &m) == 2) {
    n *= 2;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
    }
    sort(v.begin(), v.end());

    auto check = [](vector<int> v, int lim, int m) {
      multiset<int> s;
      s.insert(v.begin(), v.end());
      int id = upper_bound(v.begin(), v.end(), lim) - v.begin();

      auto rem = [&](int shift, int from, int to) {
        auto it = s.upper_bound(to);
        if (it == s.begin()) {
          return false;
        }
        --it;
        if (shift + *it < from) {
          return false;
        }
        s.erase(it);
        return true;
      };

      for (int i = id; i < (int)v.size(); i++) {
        auto it = s.find(v[i]);
        if (it == s.end()) continue;
        s.erase(it);
        int x = m + lim - v[i];
        if (!rem(v[i], m, x)) {
          return false;
        }
      }

      for (int i = id; i >= 0; i--) {
        auto it = s.find(v[i]);
        if (it == s.end()) continue;
        s.erase(it);
        int x = m + lim - v[i];
        if (!rem(v[i], m, x)) {
          s.insert(v[i]);
        }
      }

      for (int i = id; i >= 0; i--) {
        auto it = s.find(v[i]);
        if (it == s.end()) continue;
        s.erase(it);
        int x = lim - v[i];
        if (!rem(v[i], 0, x)) {
          return false;
        }
      }

      return s.empty();
    };

    int l = -1, r = m;
    while (r - l > 1) {
      int mid = (l + r) / 2;
      if (check(v, mid, m)) {
        r = m;
      } else {
        l = m;
      }
    }

    printf("%d\n", r);
  }

  return 0;
}
