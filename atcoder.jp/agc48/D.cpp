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

vector<vector<int>> dp;
vector<int> a;

int calc(int l, int r) {
  auto &ans = dp[l][r];
  if (ans != numeric_limits<int>::min()) {
    return ans;
  }
  if (r - l == 1) {
    return ans = 1;
  }
  if (r - l == 2) {
    return a[l] - a[l + 1];
  }

  auto eat_left = calc(l + 1, r);
  auto eat_right = calc(l, r - 1);
  eprintf("l,r = [%d, %d], left = %d, right = %d", l, r, eat_left, eat_right);
  if (eat_left + 1 >= eat_right) {
    ans = eat_left + 1;
  } else if (a[l] <= a[r - 1]) {
    ans = a[r - 1] - a[l];
  } else {
    ans = a[l] - a[r - 1];
  }
  eprintf(" -> %d\n", ans);
  return ans;
}

int solve() {
  int n;
  scanf("%d", &n);
  a.resize(n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  dp = vector<vector<int>>(n + 1, vector<int>(n + 1, numeric_limits<int>::min()));
  return calc(0, n);
}

map<pair<vector<int>, int>, bool> res;

bool solve_stupid(vector<int> a, int move) {
  if (res.find({a, move}) != res.end()) {
    return res[{a, move}];
  }
  bool& ans = res[{a, move}];
  if (move == 0) {
    if (!a.size()) {
      return ans = false;
    }
    while (a[0] > 1) {
      --a[0];
      if (solve_stupid(a, 1 - move)) {
        return ans = true;
      }
    }
    a.erase(a.begin());
    return ans = solve_stupid(a, 1 - move);
  } else {
    if (!a.size()) {
      return ans = true;
    }
    while (a.back() > 1) {
      --a.back();
      if (!solve_stupid(a, 1 - move)) {
        return ans = false;
      }
    }
    a.pop_back();
    return ans = solve_stupid(a, 1 - move);
  }
}


int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  int t;
  scanf("%d", &t);
  while (t-->0) {
    int ans = solve();
#ifdef LOCAL
    res.clear();
    if ((ans > 0) != solve_stupid(a, 0)) {
      eprintf("t = %d, ans = %d\n", t, ans);
      for (int i : a) {
        eprintf("%d ", i);
      }
      eprintf("\n");
      assert(0);
    }
#endif
    eprintf("ans = %d\n", ans);
    if (ans > 0) {
      printf("First\n");
    } else {
      printf("Second\n");
    }
  }

  return 0;
}
