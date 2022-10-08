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

const int MAXN = 310000;

int a[MAXN];
int sum[MAXN];
int sum2[MAXN];

//#define DEBUG

int get_sum(int l, int r) {
  int ans = sum[r] - sum[l];
#ifdef DEBUG2
  int res = 0;
  for (int i = l; i < r; i++) {
    res += a[i];
  }
  assert(ans == res);
#endif
  return ans;
}

int get_sum_lf(int l, int r) {
  int ans;
  if (l % 2 == 0) {
    ans = sum2[r] - sum2[l];
  } else {
    ans = get_sum(l, r) - (sum2[r] - sum2[l]);
  }
#ifdef DEBUG2
  int res = 0;
  for (int i = l; i < r; i += 2) {
    res += a[i];
  }
  if (ans != res) {
    assert(0);
  }
#endif
  return ans;
}

int get_sum_rg(int l, int r) {
  int ans = 0;
  if (l % 2 != r % 2) {
    ans = get_sum_lf(l, r);
  } else {
    ans = get_sum(l, r) - get_sum_lf(l, r);
  }
#ifdef DEBUG2
  int res = 0;
  for (int i = r - 1; i >= l; i -= 2) {
    res += a[i];
  }
  assert(ans == res);
#endif
  return ans;
}

map<pair<int, int>, int> cache;

int solve(int l, int r) {
  if (l == r) {
    return 0;
  }
  auto it = cache.find({l, r});
  if (it != cache.end()) {
    return it->second;
  }
  auto& ans = cache[{l, r}];

  int v = get_sum_lf(l, r);
  ans = abs(get_sum(l, r) - 2 * v);

  if ((r - l) % 2 == 0) {
    return ans;
  }

  int ans0 = ans;


  for (int i = l + 1; i < r - 1; i += 2) {
    int res1, res2;

    res1 = solve(i + 1, r) + (2 * get_sum_rg(l, i + 1) - get_sum(l, i + 1));
    res2 = solve(l, i) + (2 * get_sum_lf(i, r) - get_sum(i, r));
    ans = max(ans, min(res1, res2));
  }

  eprintf("%d %d %d %d\n", l, r, ans, ans0);
  if ((r - l) % 4 != 3) {
    assert(ans == ans0);
  }

  return ans;
}

int main() {
#ifdef LOCAL
  freopen("f.in", "r", stdin);
//  freopen("f.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  for (int i = 0; i < n; i++) {
    sum[i + 1] = sum[i] + a[i];
    sum2[i + 1] = sum2[i];
    if (i % 2 == 0) {
      sum2[i + 1] += a[i];
    }
  }

  int bal = solve(0, n);
  eprintf("bal = %d\n", bal);

  int tot = get_sum(0, n);
  eprintf("cache.size() = %d\n", (int)cache.size());

  printf("%d %d\n", (tot + bal) / 2, (tot - bal) / 2);

  return 0;
}
