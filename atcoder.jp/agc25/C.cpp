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

ll solve(multiset<pair<int, int>> sl, multiset<pair<int, int>> sr, int x) {
  int n = sl.size();
  ll ans = 0;
  int cur = 0;
  for (int i = 0; i < n; i++) {
    int l, r;
    if (i % 2 == x) {
      tie(l, r) = *sl.rbegin();
    } else {
      tie(r, l) = *sr.begin();
    }
    {
      auto itl = sl.find({l, r});
      assert(itl != sl.end());
      sl.erase(itl);
    }
    {
      auto itr = sr.find({r, l});
      assert(itr != sr.end());
      sr.erase(itr);
    }

    if (cur < l) {
      ans += l - cur;
      cur = l;
    }
    if (cur > r) {
      ans += cur - r;
      cur = r;
    }
  }
  return ans + abs(cur);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  while (scanf("%d", &n) == 1) {
    multiset<pair<int, int>> sl;
    multiset<pair<int, int>> sr;

    for (int i = 0; i < n; i++) {
      int l, r;
      scanf("%d%d", &l, &r);
      sl.insert({l, r});
      sr.insert({r, l});

    }

    ll ans = max(solve(sl, sr, 1), solve(sl, sr, 0));
    printf("%lld\n", ans);
  }

  return 0;
}
