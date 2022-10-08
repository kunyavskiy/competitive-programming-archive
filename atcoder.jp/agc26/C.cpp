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

map<pair<string, int>, int> get(string s) {
  map<pair<string, int>, int> r;
  int n = s.size();
  for (int i = 0; i < (1 << n); i++) {
    string t0, t1;
    for (int j = 0; j < n; j++) {
      if (i & (1 << j)) {
        t1 += s[j];
      } else {
        t0 += s[j];
      }
    }
    reverse(t1.begin(), t1.end());
    r[{t0 + t1, t0.size()}] += 1;
  }
  return r;
};

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n;
  static char buf[200];
  while (scanf("%d%s", &n, buf) == 2) {
    string p1 = string(buf, buf + n);
    string p2 = string(buf + n, buf + 2 * n);
    reverse(p2.begin(), p2.end());
    auto cnt1 = get(p1);
    auto cnt2 = get(p2);

    ll ans = 0;
    for (auto x : cnt1) {
      ans += x.second * 1LL * cnt2[x.first];
    }

    printf("%lld\n", ans);
    //break;
  }

  return 0;
}
