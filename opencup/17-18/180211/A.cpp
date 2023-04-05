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

ll solve(int d, const vector<vector<int>> &a, int i0, int i1, int i2) {
  ll res = 0;
  for (int j0 = 0; j0 < int(a[i0].size()); ++j0) {
    int L1 = lower_bound(a[i1].begin(), a[i1].end(), a[i0][j0] + (i1 > i0 ? 0 : 1)) - a[i1].begin();
    int R1 = lower_bound(a[i1].begin(), a[i1].end(), a[i0][j0] + d + 1) - a[i1].begin();
    int L2 = lower_bound(a[i2].begin(), a[i2].end(), a[i0][j0] + (i2 > i0 ? 0 : 1)) - a[i2].begin();
    int R2 = lower_bound(a[i2].begin(), a[i2].end(), a[i0][j0] + d + 1) - a[i2].begin();
    eprintf("j0 %d L1 %d R1 %d L2 %d R2 %d\n", j0, L1, R1, L2, R2);
    res += ll(R1 - L1) * (R2 - L2);
  }
  return res;
}


bool solve() {
  int n[3] = {0};
  int d;
  if (scanf("%d%d%d%d", &d, &n[0], &n[1], &n[2]) != 4) {
    return false;
  }
  eprintf("%d %d %d %d\n", d, n[0], n[1], n[2]);
  vector<vector <int>> a(3);
  for (int i = 0; i < 3; ++i) {
    a[i].resize(n[i]);
    for (int j = 0; j < n[i]; ++j) {
      scanf("%d", &a[i][j]);
    }
  }

  ll res = 0;
  res += solve(d, a, 0, 1, 2);
  res += solve(d, a, 1, 0, 2);
  res += solve(d, a, 2, 0, 1);
  printf("%lld\n", res);
  return true;
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  while (solve());

  return 0;
}
