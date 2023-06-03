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

char s[100'000];
char a[100'000];
char b[100'000];

bool go(int pos, int d1, int d2, int c) {
  if (s[pos] == 0) {
    a[pos] = b[pos] = 0;
    if (c == 0)
      return true;
    return false;
  }
  if (s[pos] - '0' != (d1 + d2 + c) % 10)
    return false;
  if (d1) {
    a[pos] = d1 + '0';
  } else {
    a[pos] = 0;
  }
  if (d2) {
    b[pos] = d2 + '0';
  } else {
    b[pos] = 0;
  }
  array<pair<int, int>, 4> opts;
  opts[0] = {d1, d2};
  opts[1] = {d1, 0};
  opts[2] = {0, d2};
  opts[3] = {0, 0};
  sort(opts.begin(), opts.end());
  int cnt = unique(opts.begin(), opts.end()) - opts.begin();
  for (int i = 0; i < cnt; i++) {
    if (go(pos + 1, opts[i].first, opts[i].second, (d1 + d2 + c) / 10)) {
      return true;
    }
  }
  return false;
}

void solve() {
  scanf("%s", s);
  int n = strlen(s);
  reverse(s, s + n);

  for (int i = 1; i < 10; i++) {
    for (int j = i; j < 10; j++) {
      if (go(0, i, j, 0)) {
        printf("%s %s\n", a, b);
        return ;
      }
    }
  }
  assert(false);
}

int main() {
#ifdef LOCAL
  freopen("a.in", "r", stdin);
  freopen("a.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-- > 0) {
    solve();
  }

  return 0;
}
