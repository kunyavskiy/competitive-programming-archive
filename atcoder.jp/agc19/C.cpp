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

const int INF = 1000 * 1000 * 1000;

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  int x1, y1, x2, y2;
  while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) == 4) {
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> v(n);
    for (auto &p: v) {
      scanf("%d%d", &p.first, &p.second);
    }
    if (x1 > x2) {
      x1 = -x1;
      x2 = -x2;
      for (auto &p : v) {
        p.first = -p.first;
      }
    }
    if (y1 > y2) {
      y1 = -y1;
      y2 = -y2;
      for (auto &p : v) {
        p.second = -p.second;
      }
    }

    vector<pair<int, int>> v2;
    for (auto p : v) {
      if (x1 <= p.first && p.first <= x2)
        if (y1 <= p.second && p.second <= y2) {
          v2.push_back(p);
        }
    }

    v = v2;

    double ans = (x2 - x1 + y2 - y1) * 100.0;
    sort(v2.begin(), v2.end());
    vector<int> dp(v2.size() + 1, INF);
    for (auto p : v2) {
      *lower_bound(dp.begin(), dp.end(), p.second) = p.second;
    }
    int cnt = 0;
    for (int x : dp) {
      if (x < INF) {
        cnt++;
      }
    }
    ans += (M_PI * 5 - 20) * cnt;
    if (cnt == min(x2 - x1, y2 - y1) + 1) {
      ans += M_PI * 5;
    }
    printf("%.20f\n", ans);
  }

  return 0;
}
