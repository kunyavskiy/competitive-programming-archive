#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <fstream>
#include <functional>
#include <numeric>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <vector>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr, __VA_ARGS__)
clock_t __my_start_clock = clock();
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x)                                                           \
  eprintf("[" #x "] Time : %.3lf s.\n",                                        \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)
#define TIMESTAMPf(x, ...)                                                     \
  eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__,                            \
          (clock() - __my_start_clock) * 1.0 / CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char *what) : what(what){};
  __timestamper(const string &what) : what(what){};
  ~__timestamper() { TIMESTAMPf("%s", what.data()); }
} __TIMESTAMPER("end");
#else
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;

char s[510'000];

void solve() {
  scanf("%s", s);
  int n = strlen(s);
  bool fail = n < 5;
  fail = fail || s[0] != '>';
  fail = fail || s[n - 1] != '>';
  fail = fail || s[n - 2] != '>';
  fail = fail || s[n - 3] != '>';
  fail = fail || count(s, s + n, '-') == 0;
  if (fail) {
    printf("No\n");
    return;
  }
  vector<pair<int, int>> ans;
  int last = n - 3;
  for (; s[last] != '-'; last--) {
    ans.emplace_back(0, last + 2);
  }
  for (int i = 1; i < last; i++) {
    if (s[i] == '>') {
      ans.emplace_back(i, last + 3);
    }
  }
  printf("Yes %d\n", (int)ans.size());
  for (auto [x, y] : ans) {
    printf("%d %d\n", x + 1, y - x + 1);
  }
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }


  return 0;
}
