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

const int MAXN = 305;

int dp[MAXN][MAXN][MAXN];
char s[MAXN];
int k;

int solve(int l, int r, int k) {
  if (l == r) { return 0;}
  if (l == r - 1) { return 1;};
  int &ans = dp[l][r][k];
  if (ans != -1) return ans;
  ans = max(ans, solve(l + 1, r, k));
  ans = max(ans, solve(l, r - 1, k));
  if (k) {
    ans = max(ans, solve(l + 1, r - 1, k - 1) + 2);
  }
  if (s[l] == s[r - 1]) {
    ans = max(ans, solve(l + 1, r - 1, k) + 2);
  }
//  eprintf("dp[%d][%d][%d] = %d\n", l, r, k, ans);
  return ans;
}

int main() {
#ifdef LOCAL
  freopen("d.in", "r", stdin);
  freopen("d.out", "w", stdout);
#endif

  while (scanf("%s%d", s, &k) == 2) {
    memset(dp, -1, sizeof(dp));
    printf("%d\n", solve(0, strlen(s), k));
  }

  return 0;
}
