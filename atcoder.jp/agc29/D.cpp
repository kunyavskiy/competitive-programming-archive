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

int solve(int h, int w, int n) {
  vector<pair<int, int>> p;
  for (int i = 0; i < n; i++) {
    int x, y;
    scanf("%d%d", &x, &y);
    p.emplace_back(x, y);
  }
  sort(p.begin(), p.end());
  int pt = 0;
  int can = 0;
  for (int i = 1; i <= h; i++) {
    bool go = can < w;
    while (pt < (int)p.size() && p[pt].first == i) {
      if (p[pt].second <= can) {
        return i - 1;
      }
      if (p[pt].second == can + 1) {
        go = false;
      }
      pt++;
    }
    if (go) {
      can++;
    }
  }
  return h;
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int h, w, n;
  while (scanf("%d%d%d", &h, &w, &n) == 3) {
    printf("%d\n", solve(h, w, n));
  }

  return 0;
}
