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

void solve() {
  int n;
  scanf("%d", &n);
  vector<int> v(n + 1);
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    scanf("%d", &v[i]);
  }
  for (int i = 1; i <= n; i++) {
    scanf("%d", &a[i]);
  }

  string ans(n, '?');

  for (int i = n; i >= 1; i--) {
    vector<int> ids;
    for (int j = i; j >= 1; j /= 2) {
      ids.push_back(j);
      if (j == 1 || a[j] == v[i])
        break;
    }
    int is_max = 1, is_not_max = 1;
    if (a[ids.back()] != v[i])
      is_max = is_not_max = 0;
    if (ids.back() != 1) {
      if (a[ids.back() / 2] > v[i]) is_not_max = 0;
      if (a[ids.back() / 2] < v[i]) is_max = 0;
    }
    for (int j : ids) {
      if (a[j] < v[i]) is_not_max = 0;
      if (a[j] > v[i]) is_max = 0;
    }
    if (is_not_max) {
      ans[i - 1] = '0';
    } else if (is_max) {
      ans[i - 1] = '1';
    } else {
      printf("Impossible\n");
      return;
    }
    for (int j = (int)ids.size() - 1; j > 0; j--) {
      swap(a[ids[j]], a[ids[j - 1]]);
    }
    assert(v[i] == a[i]);
  }
  printf("%s\n", ans.c_str());
}

int main() {
  #ifdef LOCAL
  freopen("i.in", "r", stdin);
  freopen("i.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    solve();
  }

  return 0;
}
