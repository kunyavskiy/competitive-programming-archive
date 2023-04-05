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

int main() {
#ifdef LOCAL
  freopen("g.in", "r", stdin);
  freopen("g.out", "w", stdout);
#endif

  int n;
  scanf("%d", &n);
  char s[30][60];
  for (int i = 0; i < n; ++i) {
    scanf("%s", s[i]);
  }

  int len = strlen(s[0]);
  vector<int> dp(1 << n);
  vector<int> par(1 << n);
  vector<pair<int, int>> split(1 << n);
  for (int mask = 1; mask < (1 << n); ++mask) {
    vector<int> v;
    for (int i = 0; i < n; ++i) {
      if (mask & (1 << i)) {
        v.push_back(i);
      }
    }
    if (v.size() == 1) {
      dp[mask] = 0;
      par[mask] = v[0];
      continue;
    }

    dp[mask] = 100;
    for (int pos = 0; pos < len; ++pos) {
      int mask0 = 0;
      int mask1 = 0;
      for (int i : v) {
        if (s[i][pos] == '0') {
          mask0 |= (1 << i);
        } else {
          mask1 |= (1 << i);
        }
      }
      if (mask0 != mask && mask1 != mask) {
        int cur = 1 + max(dp[mask0], dp[mask1]);
        if (dp[mask] > cur) {
          dp[mask] = cur;
          par[mask] = pos;
          split[mask] = {mask0, mask1};
        }
      }
    }
  }

  auto print = [&](auto &self, int mask) -> void {
    if (dp[mask] == 0) {
      printf("= %d\n", par[mask]);
    } else {
      printf("> %d\n", par[mask]);
      self(self, split[mask].first);
      self(self, split[mask].second);
    }
  };

  print(print, (1 << n) - 1);

  return 0;
}
