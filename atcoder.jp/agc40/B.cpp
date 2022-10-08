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

  int n;
  while (scanf("%d", &n) == 1) {
    vector<pair<int, int>> v(n);
    int ans = 0;
    for (auto &x : v) {
      scanf("%d%d", &x.first, &x.second);
      ++x.second;
    }
    sort(v.begin(), v.end());
    auto intersect = [](pair<int, int> a, pair<int, int> b) -> pair<int, int>{
      return {max(a.first, b.first), min(a.second, b.second)};
    };
    auto len = [](pair<int, int> a) {
      return max(0, a.second - a.first);
    };

    vector<pair<int, int>> pr(n);
    pr[0] = v[0];
    for (int i = 1; i < n; i++) {
      pr[i] = intersect(pr[i - 1], v[i]);
    }
    vector<pair<int, int>> sf(n);
    sf.back() = v.back();
    for (int i = n - 2; i >= 0; i--) {
      sf[i] = intersect(sf[i + 1], v[i]);
    }

    for (int i = 0; i < n - 1; i++) {
      ans = max(ans, len(pr[i]) + len(sf[i + 1]));
      pair<int, int> other;
      if (i == 0) {
        other = sf[1];
      } else if (i == n - 1) {
        other = pr[n - 2];
      } else {
        other = intersect(pr[i - 1], sf[i + 1]);
      }
      ans = max(ans, len(v[i]) + len(other));
    }

    printf("%d\n", ans);
  }

  return 0;
}
