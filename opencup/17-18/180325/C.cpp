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

bool check(string s, int ans) {
  int n = s.size();
  vector<bool> dp(1 << n);
  {
    int mask = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '1') {
        mask |= 1 << i;
      }
    }
    dp[mask] = true;
  }
  int all = (1 << n) - 1;
  int x = 0;
  for (int i = 0; i < ans; i++) {
    x = ((x << 1) | 1) & all;
  }
  for (int i = 0; i < ans; i++) {
    vector<bool> ndp(1 << n);
    for (int j = 0; j < (1 << n); j++) {
      if (dp[j]) {
        ndp[j] = true;
        for (int bit = 0; bit < n; bit++) {
          ndp[j ^ ((x << bit) & all)] = true;
        }
      }
    }
    x = x >> 1;
    dp = ndp;
  }
  return dp[all];
}

void solve(string s) {
  int ans = 0;
  while (!check(s, ans)) {
    ans++;
  }
  printf("%d\n", ans);
}

int main() {
#ifdef LOCAL
  freopen("c.in", "r", stdin);
  freopen("c.out", "w", stdout);
#endif

  string s;
  while (cin >> s) {
    solve(s);
  }

  return 0;
}
