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

char a[1'000'100];
char b[1'000'100];

int solve() {
  int n, m;
  scanf("%d%d", &n, &m);
  scanf("%s%s", a, b);
  vector<int> lf(n), rg(n);
  for (auto s: {a, b}) {
    vector<int> &to = (s[0] == 'D') ? lf : rg;
    int row = 0, col = 0;
    for (int i = 0; s[i]; i++) {
      if (s[i] == 'R') {
        col++;
      } else {
        to[row] = col;
        row++;
      }
    }
  }
  for (int i = 0; i < n; i++) {
    eprintf("%d: [%d,%d)\n", i, lf[i], rg[i]);
  }
  int cur_val = rg[n - 1] - lf[n - 1] - 1;
  eprintf("i = %d, cur_val = %d\n", n - 1, cur_val);
  for (int i = n - 2; i >= 0; i--) {
    cur_val = min(cur_val - 1, rg[i] - lf[i + 1] - 1);
    if (lf[i] < lf[i + 1]) {
      cur_val = max(cur_val + 1, 0) + (lf[i + 1] - lf[i] - 1);
    }
    eprintf("i = %d, cur_val = %d\n", i, cur_val);
  }
  eprintf("====");
  return cur_val;
}

int main() {
#ifdef LOCAL
  freopen("k.in", "r", stdin);
  freopen("k.out", "w", stdout);
#endif

  int k;
  while (scanf("%d", &k) == 1) {
    int ans = 0;
    for (int i = 0; i < k; i++) {
      ans += solve();
    }
    if (ans > 0) {
      printf("First\n");
    } else {
      printf("Second\n");
    }
  }
  return 0;
}
