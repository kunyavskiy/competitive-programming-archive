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

int read_perm(int n) {
  vector<int> bit(n);
  auto add = [&](int x) {
    while (x < n) {
      bit[x]++;
      x = x | (x + 1);
    }
  };
  auto get = [&](int r) {
    int ans = 0;
    while (r != -1) {
      ans += bit[r];
      r = (r & (r + 1)) - 1;
    }
    return ans;
  };
  ll ans = 0;
  for (int i = 0; i < n; i++) {
    int x;
    scanf("%d", &x);
    --x;
    ans += i - get(x);
    add(x);
  }
  return ans & 1;
}

void solve() {
  int n;
  scanf("%d", &n);
  int cur = read_perm(n);
  cur ^= read_perm(n);

  string ans = string() + "BA"[cur];

  for (int i = 0; i < n - 1; i++) {
    int l, r, d;
    scanf(" %*c %d %d %d", &l, &r, &d);
    if (d % 2 != 0 && (r - l) % 2 == 1) {
      cur ^= 1;
    }
    ans += "BA"[cur];
  }

  printf("%s\n", ans.c_str());

}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
