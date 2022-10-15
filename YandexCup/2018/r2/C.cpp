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
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

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
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int n, m, ds, cs, da, ca;
  while (scanf("%d%d%d%d%d%d", &n, &m, &ds, &cs, &da, &ca) == 6) {
    int ans = 0;
    vector<int> hs(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &hs[i]);
    }
    for (int i = 0; i * ca <= m; i++) {
      int killed = 0;
      vector<int> to_kill;
      for (int h : hs) {
        if (h <= i * da) {
          killed++;
        } else {
          to_kill.push_back((h - i * da + ds - 1) / ds);
        }
      }
      sort(to_kill.begin(), to_kill.end());
      int have = (m - i * ca) / cs;
      for (int k : to_kill) {
        if (k <= have) {
          killed++;
          have -= k;
        }
      }
      ans = max(ans, killed);
    }
    printf("%d\n", ans);
  }

  return 0;
}
